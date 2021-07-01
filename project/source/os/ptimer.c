/*
 * ptimer.c
 *
 *  Created on: 25.06.2021
 *      Author: marco
 */

#include "ptimer.h"


ptlist_t ptimer_running_list;

timestamp_t ptimer_next_expiration = 0;

void ptimer_add_to_list(ptimer_t *ptimer)
{
   if( !ptimer->running )
   {
      ptimer->running = true;
      ptlist_push_front(&ptimer_running_list,ptimer);
   }
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

      timestamp_t now = timestamp_now();
      ptimer_t *curr = (ptimer_t*)ptlist_begin(&ptimer_running_list);

      while(curr != (ptimer_t*)ptlist_end(&ptimer_running_list))
      {
         if( ptimer_expired(curr) )
         {
            ptimer_t *next = (ptimer_t*)ptlist_next(&ptimer_running_list,curr);

            ptimer_remove_from_list(curr);

            if( curr->handler )
            {
               curr->handler(curr);
            }

            curr = next;
         }
         else
         {
            /* comp next exp time */
            curr  = (ptimer_t*)ptlist_next(&ptimer_running_list,curr);
         }
      }
   }

   PROCESS_END();
}

void ptimer_module_init()
{
    process_start(&ptimer_process, NULL);
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


void ptimer_reset(ptimer_t* ptimer)
{
   timer_reset(&ptimer->timer);
   ptimer_add_to_list(ptimer);
}

void ptimer_set_span(ptimer_t* ptimer, timespan_t span)
{
   timer_set_span(&ptimer->timer,span);
}

void ptimer_stop(ptimer_t* ptimer)
{
   ptimer_remove_from_list(ptimer);
}




