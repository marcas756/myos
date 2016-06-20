/*
 * task.h
 *
 *  Created on: 07. Mai 2016
 *      Author: blackdigi
 */

#ifndef TASK_H_
#define TASK_H_

#include "project.h"

#include <stdbool.h>
#include <stddef.h>
#include "pt.h"
#include "ringbuffer.h"
#include "task_list.h"


#define TASK_THREAD_ARGS        task_t *task, event_id_t event, void *data
#define TASK_THREAD(name)       PT_THREAD(name(TASK_THREAD_ARGS))
#define task_state_t            pt_state_t

/*!
    \brief  Mapping of protothread states to task states
\{*/
#define TASK_STATE_TERMINATED   PT_STATE_TERMINATED
#define TASK_STATE_WAITING      PT_STATE_WAITING
#define TASK_STATE_RUNNING      (PT_STATE_WAITING+1)
/*!\}*/



typedef struct task_t task_t;

typedef enum {
    EVENT_TASK_START,
    EVENT_TASK_RESUME,
    EVENT_TASK_POLL
}event_id_t;

typedef struct {
    task_t *target;
    event_id_t id;
    void *data;
}event_t;

typedef task_state_t (*task_thread_fp)(TASK_THREAD_ARGS);

struct task_t{
    task_list_node_t link;
    pt_t pt;
    task_thread_fp thread;
    task_state_t state;
    void *data;
    bool pollreq;
};


#define task_event_init(eventptr, targetptr, event_id, dataptr)                 \
        do {                                                                    \
            (eventptr)->target = targetptr;                                     \
            (eventptr)->id = event_id;                                          \
            (eventptr)->data = dataptr;                                         \
        } while(0)



#define task_init(taskptr)                                      \
    do {                                                        \
        (taskptr)->state = TASK_STATE_TERMINATED;               \
    } while(0)



/* Addressed event */


#define TASK_BEGIN()    PT_BEGIN(&((task)->pt))
#define TASK_END()      PT_END(&((task)->pt))

#define TASK_SUSPEND()                                                  \
    do {                                                                \
        task_post(task_current, EVENT_TASK_RESUME, NULL);               \
        TASK_WAIT_EVENT_UNTIL(event == EVENT_TASK_RESUME);              \
    } while(0)



#define TASK_WAIT_EVENT()               PT_YIELD(&((task)->pt))
#define TASK_WAIT_EVENT_UNTIL(cond)     PT_YIELD_UNTIL(&((task)->pt),cond);


bool task_post(task_t *target, event_id_t event_id, void *data);
void task_poll(task_t *target);
bool task_create(task_t *task, task_thread_fp thread, void *data);



#endif /* TASK_H_ */
