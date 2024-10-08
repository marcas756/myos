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


#include "myos.h"


static ptlist_t ptimer_running_list;
static ptimer_t *ptimer_next_to_expire = NULL;

void ptimer_next_update(ptimer_t *ptimer)
{
   if( ptimer_next_to_expire )
   {
      timestamp_t next_stop = timer_timestamp_stop(&ptimer_next_to_expire->timer);
      timestamp_t this_stop = timer_timestamp_stop(&ptimer->timer);

      if( timestamp_less_than(this_stop,next_stop) )
      {
         CRITICAL_EXPRESSION(ptimer_next_to_expire = ptimer);
      }
   }
   else
   {
      CRITICAL_EXPRESSION(ptimer_next_to_expire = ptimer);
   }
}

void ptimer_add_to_list(ptimer_t *ptimer)
{
   if ( !ptimer->running )
   {
      ptimer->running = true;
      ptlist_push_front(&ptimer_running_list,ptimer);
   }

   ptimer_next_update(ptimer);
}

void ptimer_remove_from_list(ptimer_t *ptimer)
{
   if( ptimer->running )
   {
      ptimer->running = false;
      ptlist_erase(&ptimer_running_list,ptimer);
   }
}


PROCESS(ptimer_process,ptimer_process);
PROCESS_THREAD(ptimer_process)
{
   PROCESS_BEGIN();

   ptlist_init(&ptimer_running_list);

   while(1)
   {
      PROCESS_WAIT_EVENT(PROCESS_EVENT_POLL);

      CRITICAL_EXPRESSION(ptimer_next_to_expire = NULL);

      ptimer_t *curr = (ptimer_t*)ptlist_begin(&ptimer_running_list);

      while(curr != (ptimer_t*)ptlist_end(&ptimer_running_list))
      {
         if( ptimer_expired(curr) )
         {
            ptimer_t *next = (ptimer_t*)ptlist_next(&ptimer_running_list,curr);

            /* remove ptimer from list */
            curr->running = false;
            ptlist_erase(&ptimer_running_list,curr);

            if( curr->handler )
            {
               curr->handler(curr);
            }

            curr = next;
         }
         else
         {
            ptimer_next_update(curr);
            curr  = (ptimer_t*)ptlist_next(&ptimer_running_list,curr);
         }
      }

   }

   PROCESS_END();
}


void ptimer_start(ptimer_t* ptimer, timespan_t span, ptimer_handler_t handler)
{
   ptimer->handler = handler;
   timer_start(&ptimer->timer,span);
   ptimer_add_to_list(ptimer);
}

void ptimer_restart(ptimer_t* ptimer)
{
   timer_restart(&ptimer->timer);
   ptimer_add_to_list(ptimer);
}

void ptimer_restart_with_new_span(ptimer_t* ptimer, timespan_t span)
{
   timer_set_span(&ptimer->timer,span);
   ptimer_restart(ptimer);
}

void ptimer_reset(ptimer_t* ptimer)
{
   timer_reset(&ptimer->timer);
   ptimer_add_to_list(ptimer);
}

void ptimer_reset_with_new_span(ptimer_t* ptimer, timespan_t span)
{
   timer_set_span(&ptimer->timer,span);
   ptimer_reset(ptimer);
}

void ptimer_poll_if_necessary(void)
{
   if (ptimer_next_to_expire && ptimer_expired(ptimer_next_to_expire))
   {
      process_poll(&ptimer_process);
   }
}




