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

      ptimer_t *ptimer;

      timestamp_t now = timestamp_now();

      ptlist_foreach(&ptimer_running_list,ptimer)
      {
         if( ptimer_expired(ptimer) )
         {
            if( ptimer->handler )
            {
               ptimer->handler(ptimer);
            }

            ptimer_remove_from_list(ptimer);
         }
         else
         {



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




