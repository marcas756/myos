#include "rtimer.h"
#include <stdlib.h>


rtimer_t *rtimer_next = NULL;
bool rtimer_mutex = false;

bool rtimer_lock(void)
{
   bool status = false;

   CRITICAL_SECTION_BEGIN();

   if ( !rtimer_mutex )
   {
      rtimer_mutex = true;
      status = true;
   }

   CRITICAL_SECTION_END();

   return status;
}

void rtimer_release()
{
   rtimer_next = NULL;
   rtimer_mutex = false;
}


void rtimer_scheduler (void)
{
   rtimer_t *rtimer = rtimer_next;
   rtimer_release();

   if( rtimer->callback )
   {
      rtimer->callback(rtimer->data);
   }
}

rtimer_timespan_t rtimer_left(rtimer_t *rtimer)
{
    rtimer_timestamp_t now = rtimer_now();
    rtimer_timestamp_t stop = rtimer_timestamp_stop(rtimer);

    if( rtimer_timestamp_less_than(now,stop) )
    {
       return stop - now;
    }

    return 0;
}

void rtimer_start(rtimer_t *rtimer, rtimer_timespan_t span, rtimer_callback_t callback, void* data)
{
   rtimer->start = rtimer_now();
   rtimer->span = span;
   rtimer->callback = callback;
   rtimer->data = data;
   rtimer_next = rtimer;
   rtimer_arch_timer_set(rtimer_timestamp_stop(rtimer));
}

void rtimer_restart(rtimer_t *rtimer)
{
   rtimer->start = rtimer_now();
   rtimer_next = rtimer;
   rtimer_arch_timer_set(rtimer_timestamp_stop(rtimer));
}

void rtimer_reset(rtimer_t *rtimer)
{
   rtimer->start += rtimer->span;
   rtimer_next = rtimer;
   rtimer_arch_timer_set(rtimer_timestamp_stop(rtimer));
}
