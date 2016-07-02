/*
 * timer.c
 *
 *  Created on: 29. Juni 2016
 *      Author: blackdigi
 */

#include "timer.h"

void timer_set(timer_t *timer, timespan_t span)
{
    timer->start = timestamp_now();
    timer->stop = timer->start+span;
}

bool timer_expired(timer_t *timer)
{
    if(timestamp_passed(timer->stop))
    {
        return true;
    }

    return false;
}

timespan_t timer_left(timer_t *timer)
{
    timestamp_t now = timestamp_now();

    if(now > timer->stop)
    {
        return 0;
    }

    return timer->stop - now;
}

void timer_block(timer_t *timer)
{

}

