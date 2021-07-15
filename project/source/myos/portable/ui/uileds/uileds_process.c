/*
 * uileds_process.c
 *
 *  Created on: Jul 14, 2021
 *      Author: marco
 */

#include "myos.h"
#include "uileds_process.h"


PROCESS(uileds_process,uileds_process);
PROCESS_THREAD(uileds_process)
{
    static etimer_t et;

    PROCESS_BEGIN();

    etimer_start(&et, TIMESTAMP_TICKS_PER_SEC/50, PROCESS_THIS(), PROCESS_EVENT_TIMEOUT, NULL);

    while(1)
    {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

        do{
            uileds_handler();
            etimer_reset(&et);
        }while(etimer_expired(&et));
    }

    PROCESS_END();
}

void uileds_process_module_init(void)
{
    process_start(&uileds_process,NULL);
}
