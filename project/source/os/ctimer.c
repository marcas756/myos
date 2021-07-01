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

   if( ctimer->callback )
   {
      PROCESS_CONTEXT_BEGIN(ctimer->context);
      ctimer->callback(ctimer);
      PROCESS_CONTEXT_END();
   }
}


void ctimer_module_init(void)
{
   ptimer_module_init();
}

void ctimer_start(ctimer_t *ctimer, timespan_t span, ctimer_callback_t callback, void *data)
{
   ctimer->callback = callback;
   ctimer->data = data;
   ctimer->context = PROCESS_THIS();
   ptimer_start(&(ctimer->ptimer), span, ctimer_timeout_handler);
}





