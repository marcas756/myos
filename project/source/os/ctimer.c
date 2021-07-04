/*
 * ctimer.c
 *
 *  Created on: 22.06.2021
 *      Author: marco
 */


#include <ctimer.h>

/*!
    \brief      Callback timer handler used by process timer

    \param      data    Current node

    \return     Precessor of current node
*/
void ctimer_timeout_handler(ptimer_t* ptimer)
{
   ctimer_t *ctimer = (ctimer_t*)ptimer;

   if( ctimer->callback )
   {
      PROCESS_CONTEXT_BEGIN(ctimer->context);
      ctimer->callback(ctimer->data);
      PROCESS_CONTEXT_END();
   }
}



void ctimer_start(ctimer_t *ctimer, timespan_t span, ctimer_callback_t callback, void *data)
{
   ctimer->callback = callback;
   ctimer->data = data;
   ctimer->context = PROCESS_THIS();
   ptimer_start(&(ctimer->ptimer), span, ctimer_timeout_handler);
}





