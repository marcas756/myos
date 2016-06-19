/*! \copyright
    Copyright (c) 2013, marcas756@gmail.com.
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
	\file	ringbuffer.h

	\brief

	\details
*/



#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include "buffer.h"

/*!
    Declares a ringbuffer type. The argumnents are \a name for a unique identification
    of the ringbuffer type, the \a type of the items and the number of items of \a type
    the ringbuffer can hold (\a size).
*/
#define RINGBUFFER_TYPEDEF(name,type,size)  \
    BUFFER_TYPEDEF(name,type,size);         \
    typedef struct {                        \
        size_t head;                        \
        size_t tail;                        \
        BUFFER_T(name) buffer;              \
    } name##_ringbuffer_t


/*!
    Defines a ringbuffer of type \a name. Can also be used with different storage classifiers.
    (static, extern, volatile ...)
*/
#define RINGBUFFER_T(name) \
    name##_ringbuffer_t

/*!
    Returns a pointer to the ringbuffer items.
    Type of returned pointer is of ringbuffer item type.
*/
#define RINGBUFFER_ITEMS(ringbufferptr) \
    BUFFER_ITEMS(&((ringbufferptr)->buffer))

/*!
    Returns an pointer to the ringbuffer items.
    Type of pointer is uint8_t (byte).
*/
#define RINGBUFFER_RAW(ringbufferptr) \
    BUFFER_RAW(&((ringbufferptr)->buffer))

/*!
    Returns the maximum number of items the ringbuffer can hold.
*/
#define RINGBUFFER_SIZE(ringbufferptr) \
        BUFFER_SIZE(&((ringbufferptr)->buffer))

/*!
    Returns the size of the ringbuffer in bytes.
*/
#define RINGBUFFER_SIZEOF(ringbufferptr) \
    BUFFER_SIZEOF(&((ringbufferptr)->buffer))


/*!
    Returns the current number of used items in the ringbuffer.
*/
#define RINGBUFFER_COUNT(ringbufferptr) \
    BUFFER_COUNT(&((ringbufferptr)->buffer))

/*!
    Returns the current head index.
*/
#define RINGBUFFER_HEAD(ringbufferptr) \
    ((ringbufferptr)->head)

/*!
    Returns the current tail index.
*/
#define RINGBUFFER_TAIL(ringbufferptr) \
    ((ringbufferptr)->tail)

/*!
    Initializes the ringbuffer.
*/
#define RINGBUFFER_INIT(ringbufferptr)      \
    do{                                     \
        RINGBUFFER_COUNT(ringbufferptr)=0;  \
        RINGBUFFER_HEAD(ringbufferptr)=0;   \
        RINGBUFFER_TAIL(ringbufferptr)=0;   \
    }while(0)

/*!
    Returns a reference of the current tail item.
*/
#define RINGBUFFER_TAIL_VAL(ringbufferptr) \
    (RINGBUFFER_ITEMS(ringbufferptr)[RINGBUFFER_TAIL(ringbufferptr)])

/*!
    Returns a pointer to the current tail item.
*/
#define RINGBUFFER_TAIL_PTR(ringbufferptr) \
    (&RINGBUFFER_TAIL_VAL(ringbufferptr))

/*!
    Returns a reference of the current head item.
*/
#define RINGBUFFER_HEAD_VAL(ringbufferptr) \
    (RINGBUFFER_ITEMS(ringbufferptr)[RINGBUFFER_HEAD(ringbufferptr)])

/*!
    Returns a pointer to the current head item.
*/
#define RINGBUFFER_HEAD_PTR(ringbufferptr) \
    (&RINGBUFFER_HEAD_VAL(ringbufferptr))

/*!
    Pushes the current tail item in the ringbuffer, or in other words: increases
    the tail index to address the next item in the ringbuffer. Automatically wraps
    around the tail index in case of index overflow. Also increases the number of items
    in the ringbuffer by one.
*/
#define RINGBUFFER_PUSH(ringbufferptr)                                              \
    do {                                                                            \
        if(++RINGBUFFER_TAIL(ringbufferptr) == RINGBUFFER_SIZE(ringbufferptr))      \
        {                                                                           \
             RINGBUFFER_TAIL(ringbufferptr) = 0;                                    \
        }                                                                           \
                                                                                    \
        RINGBUFFER_COUNT(ringbufferptr)++;                                          \
    }while (0)


/*!
    Pops the current head item in the ringbuffer, or in other words: increases
    the head index to address the next item in the ringbuffer. Automatically wraps
    around the head index in case of index overflow. Also decreases the number of items
    in the ringbuffer by one.
*/
#define RINGBUFFER_POP(ringbufferptr)                                               \
    do {                                                                            \
        if(++RINGBUFFER_HEAD(ringbufferptr) == RINGBUFFER_SIZE(ringbufferptr))      \
        {                                                                           \
             RINGBUFFER_HEAD(ringbufferptr) = 0;                                    \
        }                                                                           \
                                                                                    \
        RINGBUFFER_COUNT(ringbufferptr)--;                                          \
    }while (0)

/*!
    Checks if no further ringbuffer items are available.
    Returns 1 if ringbuffer is full, otherwise 0.
*/
#define RINGBUFFER_FULL(ringbufferptr) \
    BUFFER_FULL(&((ringbufferptr)->buffer))

/*!
    Checks if the ringbuffer has no items stored.
    Returns 1 if ringbuffer is empty, otherwise 0.
*/
#define RINGBUFFER_EMPTY(ringbufferptr) \
    BUFFER_EMPTY(&((ringbufferptr)->buffer))

/*!
    Reads one item into /a var by value. Automatically
    pops the ringbuffer. Read oldest element. App must ensure
    !RINGBUFFER_EMPTY() first.
*/
#define RINGBUFFER_READ(ringbufferptr,var)          \
    do {                                            \
        var = RINGBUFFER_HEAD_VAL(ringbufferptr);   \
        RINGBUFFER_POP(ringbufferptr);              \
    }while(0)
/*!
    Writes one item into ringbuffer by value.
    Automatically pushes the ringbuffer.
    Overwrites the oldest element if ringbuffer is full. App can
    choose to avoid the overwrite by checking RINGBUFFER_FULL().
*/
#define RINGBUFFER_WRITE(ringbufferptr,value)           \
    do {                                                \
        RINGBUFFER_TAIL_VAL(ringbufferptr) = value;     \
        RINGBUFFER_PUSH(ringbufferptr);                 \
    }while(0)


#endif /* RINGBUFFER_H_ */
