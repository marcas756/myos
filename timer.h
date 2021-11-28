/*! \copyright
 
   https://opensource.org/licenses/BSD-3-Clause
 
   Copyright 2013-2021 Marco Bacchi <marco@bacchi.at>
   
   Redistribution and use in source and binary forms, with or without 
   modification, are permitted provided that the following conditions are met:
   
   1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.
   
   2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

   3. Neither the name of the copyright holder nor the names of its 
   contributors may be used to endorse or promote products derived from this 
   software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
   POSSIBILITY OF SUCH DAMAGE.
*/


/*!
    \file       timer.h

    \brief

    \details
*/

#ifndef  TIMER_H_
#define  TIMER_H_

#include "timestamp.h"
#include <stdbool.h>

/* required due to redefinition of timer_t in /usr/include/x86_64-linux-gnu/bits/types/timer_t.h for linux host build */
typedef struct {
    timestamp_t start;
    timespan_t span;
}myos_timer_t ;

#define timer_t myos_timer_t

void timer_start(timer_t *timer, timespan_t span);

timespan_t timer_left(timer_t *timer);

void timer_reset(timer_t *timer);
void timer_set_span(timer_t *timer, timespan_t span);

/*!
    \brief      Restarts a previously set timer
    \details    Restarts a previously set timer. Be aware of that the timer must have
                been set properly before, otherwise behaviour is undefined.

    \param[in]      timer       Timer instance to restart
*/
void timer_restart(timer_t *timer);
bool timer_expired(timer_t *timer);

#define timer_timestamp_stop(timerptr) \
      ((timerptr)->start + (timerptr)->span)

#define timer_module_init timestamp_module_init


#endif /*  TIMER_H_ */
