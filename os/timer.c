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
    \file       timer.c

    \brief

    \details
*/


#include "timer.h"

/*!
    \brief      Starts a timer using a time span
    \details    Timer will expire as soon as the time span elapsed.
                If the timer is running yet, the timer gets reinitialized with
                the new parameters provided. Any information about the previous timer setting
                gets lost.


    \param[in]      timer       Timer instance to set
    \param[in]      span        Time span to wait to elapse
*/
void timer_start(timer_t *timer, timespan_t span)
{
   timer->span = span;
   timer->start = timestamp_now();
}

void timer_restart(timer_t *timer)
{
    timer->start = timestamp_now();
}


void timer_set_span(timer_t *timer, timespan_t span)
{
   timer->span = span;
}


void timer_reset(timer_t *timer)
{
   timer->start += timer->span;
}



/*!
    \brief      Get the time left for the timer to expire
    \details    Provides the time left until expiration of the timer.
                It the timer expired yet, it will return 0 regardless of additional time elapsed
                after expiration of the timer. This function does not provide any information
                about the time after timers expiration.

    \param[in]      timer       Timer instance
    \returns    time left until expiration
*/
timespan_t timer_left(timer_t *timer)
{
    timestamp_t now = timestamp_now();
    timestamp_t stop = timer_timestamp_stop(timer);

    if( timestamp_less_than(now,stop) )
    {
       return stop - now;
    }

    return 0;
}



/*!
    \brief      Check if timer expired
    \details    Checks if timer expired. Timer will expire as soon as the time span
                provided with timer_start is elapsed.

    \param[in]      timer       Timer instance to check
    \returns    true if timer expired, false otherwise
*/
bool timer_expired(timer_t *timer)
{
   return (timer_left(timer) == 0);
}





