/*
 * rtimer_arch.c
 *
 *  Created on: 06.07.2021
 *      Author: marco
 */

#include "rtimer_arch.h"
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
/*
   ITIMER_REAL
   This timer counts down in real (i.e., wall clock) time.
   At each expiration, a SIGALRM signal is generated.

   ITIMER_VIRTUAL
   This timer counts down against the user-mode CPU time
   consumed by the process.  (The measurement includes CPU
   time consumed by all threads in the process.)  At each
   expiration, a SIGVTALRM signal is generated.

   ITIMER_PROF
   This timer counts down against the total (i.e., both user
   and system) CPU time consumed by the process.  (The
   measurement includes CPU time consumed by all threads in
   the process.)  At each expiration, a SIGPROF signal is
   generated.

   In conjunction with ITIMER_VIRTUAL, this timer can be used
   to profile user and system CPU time consumed by the
   process.
*/


static struct sigaction rtimer_arch_sa;
static struct itimerval rtimer_arch_timer;

extern void rtimer_scheduler (void);


static void rtimer_arch_scheduler(int signum)
{
   if( signum == SIGALRM )
   {
      rtimer_scheduler();
   }
}

void rtimer_arch_module_init(void)
{
   rtimer_arch_sa.sa_handler = &rtimer_arch_scheduler;
   sigaction (SIGALRM, &rtimer_arch_sa, NULL);
}

rtimer_arch_timestamp_t rtimer_arch_now(void)
{
   struct timespec tim;
   rtimer_arch_timestamp_t timerval;
   clock_gettime( CLOCK_MONOTONIC, &tim );
   timerval = RTIMER_ARCH_TICKS_PER_SEC * tim.tv_sec + (tim.tv_nsec*RTIMER_ARCH_TICKS_PER_SEC)/1000000000UL;
   return timerval;
}


void rtimer_arch_timer_set(rtimer_arch_timestamp_t stop)
{
   rtimer_arch_timespan_t span = stop - rtimer_arch_now();
   rtimer_arch_timer.it_value.tv_sec = span/RTIMER_ARCH_TICKS_PER_SEC;
   rtimer_arch_timer.it_value.tv_usec = ((span%RTIMER_ARCH_TICKS_PER_SEC)*1000000UL)/RTIMER_ARCH_TICKS_PER_SEC;
   setitimer (ITIMER_REAL, &rtimer_arch_timer, NULL);
}









