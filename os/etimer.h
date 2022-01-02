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


#ifndef ETIMER_H_
#define ETIMER_H_

#include "myos.h"

typedef struct {
   ptimer_t ptimer;
   process_event_t evt;
}etimer_t;

#define etimer_module_init() ptimer_module_init()
void etimer_start(etimer_t *etimer, timespan_t span, process_t *to, process_event_id_t evtid, void *data);
#define etimer_restart(etimerptr)                       ptimer_restart((ptimer_t*)etimerptr)
#define etimer_restart_with_new_span(etimerptr,span)    ptimer_restart_with_new_span((ptimer_t*)etimerptr,span)
#define etimer_reset(etimerptr)                         ptimer_reset((ptimer_t*)etimerptr)
#define etimer_reset_with_new_span(etimerptr,span)      ptimer_reset_with_new_span((ptimer_t*)etimerptr,span)
#define etimer_stop(etimerptr)                          ptimer_stop((ptimer_t*)etimerptr)
#define etimer_expired(etimerptr)                       ptimer_expired((ptimer_t*)etimerptr)
#define etimer_left(etimerptr)                          ptimer_left((ptimer_t*)etimerptr)


#define PROCESS_SLEEP(etimerptr,span) \
   do{ \
      etimer_start(etimerptr, span, PROCESS_THIS(), PROCESS_EVENT_CONTINUE, NULL); \
      PROCESS_WAIT_EVENT(PROCESS_EVENT_CONTINUE); \
   }while(0)

#endif /* ETIMER_H_ */
