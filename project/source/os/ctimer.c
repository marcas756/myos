/*
 * ctimer.c
 *
 *  Created on: 22.06.2021
 *      Author: marco
 */


#include <ctimer.h>


void ctimer_timeout_handler(void* data)
{
   ctimer_t *ctimer = data;

   PROCESS_CONTEXT_BEGIN(ctimer->context);

   if( ctimer->callback )
   {
      ctimer->callback(ctimer->data);
   }

   PROCESS_CONTEXT_END();
}


void ctimer_module_init()
{
   ptimer_module_init();
}

bool ctimer_start(ctimer_t *ctimer, timespan_t span, ctimer_callback_t callback, void *data)
{
   ptimer_t *ptimer = &(ctimer->ptimer);

   if( ptimer_is_running(ptimer) )
   {
      return false;
   }

   ctimer->callback = callback;
   ctimer->data = data;
   ctimer->context = PROCESS_THIS();

   ptimer_start(ptimer, span, ctimer_timeout_handler);

   return true;
}

