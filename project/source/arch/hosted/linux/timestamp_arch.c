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
   timestamp_t microsec;
   clock_gettime( CLOCK_MONOTONIC, &tim );
   microsec = 1000000ULL * tim.tv_sec + tim.tv_nsec / 1000;
   return microsec;
}

bool timestamp_init(void)
{

}



