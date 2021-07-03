/*
 * ptimer.c
 *
 *  Created on: 25.06.2021
 *      Author: marco
 */

#include "ptimer.h"
#include "critical.h"


ptlist_t ptimer_running_list;

ptimer_t *ptimer_next_in_time = NULL;

void ptimer_next_update(ptimer_t *ptimer)
{
   if( ptimer_next_in_time )
   {
      timestamp_t next_stop = timer_timestamp_stop(&ptimer_next_in_time->timer);
      timestamp_t this_stop = timer_timestamp_stop(&ptimer->timer);

      if( timestamp_less_than(this_stop,next_stop) )
      {
         CRITICAL_EXPRESSION(ptimer_next_in_time = ptimer);
      }
   }
   else
   {
      CRITICAL_EXPRESSION(ptimer_next_in_time = ptimer);
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

      CRITICAL_EXPRESSION(ptimer_next_in_time = NULL);

      ptlist_foreach(&ptimer_running_list,ptimer)
      {
         ptimer_next_update(ptimer);
      }
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

      CRITICAL_EXPRESSION(ptimer_next_in_time = NULL);

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

void ptimer_stop(ptimer_t* ptimer)
{
   ptimer_remove_from_list(ptimer);
}

void ptimer_poll(void)
{
   if (ptimer_next_in_time && ptimer_expired(ptimer_next_in_time))
   {
      process_poll(&ptimer_process);
   }
}




