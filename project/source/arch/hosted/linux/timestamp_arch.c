/*
 * timestamp_arch.c
 *
 *  Created on: 27.06.2021
 *      Author: marco
 */

#include"timestamp_arch.h"

timestamp_arch_t timestamp_arch_now(void)
{
   struct timespec tim;
   timestamp_arch_t millisec;
   clock_gettime( CLOCK_MONOTONIC, &tim );
   millisec = TIMESTAMP_ARCH_TICKS_PER_SEC * tim.tv_sec + tim.tv_nsec / 1000000UL;
   return millisec;
}

