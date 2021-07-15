/*
 * timestamp_arch.c
 *
 *  Created on: 27.06.2021
 *      Author: marco
 */

#include"timestamp_arch.h"
#include "main.h"

extern void ptimer_poll_if_necessary(void);

volatile timestamp_arch_t timestamp_arch_counter = 0;

void SysTick_Handler(void)
{
  HAL_IncTick();
  timestamp_arch_counter++;
  ptimer_poll_if_necessary();
}

timestamp_arch_t timestamp_arch_now(void)
{
    timestamp_arch_t t1,t2;

    do {
        t1 = timestamp_arch_counter;
        t2 = timestamp_arch_counter;
    } while( t1 != t2 );

    return t1;
}

