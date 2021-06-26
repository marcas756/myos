/*
 * etimer.c
 *
 *  Created on: 22.06.2021
 *      Author: marco
 */


#include "etimer.h"


etlist_t etimer_list;

#define etimer_is_running(etimerptr) (etlist_next(&etimer_list,etimerptr) != ETIMER_NOT_RUNNING)

void module_etimer_init()
{
   etlist_init(&etimer_list);
}

bool etimer_set(etimer_t *etimer, timespan_t span, process_t *to, process_event_id_t evtid, void *data)
{
   if( etimer_is_running(etimer) )
   {
      return false;
   }

   timer_start(&etimer->timer,span);

   etimer->event.from = process_current;
   etimer->event.to = to;
   etimer->event.id = evtid;
   etimer->event.data = data;

   etlist_push_front(&etimer_list,etimer);

   return true;
}

bool etimer_stop(etimer_t *etimer)
{
   if(etimer_is_running(etimer))
   {
      etlist_erase(&etimer_list,etimer);
      etlist_next(&etimer_list,etimer) = ETIMER_NOT_RUNNING;
      return true;
   }

   return false;
}
