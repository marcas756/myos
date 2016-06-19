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
	\file	buffer.h

    \brief

    \details
*/

#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>
#include <stddef.h>
#include <string.h>


/*!
    Declares a buffer type. The argumnents are \a name for a unique identification
    of the buffer type, the \a type of the items and the number of items of \a type
    the buffer can hold (\a size).
*/
#define BUFFER_TYPEDEF(name,type,size)  \
    typedef struct {                    \
            size_t count;               \
            type items [size];          \
    } name##_buffer_t


/*!
     Defines a buffer of type \a name. Can also be combined with different storage classifiers.
    (static, extern, volatile ...)
*/
#define BUFFER_T(name) \
    name##_buffer_t


/*!
    Returns a pointer to the buffer items.
    Type of returned pointer is of buffer item type.
*/
#define BUFFER_ITEMS(bufferptr) \
    ((bufferptr)->items)

/*!
    Returns an pointer to the buffer items.
    Type of pointer is uint8_t (byte).
*/
#define BUFFER_RAW(bufferptr) \
	((uint8_t*)BUFFER_ITEMS(bufferptr))

/*!
    Returns the size of the buffer in bytes.
*/
#define BUFFER_SIZEOF(bufferptr) \
    (sizeof(BUFFER_ITEMS(bufferptr)))


/*!
     Returns the maximum number of items the buffer can hold.
*/
#define BUFFER_SIZE(bufferptr) \
    (BUFFER_SIZEOF(bufferptr)/sizeof(*BUFFER_ITEMS(bufferptr)))

/*!
    Returns the current number of items used in the buffer.
*/
#define BUFFER_COUNT(bufferptr) \
    ((bufferptr)->count)

/*!
    Initializes the buffer.
*/
#define BUFFER_INIT(bufferptr) \
    do{BUFFER_COUNT(bufferptr)=0;}while(0)

/*!
    Initializes the buffer and sets all bytes in the buffer to 0.
*/
#define BUFFER_CLEAR(bufferptr)                                     \
    do {                                                            \
    	BUFFER_INIT(bufferptr);                                     \
        memset(BUFFER_RAW(bufferptr),0,BUFFER_SIZEOF(bufferptr));   \
    }                                                               \
    while(0)

/*!
    Copies source buffer to destination buffer.
    Source and destination buffer have to be of same type.
*/
#define BUFFER_COPY(destinationptr,sourceptr) \
    do{*(destinationptr)=*(sourceptr);}while(0)

/*!
    Checks if no further buffer items are available.
    Returns 1 if buffer is full, otherwise 0.
*/
#define BUFFER_FULL(bufferptr) \
    (BUFFER_COUNT(bufferptr)>=BUFFER_SIZE(bufferptr))

/*!
    Checks if the buffer has no items stored.
    Returns 1 if buffer is empty, otherwise 0.
*/
#define BUFFER_EMPTY(bufferptr) \
    (!BUFFER_COUNT(bufferptr))
/*!
    Moves to next free item in the buffer.
    It does not check for buffer overflow.
    In case of buffer overflow the behaviour is undefined.
    Use BUFFER_FULL to check if buffer is full before using this macro.
*/
#define BUFFER_NEXT(bufferptr) \
    (++BUFFER_COUNT(bufferptr))

/*!
    Returns the current free item by value.
*/
#define BUFFER_VAL(bufferptr) \
    (BUFFER_ITEMS(bufferptr)[BUFFER_COUNT(bufferptr)])

/*!
    Returns a pointer to the current free item.
*/
#define BUFFER_PTR(bufferptr) \
    (&BUFFER_VAL(bufferptr))

/*!
    Append an item to the buffer by value.
    Automatically increases the buffer count.
    It does not check for buffer overflow.
    In case of buffer overflow the behaviour is undefined.
    Use BUFFER_FULL to check if buffer is full before using this macro.
*/
#define BUFFER_APPEND(bufferptr,item) \
	do {BUFFER_VAL(bufferptr) = item; BUFFER_NEXT(bufferptr);}while(0)


#endif /* BUFFER_H_ */
