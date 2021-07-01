/*
 * ctimer.h
 *
 *  Created on: 22.06.2021
 *      Author: marco
 */

#ifndef CTIMER_H_
#define CTIMER_H_


#include "ptimer.h"

typedef struct ctimer_t ctimer_t;

typedef void (*ctimer_callback_t)(ctimer_t *ctimer);

struct ctimer_t {
   ptimer_t ptimer;
   process_t *context;
   ctimer_callback_t callback;
   void* data;
};


void ctimer_module_init(void);
void ctimer_start(ctimer_t *ctimer, timespan_t span, ctimer_callback_t callback, void *data);

#define ctimer_restart(ctimerptr) \
      ptimer_restart(&((ctimerptr)->ptimer))






#endif /* CTIMER_H_ */
