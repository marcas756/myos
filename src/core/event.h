/*! \copyright
    Copyright (c) 2014, marcas756@gmail.com.
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. The name of the author may not be used to endorse or promote
       products derived from this software without specific prior
       written permission.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
    GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/*!
    \file   event.h

    \brief

    \details
*/
#ifndef EVENT_H_
#define EVENT_H_

#include <stdint.h>
#include <stdbool.h>

#include "oz_conf.h"
#include "ringbuffer.h"


#ifdef OZCONF_EVENT_QUEUE_SIZE
    #define EVENT_QUEUE_SIZE OZCONF_EVENT_QUEUE_SIZE
#else
    #define EVENT_QUEUE_SIZE 8
#endif

#ifdef OZCONF_EVENT_ID_TYPE
    typedef OZCONF_EVENT_ID_TYPE event_id_t;
#else
    typedef uint8_t event_id_t;
#endif


enum {
    EVENT_OZ_BROADCAST      = 0x7F,
    EVENT_APP_BASE          = 0x80
};


typedef struct {
    void* target;           //!< Target the event is meant for
    void* source;           //!< Source that raised the event. Thus the target is able to send an response event back to the source.
    void* data;             //!< Additional data associated with the event
    event_id_t event_id;    //!< Event id number to enable source/target to distinguish different events
}event_t;

RINGBUFFER_TYPEDEF(event_queue, event_t, EVENT_QUEUE_SIZE);
extern RINGBUFFER_T(event_queue) event_queue;

bool event_enqueue(void *target, void *source, event_id_t event_id, void *data);

#define event_check()   (RINGBUFFER_COUNT(event_queue))
#define event_receive() RINGBUFFER_TAIL_PTR(event_queue)
#define event_dequeue() RINGBUFFER_POP(event_queue)




#endif /* EVENT_H_ */
