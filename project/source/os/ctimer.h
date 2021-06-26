/*
 * ctimer.h
 *
 *  Created on: 22.06.2021
 *      Author: marco
 */

#ifndef CTIMER_H_
#define CTIMER_H_


#include "ptimer.h"



typedef void (*ctimer_callback_t)(void* data);

typedef struct {
   ptimer_t ptimer;
   process_t *context;
   ctimer_callback_t callback;
   void* data;
}ctimer_t;






#endif /* CTIMER_H_ */
