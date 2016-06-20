#include "task.h"

 #if DEBUG_TASK
 #define DBG(args) DEBUG_PRINTF(args)
 #else
 #define DBG(args)
 #endif

/*!
    \brief  Define size of the event queue, if not defined yet
\{*/
#if !TASK_EVENT_QUEUE_SIZE
#define TASK_EVENT_QUEUE_SIZE 8
#endif
/*!\}*/

#ifdef TASK_ERRORS
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

RINGBUFFER_TYPEDEF(task_event_queue, event_t, TASK_EVENT_QUEUE_SIZE);
STATIC RINGBUFFER_T(task_event_queue) task_event_queue;
STATIC task_t *task_current;
STATIC task_list_t task_list;
STATIC bool task_pollreq;

#define task_init_startup(taskptr, threadfptr, dataptr)         \
    do {                                                        \
        PT_INIT(&(taskptr)->pt);                                \
        (taskptr)->state = TASK_STATE_WAITING;                  \
        (taskptr)->thread = threadfptr;                         \
        (taskptr)->data = dataptr;                              \
    } while(0)



STATIC void task_invoke(task_t *task ,event_id_t event_id, void *data)
{
    /* Don't deliver any event to a terminated task */
    if(task->state == PT_STATE_TERMINATED)
    {
        TASK_ERROR(invoke_error);
        return;
    }

    /* Invoke task */
    task_current = task;
    task->state = task->thread(task,event_id,data);
    task_current = NULL;

    /* Remove task from task list if it has terminated */
    if(task->state == PT_STATE_TERMINATED)
    {
        task_list_erase(task);
    }

    return;
}


bool task_create(task_t *task, task_thread_fp thread, void *data)
{
    /* task must not run yet */
    if(task->state != PT_STATE_TERMINATED)
    {
        TASK_ERROR(create_error);
        return false;
    }

    /* setup task */
    task_init_startup(task, thread, data);

    /* try sending startup event to task */
    if(!task_post(task, EVENT_TASK_START, NULL))
    {
        return false;
    }

    /* add task to running task list */
    task_list_push_front(task);

    return true;
}


void task_poll(task_t *target)
{
    target->pollreq = true;
    task_pollreq = true;
}


bool task_post(task_t *target, event_id_t event_id, void *data)
{
    event_t *event;

    /* check if there is place for another event */
    if(RINGBUFFER_FULL(&task_event_queue))
    {
        TASK_ERROR(post_error);
        return false;
    }

    /* init and push event onto event queue */
    event = RINGBUFFER_TAIL_PTR(&task_event_queue);
    task_event_init(event, target, event_id, data);
    RINGBUFFER_PUSH(&task_event_queue);

    return true;
}



void task_scheduler_run ()
{
    event_t *event;

    /* poll handler */
    if(task_pollreq)
    {
        task_t *iterator;

        /* deliver poll event to running tasks with poll flag set */
        for(iterator = (task_t*)task_list_begin(); iterator; iterator = (task_t*)task_list_next(iterator))
        {
            if(iterator->pollreq)
            {
                task_invoke(iterator,EVENT_TASK_POLL,NULL);
            }
        }
    }

    /* check if there is any regular event to handle */
    if(RINGBUFFER_EMPTY(&task_event_queue))
    {
        return;
    }

    /* get event from event queue */
    event = RINGBUFFER_HEAD_PTR(&task_event_queue);

    if(event->target) /* Addressed event? */
    {
        task_invoke(event->target,event->id,event->data);
    }
    else /* Broadcast event! */
    {
        task_t *iterator;

        /* deliver event to all running tasks */
        for(iterator = (task_t*)task_list_begin(); iterator; iterator = (task_t*)task_list_next(iterator))
            task_invoke(iterator,event->id,event->data);
    }

    /* event handled ... remove it from event queue */
    RINGBUFFER_POP(&task_event_queue);
}




