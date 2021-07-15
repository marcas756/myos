/*
 * rtimer_arch.h
 *
 *  Created on: 06.07.2021
 *      Author: marco
 */

#ifndef RTIMER_ARCH_H_
#define RTIMER_ARCH_H_

#include <stdint.h>


typedef uint16_t rtimer_arch_timestamp_t;
typedef rtimer_arch_timestamp_t rtimer_arch_timespan_t;

#define RTIMER_TIMESTAMP_ARCH_DIFF(a,b)         ((int16_t)((a)-(b)))
#define RTIMER_ARCH_TICKS_PER_SEC   (((rtimer_arch_timestamp_t)(~((rtimer_arch_timestamp_t)(0)))+1)/2)
rtimer_arch_timestamp_t rtimer_arch_now(void);
void rtimer_arch_timer_set(rtimer_arch_timestamp_t stop);
void rtimer_arch_module_init(void);





#endif /* RTIMER_ARCH_H_ */
