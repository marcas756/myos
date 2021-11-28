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


#ifndef PTIMER_H_
#define PTIMER_H_

#include "myos.h"
#include <stdbool.h>



#if (MYOSCONF_PTIMER_LIST_TYPE == MYOSCONF_DLIST)

#include "dlist.h"
typedef dlist_t ptlist_t;
typedef dlist_node_t ptlist_node_t;
#define PTLIST_NODE_TYPE                              DLIST_NODE_TYPE
#define ptlist_init(listptr)                          dlist_init(listptr)
#define ptlist_erase(listptr,nodeptr)                 dlist_erase(listptr,nodeptr)
#define ptlist_next(listptr,nodeptr)                  dlist_next(listptr,nodeptr)
#define ptlist_push_front(listptr,nodeptr)            dlist_push_front(listptr,nodeptr)
#define ptlist_prev(listptr,nodeptr)                  dlist_prev(listptr,nodeptr)
#define ptlist_foreach(listptr,iterator)              dlist_foreach(listptr,iterator)
#define ptlist_find(listptr,nodeptr)                  dlist_findlistptr,nodeptr)
#define ptlist_begin(listptr)                         dlist_begin(listptr)
#define ptlist_end(listptr)                           dlist_end(listptr)
#define ptlist_empty(listptr)                         dlist_empty(listptr)

#else

#include "slist.h"
typedef slist_t ptlist_t;
typedef slist_node_t ptlist_node_t;
#define PTLIST_NODE_TYPE                              SLIST_NODE_TYPE
#define ptlist_init(listptr)                          slist_init(listptr)
#define ptlist_erase(listptr,nodeptr)                 slist_erase(listptr,nodeptr)
#define ptlist_next(listptr,nodeptr)                  slist_next(listptr,nodeptr)
#define ptlist_push_front(listptr,nodeptr)            slist_push_front(listptr,nodeptr)
#define ptlist_prev(listptr,nodeptr)                  slist_prev(listptr,nodeptr)
#define ptlist_foreach(listptr,iterator)              slist_foreach(listptr,iterator)
#define ptlist_find(listptr,nodeptr)                  slist_findlistptr,nodeptr)
#define ptlist_begin(listptr)                         slist_begin(listptr)
#define ptlist_end(listptr)                           slist_end(listptr)
#define ptlist_empty(listptr)                         slist_empty(listptr)

#endif



PROCESS_EXTERN(ptimer_process);

typedef struct ptimer_t ptimer_t;

typedef void (*ptimer_handler_t) (ptimer_t *data);

struct ptimer_t{
   PTLIST_NODE_TYPE;
   timer_t timer;
   ptimer_handler_t handler;
   bool running;
};


#define ptimer_module_init() process_start(&ptimer_process, NULL);
void ptimer_poll_if_necessary(void);
void ptimer_start(ptimer_t* ptimer, timespan_t span, ptimer_handler_t handler);
void ptimer_restart(ptimer_t* ptimer);
void ptimer_restart_with_new_span(ptimer_t* ptimer, timespan_t span);
void ptimer_reset(ptimer_t* ptimer);
void ptimer_reset_with_new_span(ptimer_t* ptimer, timespan_t span);
#define ptimer_stop(ptimerptr) ptimer_remove_from_list(ptimerptr);
#define ptimer_expired(ptimerptr)   timer_expired(&(ptimerptr)->timer)
#define ptimer_left(ptimerptr)      timer_left(&(ptimerptr)->timer)

#endif /* PTIMER_H_ */
