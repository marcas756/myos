/*
 * etimer.c
 *
 *  Created on: 22.06.2021
 *      Author: marco
 */


#include "etimer.h"

extern bool process_deliver_event(process_event_t *evt);

void etimer_timeout_handler(void* data)
{
   etimer_t *etimer = data;

   if( PROCESS_IS_RUNNING(etimer->evt.to) )
   {
      PROCESS_CONTEXT_BEGIN(etimer->evt.to);

      process_deliver_event(&etimer->evt);

      PROCESS_CONTEXT_END();
   }
}




void etimer_start(etimer_t *etimer, timespan_t span, process_t *to, process_event_id_t evtid, void *data)
{
   etimer->evt.id = evtid;
   etimer->evt.data = data;
#if (PROCESS_CONF_EVENT_FROM == MYOSCONF_YES)
   etimer->evt.from = PROCESS_THIS();
#endif
   etimer->evt.to = to;

   ptimer_start(&(etimer->ptimer), span, etimer_timeout_handler);
}


