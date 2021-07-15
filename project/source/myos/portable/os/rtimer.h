/*
 * rtimer.h
 *
 *  Created on: 03.07.2021
 *      Author: marco
 */

#ifndef RTIMER_H_
#define RTIMER_H_


#include "myos.h"
#include "rtimer_arch.h"


typedef rtimer_arch_timestamp_t rtimer_timestamp_t;
typedef rtimer_timestamp_t rtimer_timespan_t;

#define RTIMER_TICKS_PER_SEC                RTIMER_ARCH_TICKS_PER_SEC
#define rtimer_now()                        rtimer_arch_now()
#define RTIMER_TIMESTAMP_DIFF               RTIMER_TIMESTAMP_ARCH_DIFF
#define rtimer_timestamp_less_than(a,b)    (RTIMER_TIMESTAMP_DIFF((a),(b)) < 0)
typedef void(*rtimer_callback_t)(void* data);

typedef struct {
   rtimer_timestamp_t start;
   rtimer_timespan_t span;
   rtimer_callback_t callback;
   void* data;
} rtimer_t;





#define PROCESS_RTIMER_OBTAIN() \
   do{ \
      while(!rtimer_lock()) \
      { \
         PROCESS_SUSPEND(); \
      } \
   }while(0)




void rtimer_start(rtimer_t *rtimer, rtimer_timespan_t span, rtimer_callback_t callback, void* data);
void rtimer_reset(rtimer_t *rtimer);
rtimer_timespan_t rtimer_left(rtimer_t *rtimer);
#define rtimer_expired(rtimerptr) (rtimer_left(rtimerptr) == 0)
#define rtimer_timestamp_stop(rtimerptr) ((rtimerptr)->start+(rtimerptr)->span)
bool rtimer_lock(void);

#define  rtimer_module_init  rtimer_arch_module_init

#endif /* SOURCE_OS_RTIMER_H_ */
