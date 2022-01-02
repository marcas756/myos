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




#include <process.h>
#include <stdlib.h>
#include "debug.h"
#include "timestamp.h"
#include "critical.h"



#if DEBUG_PROCESS
#define DBG(...) DBG_FUNC(__VA_ARGS__)
#define DBG_PROCESS(...) do{DBG("[%d] process: ",(int)timestamp_now());DBG(__VA_ARGS__);}while(0)
#else
#define DBG(...)
#define DBG_PROCESS(...)
#endif

process_t *process_current = NULL;

static plist_t process_running_list;

RINGBUFFER_TYPEDEF(process_event_queue,process_event_t,PROCESS_EVENT_QUEUE_SIZE);
static RINGBUFFER_T(process_event_queue) process_event_queue;
static bool process_global_pollreq = false;



void process_module_init(void)
{
   /* start with an empty process list and an empty event queue */
   plist_init(&process_running_list);
   RINGBUFFER_INIT(process_event_queue);
   PROCESS_THIS() = NULL;
}



bool process_post(process_t *to, process_event_id_t evtid, void* data)
{
   process_event_t *evt;

   if( RINGBUFFER_FULL(process_event_queue) )
   {
      return false;
   }

   evt = RINGBUFFER_TAIL_PTR(process_event_queue);
#if (MYOSCONF_PROC_EVENT_FROM == MYOSCONF_YES)
   evt->from = PROCESS_THIS();
#endif
   evt->to = to;
   evt->id = evtid;
   evt->data = data;

#if (MYOSCONF_PROC_EVENT_FROM == MYOSCONF_YES)
   DBG_PROCESS("post from %p to %p evtid=%d ...\n",(void*)evt->from,(void*)evt->to,evt->id);
#else
   DBG_PROCESS("post to %p evtid=%d ...\n",(void*)evt->to,evt->id);
#endif

   RINGBUFFER_PUSH(process_event_queue);

   return true;
}

bool process_deliver_event(process_event_t *evt)
{

#if (MYOSCONF_PROC_EVENT_FROM == MYOSCONF_YES)
   DBG_PROCESS("deliver_event from %p to %p evtid=%d ...\n",(void*)evt->from,(void*)evt->to,evt->id);
#else
   DBG_PROCESS("deliver_event to %p evtid=%d ...\n",(void*)evt->to,evt->id);
#endif

   if ( PROCESS_IS_RUNNING(evt->to) )
   {
      PROCESS_CONTEXT_BEGIN(evt->to);

      if ( PROCESS_THIS()->thread(PROCESS_THIS(),evt) == PT_STATE_TERMINATED )
      {
         plist_erase(&process_running_list, PROCESS_THIS());
         /* broadcast exit to all ? */
      }

      PROCESS_CONTEXT_END();

      DBG_PROCESS("deliver_event success\n");
      return true;
   }

   DBG_PROCESS("deliver_event failure\n");
   return false;
}

bool process_post_sync(process_t *to, process_event_id_t evtid, void* data)
{
   process_event_t evt;
#if (MYOSCONF_PROC_EVENT_FROM== MYOSCONF_YES)
   evt.from = PROCESS_THIS();
#endif
   evt.to = to;
   evt.id = evtid;
   evt.data = data;

#if (MYOSCONF_PROC_EVENT_FROM == MYOSCONF_YES)
   DBG_PROCESS("post_sync from %p to %p evtid=%d ...\n",(void*)evt.from,(void*)evt.to,evt.id);
#else
   DBG_PROCESS("post_sync to %p evtid=%d ...\n",(void*)evt.to,evt.id);
#endif

   return process_deliver_event(&evt);
}

bool process_start(process_t *process, void* data)
{
   DBG_PROCESS("start %p ...\n",(void*)process);

   if( PROCESS_IS_RUNNING(process) )
   {
      DBG_PROCESS("start %p failure\n",(void*)process);
      return false;
   }

   process->data = data;
   PT_INIT(&process->pt);
   plist_push_front(&process_running_list, process);

   {
      process_event_t evt;

      evt.to = process;
#if (MYOSCONF_PROC_EVENT_FROM == MYOSCONF_YES)
      evt.from = PROCESS_THIS();
#endif
      evt.data = data;
      evt.id = PROCESS_EVENT_START;

      PROCESS_CONTEXT_BEGIN(evt.to);

      if ( PROCESS_THIS()->thread(PROCESS_THIS(),&evt) == PT_STATE_TERMINATED )
      {
         plist_erase(&process_running_list, PROCESS_THIS());
         /* broadcast exit to all ? */
      }

      PROCESS_CONTEXT_END();
   }

   DBG_PROCESS("start %p success\n",(void*)process);

   return true;
}

void process_poll(process_t *process)
{
   DBG_PROCESS("polling %p \n",(void*)process);
   process->pollreq = true;
   process_global_pollreq = true;
}


int process_run(void)
{
   /* Poll should only be triggered by interrupts. Interrupts always have a higher priority than the main loop context by definition.
      Thus we first handle all poll requests from interrupts first, before we deliver the next non polling event to a process. */
   while(process_global_pollreq)
   {
      process_t *process;

      CRITICAL_EXPRESSION(process_global_pollreq = false);

      plist_foreach(&process_running_list,process)
      {
         if( process->pollreq )
         {
            CRITICAL_EXPRESSION(process->pollreq = false);
            process_post_sync(process, PROCESS_EVENT_POLL, NULL);
         }
      }
   }


   if( RINGBUFFER_COUNT(process_event_queue) )
   {
      process_deliver_event(RINGBUFFER_HEAD_PTR(process_event_queue));
      RINGBUFFER_POP(process_event_queue);
   }

   return RINGBUFFER_COUNT(process_event_queue)+process_global_pollreq;
}

void process_init( process_t *process, process_thread_t thread )
{
   process->thread = thread;
   process->data = NULL;
   PT_INIT(&process->pt);
   process->pollreq = false;
}

