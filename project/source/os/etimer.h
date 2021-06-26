/*
 * etimer.h
 *
 *  Created on: 22.06.2021
 *      Author: marco
 */

#ifndef ETIMER_H_
#define ETIMER_H_

#include "ctimer.h"



#define ETIMER_NOT_RUNNING NULL





typedef struct {
   CTLIST_NODE_TYPE;
   timer_t timer;
   ctimer_callback_t callback;
   process_event_t evt;
}etimer_t;

#define etimer_init(etimerptr) \
      etlist_next(&etimer_list, etimerptr) = ETIMER_NOT_RUNNING;



#endif /* ETIMER_H_ */
