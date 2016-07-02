/*
 * timer.h
 *
 *  Created on: 26. Juni 2016
 *      Author: blackdigi
 */

#ifndef  TIMER_H_
#define  TIMER_H_

#include "timestamp.h"

#include <stdbool.h>

typedef struct {
    timestamp_t start;
    timestamp_t stop;
}timer_t;

void timer_set(timer_t *timer, timespan_t span);
bool timer_expired(timer_t *timer);
timespan_t timer_left(timer_t *timer);
void timer_reset();
void timer_restart();



#endif /*  TIMER_H_ */
