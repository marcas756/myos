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
    \file       module.h
    \authors

    \brief      Brief description of the module

    \details    Detailed description of the module
*/

#ifndef PROCESS_H_
#define PROCESS_H_

#include "myosconf.h"
#include "pt.h"
#include "ringbuffer.h"
#include <stdbool.h>


#if (MYOSCONF_PROC_LIST_TYPE == MYOSCONF_DLIST)
#else
#include "slist.h"
typedef slist_t plist_t;
typedef slist_node_t plist_node_t;
#define PLIST_NODE_TYPE                              SLIST_NODE_TYPE
#define plist_init(listptr)                          slist_init(listptr)
#define plist_erase(listptr,nodeptr)                 slist_erase(listptr,nodeptr)
#define plist_next(listptr,nodeptr)                  slist_next(listptr,nodeptr)
#define plist_push_front(listptr,nodeptr)            slist_push_front(listptr,nodeptr)
#define plist_prev(listptr,nodeptr)                  slist_prev(listptr,nodeptr)
#define plist_foreach(listptr,iterator)              slist_foreach(listptr,iterator)
#endif



#ifdef MYOSCONF_PROC_EVENT_QUEUE_SIZE
#define PROCESS_EVENT_QUEUE_SIZE    MYOSCONF_PROC_EVENT_QUEUE_SIZE
#else
#define PROCESS_EVENT_QUEUE_SIZE    8
#endif


#define PROCESS_EVENT_START     0
#define PROCESS_EVENT_POLL      1
#define PROCESS_EVENT_CONTINUE  2
#define PROCESS_EVENT_TIMEOUT   3

#define PROCESS_BROADCAST NULL



typedef struct process_event_t process_event_t;
typedef struct process_t process_t;
typedef int(*process_thread_t)(process_t *process, process_event_t *evt);


struct process_t {
   PLIST_NODE_TYPE;
   process_thread_t thread;
   void* data;
   pt_t pt;
   bool pollreq;
};


struct process_event_t {
   process_event_id_t id;
   void *data;
#if (MYOSCONF_PROC_EVENT_FROM == MYOSCONF_YES)
   process_t *from;
#endif
   process_t *to;
};


extern process_t *process_current;
#define PROCESS_THIS() process_current

#define PROCESS_CONTEXT_BEGIN(processptr) \
      do{ \
         process_t *process_backup; \
         process_backup = PROCESS_THIS(); \
         PROCESS_THIS() = processptr

#define PROCESS_CONTEXT_END() \
         PROCESS_THIS() = process_backup; \
      }while(0)


#define PROCESS(name,threadname) \
   int process_thread_##threadname(process_t *process, process_event_t *evt);  \
   process_t name = {{0},process_thread_##threadname,0,{0},false}

#define PROCESS_EXTERN(name) \
      extern process_t name

#define PROCESS_DATA()            (process->data)
#define PROCESS_PT()              (process->pt)
#define PROCESS_EVENT_DATA()      (evt->data)
#define PROCESS_EVENT_ID()        (evt->id)


#define EXTERN_PROCESS(name) \
   extern process_t name

#define PROCESS_THREAD(name) \
int process_thread_##name(process_t *process, process_event_t *evt)

#if (MYOSCONF_PROC_EVENT_FROM == MYOSCONF_YES)
#define PROCESS_RESPOND(evtid,dataptr) \
   process_respond(evt,evtid,dataptr)
#endif


#define PROCESS_INIT(processptr,threadname) \
   process_init(processptr, process_thread_##threadname)

#define PROCESS_IS_RUNNING(processptr) \
   (PT_IS_RUNNING(&(processptr)->pt))


#define PROCESS_BEGIN()                 PT_BEGIN(&PROCESS_PT())
#define PROCESS_END()                   PT_END(&PROCESS_PT())
#define PROCESS_WAIT_EVENT(evtid)       PT_YIELD_UNTIL(&PROCESS_PT(), PROCESS_EVENT_ID() == evtid)
#define PROCESS_WAIT_EVENT_UNTIL(cond)  PT_YIELD_UNTIL(&PROCESS_PT(), cond)
#define PROCESS_WAIT_ANY_EVENT()        PT_YIELD(&PROCESS_PT())

#define PROCESS_SUSPEND() \
   do{ \
      process_post(PROCESS_THIS(),PROCESS_EVENT_CONTINUE,NULL); \
      PROCESS_WAIT_EVENT(PROCESS_EVENT_CONTINUE); \
   while(0)

void process_module_init(void);
void process_init( process_t *process, process_thread_t thread );
bool process_start(process_t *process, void* data);
bool process_post(process_t *to, process_event_id_t evtid, void* data);
bool process_post_sync(process_t *to, process_event_id_t evtid, void* data);
int process_run(void);
void process_poll(process_t *process);

#endif /* PROCESS_H_ */


















