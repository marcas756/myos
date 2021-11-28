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









