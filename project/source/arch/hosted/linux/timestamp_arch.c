/*
 * timestamp_arch.c
 *
 *  Created on: 27.06.2021
 *      Author: marco
 */

#include"timestamp_arch.h"

timestamp_t timestamp_now(void)
{
   struct timespec tim;
   timestamp_t millisec;
   clock_gettime( CLOCK_MONOTONIC, &tim );
   millisec = TICKS_PER_SEC * tim.tv_sec + tim.tv_nsec / 1000000;
   return millisec;
}


bool timestamp_module_init(void)
{
  return true;
}



