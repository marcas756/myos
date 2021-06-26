/*
 * ptimer.c
 *
 *  Created on: 25.06.2021
 *      Author: marco
 */

#include "ptimer.h"

ptlist_t ptimer_list;

#define ptimer_is_running(ptimerptr) (ptlist_next(&ptimer_list,ptimerptr) != PTIMER_NOT_RUNNING)

PROCESS(ptimer_process,ptimer_process);
PROCESS_THREAD(ptimer_process)
{
   PROCESS_BEGIN();

   ptlist_init(&ptimer_list);

   while(1)
   {
      PROCESS_WAIT_EVENT(PROCESS_EVENT_POLL);



     // ptlist_foreach()
   }

   PROCESS_END();
}

void ptimer_module_init()
{
    process_start(&ptimer_process, NULL);
}

bool ptimer_start(ptimer_t* ptimer, timespan_t span, ptimer_handler_t *handler)
{
   if( ptimer_is_running(ptimer) )
   {
      return false;
   }

   ptimer->handler = handler;
   timer_start(&ptimer->timer,span);

   ptlist_push_front(&ptimer_list,ptimer);

   return true;
}
