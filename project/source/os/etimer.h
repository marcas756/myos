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


#endif /* ETIMER_H_ */
