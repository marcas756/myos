#include "task.h"

 #if DEBUG_TASK
 #define DBG(args) DEBUG_PRINTF(args)
 #else
 #define DBG(args)
 #endif

/*!
    \brief  Define size of the event queue, if not defined yet
\{*/
#if (TASK_EVENT_QUEUE_SIZE <= 0)
#define TASK_EVENT_QUEUE_SIZE 8
#endif
/*!\}*/

#if TASK_ERRORS

    typedef struct {
        uint8_t invoke_error;
        uint8_t create_error;
        uint8_t post_error;
    }task_errors_t;


    STATIC task_errors_t task_errors;

    #define TASK_ERROR(error)                           \
        do {                                            \
            if(task_errors.error != ~((uint8_t)(0)))    \
               {task_errors.error++;}                   \
        }while(0)

#else /*!TASK_ERRORS*/

    #define TASK_ERROR(error)

#endif /*TASK_ERRORS*/


STATIC RINGBUFFER_T(task_event_queue) task_event_queue;
task_t *task_current = NULL;
STATIC task_list_t task_list;
bool task_pollreq;

#define task_foreach(iterator)                                  \
        for((iterator) = (task_t*)task_list_begin();            \
            (iterator);                                         \
            (iterator) = (task_t*)task_list_next(iterator))


#define task_init_startup(taskptr, threadfptr, dataptr)         \
    do {                                                        \
        PT_INIT(&(taskptr)->pt);                                \
        (taskptr)->state = TASK_STATE_WAITING;                  \
        (taskptr)->thread = threadfptr;                         \
        (taskptr)->data = dataptr;                              \
    } while(0)



#if TASK_INLINE_INVOKE

    #define task_invoke(taskptr,event_id, dataptr)                              \
        do{                                                                     \
            task_t *tmp = task_current;                                         \
            task_current = (taskptr);                                           \
            task_current->state = task_current->thread(event_id, dataptr);      \
            if(task_current->state == TASK_STATE_TERMINATED)                    \
            {                                                                   \
                task_list_erase(task_current);                                  \
            }                                                                   \
            task_current = tmp;                                                 \
         }while(0)

#else /*! TASK_INLINE_INVOKE */

    static void task_invoke(task_t *taskptr,event_id_t event_id, void *dataptr)
    {
        task_t *tmp = task_current;
        task_current = (taskptr);
        task_current->state = task_current->thread(event_id, dataptr);

        if(task_current->state == TASK_STATE_TERMINATED)
        {
            task_list_erase(task_current);
        }

        task_current = tmp;
    }

#endif

#if TASK_INLINE_POLLHANDLER

    #define task_poll_handler()                                                             \
        do{                                                                                 \
            task_t *iterator;                                                               \
            task_pollreq = 0;                                                               \
            task_foreach(iterator)                                                          \
            {                                                                               \
                if(iterator->pollreq)                                                       \
                {                                                                           \
                    iterator->pollreq = 0;                                                  \
                    task_invoke(iterator, EVENT_TASK_POLL, NULL);                           \
                }                                                                           \
            }                                                                               \
        }while(0)


#else /* !TASK_INLINE_POLLHANDLER */

    static void task_poll_handler(void)
    {
        task_t *iterator;

        task_pollreq = 0;

        task_foreach(iterator)
        {
            if(iterator->pollreq)
            {
                iterator->pollreq = 0;
                task_invoke(iterator, EVENT_TASK_POLL, NULL);
            }
        }
    }

#endif


bool task_post_now(task_t *target ,event_id_t event_id, void *data)
{
    /* Don't deliver any event to a terminated task */
    if(target->state == PT_STATE_TERMINATED)
    {
        TASK_ERROR(invoke_error);
        return false;
    }

    task_invoke(target, event_id, data);

    return true;
}


bool task_start(task_t *task, task_thread_fp thread, void *data)
{
    /* task must exist and must not run yet */
    if(!task || task_list_find(task))
    {
        TASK_ERROR(create_error);
        return false;
    }

    /* setup task */
    task_init_startup(task, thread, data);

    task_invoke(task, EVENT_TASK_START, NULL);

    /* if task did not terminate on its own ... */
    if(task->state != TASK_STATE_TERMINATED)
    {
        /* ... add it to running task list */
        task_list_push_front(task);
    }

    return true;
}


#if TASK_INLINE_POLL

    #define task_poll(targetptr)            \
        do{                                 \
            (targetptr)->pollreq = true;    \
            task_pollreq = true;            \
        }while(0)

#else /* !TASK_INLINE_POLL */

    void task_poll(task_t *target)
    {
        target->pollreq = true;
        task_pollreq = true;
    }

#endif


bool task_post(task_t *target, event_id_t event_id, void *data)
{
    event_t *event;

    /* check if there is place for another event */
    if(RINGBUFFER_FULL(task_event_queue))
    {
        TASK_ERROR(post_error);
        return false;
    }

    /* init and push event onto event queue */
    event = RINGBUFFER_TAIL_PTR(task_event_queue);
    task_event_init(event, target, event_id, data);
    RINGBUFFER_PUSH(task_event_queue);

    return true;
}



void task_scheduler_run()
{
    event_t *event;

    /* handle any poll requests in between two regular events */
    if(task_pollreq)
    {
        task_poll_handler();
    }

    /* check if there is any regular event to handle */
    if(RINGBUFFER_EMPTY(task_event_queue))
    {
        return;
    }

    /* get event from event queue */
    event = RINGBUFFER_HEAD_PTR(task_event_queue);

    /* Addressed event? */
    if(event->target)
    {
        task_invoke(event->target, event->id, event->data);
    }
    else /* not addressed ... broadcast event to all running tasks */
    {
        task_t *iterator;

        /* deliver event to all running tasks */
        task_foreach(iterator)
        {
            /* handle any poll requests in between two regular broadcast task invocations */
            if(task_pollreq)
            {
                task_poll_handler();
            }

            task_invoke(iterator, event->id, event->data);
        }
    }

    /* event handled ... remove it from event queue */
    RINGBUFFER_POP(task_event_queue);
}




