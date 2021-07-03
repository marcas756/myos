/*
 * etimer.h
 *
 *  Created on: 22.06.2021
 *      Author: marco
 */

#ifndef ETIMER_H_
#define ETIMER_H_

#include "ptimer.h"

typedef struct {
   ptimer_t ptimer;
   process_event_t evt;
}etimer_t;

#define etimer_module_init() ptimer_module_init()
void etimer_start(etimer_t *etimer, timespan_t span, process_t *to, process_event_id_t evtid, void *data);

#define PROCESS_SLEEP(etimerptr,span) \
   do{ \
      etimer_start(etimerptr, span, PROCESS_THIS(), PROCESS_EVENT_CONTINUE, NULL); \
      PROCESS_WAIT_EVENT(PROCESS_EVENT_CONTINUE); \
   }while(0)

#endif /* ETIMER_H_ */
