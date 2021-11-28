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


/*!
    \brief      Callback timer implementation (ctimer)

    \details
*/


#ifndef CTIMER_H_
#define CTIMER_H_


#include "myos.h"

typedef struct ctimer_t ctimer_t;

typedef void (*ctimer_callback_t)(ctimer_t *ctimer);

struct ctimer_t {
   ptimer_t ptimer;
   process_t *context;
   ctimer_callback_t callback;
   void* data;
};


#define ctimer_module_init() ptimer_module_init()
void ctimer_start(ctimer_t *ctimer, timespan_t span, ctimer_callback_t callback, void *data);
#define ctimer_restart(ctimerptr)                       ptimer_restart((ptimer_t*)ctimerptr)
#define ctimer_restart_with_new_span(ctimerptr,span)    ptimer_restart_with_new_span((ptimer_t*)ctimerptr,span)
#define ctimer_reset(ctimerptr)                         ptimer_rreset((ptimer_t*)ctimerptr)
#define ctimer_reset_with_new_span(ctimerptr,span)      ptimer_reset_with_new_span((ptimer_t*)ctimerptr,span)
#define ctimer_stop(ctimerptr)                          ptimer_stop((ptimer_t*)ctimerptr)
#define ctimer_expired(ctimerptr)                       ptimer_expired((ptimer_t*)ctimerptr)
#define ctimer_left(ctimerptr)                          ptimer_left((ptimer_t*)ctimerptr)



#endif /* CTIMER_H_ */
