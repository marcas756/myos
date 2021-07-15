/*
 * init.c
 *
 *  Created on: 04.07.2021
 *      Author: marco
 */

#include "myos.h"

void myos_module_init(void)
{
    process_module_init();
    timestamp_module_init();
    timer_module_init();
    ptimer_module_init();
    ctimer_module_init();
}
