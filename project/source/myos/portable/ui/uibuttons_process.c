/*
 * uibuttons_process.c
 *
 *  Created on: Jul 15, 2021
 *      Author: marco
 */

#include"myos.h"
#include "uibuttons_process.h"

extern uibutton_t uibuttons[];
extern const int uibuttons_count;

PROCESS(uibuttons_process,uibuttons_process);
PROCESS_THREAD(uibuttons_process)
{
    static etimer_t et;

    PROCESS_BEGIN();

    UIBUTTONS_INIT_ALL();

    etimer_start(&et, TIMESTAMP_TICKS_PER_SEC/50, PROCESS_THIS(), PROCESS_EVENT_TIMEOUT, NULL);

    while(1)
    {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

        do{
        	UIBUTTONS_POLL_ALL();
            etimer_reset(&et);
        }while(etimer_expired(&et));
    }

    PROCESS_END();
}





void uibuttons_process_module_init(void)
{
    process_start(&uibuttons_process,NULL);
}
