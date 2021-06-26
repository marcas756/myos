/*
 * ptimer.h
 *
 *  Created on: 25.06.2021
 *      Author: marco
 */

#ifndef PTIMER_H_
#define PTIMER_H_

#include "timer.h"
#include "process.h"
#include <stdbool.h>

#define SLIST 0
#define DLIST 1

#define PTIMER_NOT_RUNNING NULL

#define PTIMER_LIST_TYPE SLIST

#if (PTIMER_LIST_TYPE == DLIST)
#elif (PTIMER_LIST_TYPE == SLIST)

#include "slist.h"

typedef slist_t ptlist_t;
typedef slist_node_t ptlist_node_t;

#define PTLIST_NODE_TYPE                              SLIST_NODE_TYPE
#define ptlist_init(listptr)                          slist_init(listptr)
#define ptlist_erase(listptr,nodeptr)                 slist_erase(listptr,nodeptr)
#define ptlist_next(listptr,nodeptr)                  slist_next(listptr,nodeptr)
#define ptlist_push_front(listptr,nodeptr)            slist_push_front(listptr,nodeptr)
#define ptlist_prev(listptr,nodeptr)                  slist_prev(listptr,nodeptr)
#define ptlist_foreach(slist,iterator)                slist_foreach(slist,iterator)

#else
#error "Unknown list type"
#endif

typedef void (*ptimer_handler_t) (void *data);

typedef struct {
   PTLIST_NODE_TYPE;
   timer_t timer;
   ptimer_handler_t *handler;
}ptimer_t;

void ptimer_module_init(void);

#endif /* PTIMER_H_ */
