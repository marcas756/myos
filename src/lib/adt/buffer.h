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
    \def BUFFER_TYPEDEF(name,type,size)
    Declares a buffer type. The argumnents are \a name for a unique identification
    of the buffer type, the \a type of the items and the number of items of \a type
    the buffer can hold (\a size).
*/
#define BUFFER_TYPEDEF(name,type,size) \
    typedef struct { \
            size_t count; \
            type items [size]; \
    } name##_buffer_t;


/*!
    \def BUFFER_T(name)
    Defines a buffer of type \a name. Can also be used with different storage classifiers.
    (static, extern, volatile ...)
*/
#define BUFFER_T(name) \
    name##_buffer_t


/*!
    \def BUFFER_ITEMS(buffer)
    Returns a pointer to the buffer items.
    Type of returned pointer is of buffer item type.
*/
#define BUFFER_ITEMS(buffer) \
    ((buffer).items)

/*!
    \def BUFFER_RAW(buffer)
    Returns an pointer to the buffer items.
    Type of pointer is uint8_t (byte).
*/
#define BUFFER_RAW(buffer) \
	((uint8_t*)BUFFER_ITEMS(buffer))

/*!
    \def BUFFER_SIZEOF(buffer)
    Returns the size of the buffer in bytes.
*/
#define BUFFER_SIZEOF(buffer) \
    sizeof(BUFFER_ITEMS(buffer))


/*!
     \def BUFFER_SIZE(buffer)
     Returns the maximum number of items the buffer can hold.
*/
#define BUFFER_SIZE(buffer) \
    (BUFFER_SIZEOF(buffer)/sizeof(BUFFER_ITEMS(buffer)[0]))

/*!
    \def BUFFER_COUNT(buffer)
    Returns the current number of used items in the buffer.
*/
#define BUFFER_COUNT(buffer) \
    ((buffer).count)

/*!
    \def BUFFER_INIT(buffer)
    Initializes the buffer.
*/
#define BUFFER_INIT(buffer) \
    do{BUFFER_COUNT(buffer)=0;}while(0)

/*!
    \def BUFFER_CLEAR(buffer)
    Initializes the buffer and sets all bytes in the buffer to 0.
*/
#define BUFFER_CLEAR(buffer) \
    do { \
    	BUFFER_INIT(buffer); \
        memset(BUFFER_RAW(buffer),0,BUFFER_SIZEOF(buffer)); \
    } \
    while(0)

/*!
    \def BUFFER_COPY(destination,source)
    Copies source buffer to destination buffer.
    Source and destination buffer have to be of same type.
*/
#define BUFFER_COPY(destination,source) \
    do{(destination)=(source);}while(0)

/*!
    \def BUFFER_FULL(buffer)
    Checks if no further buffer items are available.
    Returns 1 if buffer is full, otherwise 0.
*/
#define BUFFER_FULL(buffer) \
    (BUFFER_COUNT(buffer)>=BUFFER_SIZE(buffer))

/*!
    \def BUFFER_EMPTY(buffer)
    Checks if the buffer has no items stored.
    Returns 1 if buffer is empty, otherwise 0.
*/
#define BUFFER_EMPTY(buffer) \
    (!BUFFER_COUNT(buffer))
/*!
    \def BUFFER_NEXT(buffer)
    Moves to next free item in the buffer.
    It does not check for buffer overflow.
    In case of buffer overflow the behaviour is undefined.
    Use BUFFER_FULL to check if buffer is full before using this macro.
*/
#define BUFFER_NEXT(buffer) \
    (++BUFFER_COUNT(buffer))

/*!
    \def BUFFER_VAL(buffer)
    Returns the current free item by value.
*/
#define BUFFER_VAL(buffer) \
    (BUFFER_ITEMS(buffer)[BUFFER_COUNT(buffer)])

/*!
    \def BUFFER_PTR(buffer)
    Returns a pointer to the current free item.
*/
#define BUFFER_PTR(buffer) \
    (&BUFFER_VAL(buffer))

/*!
    \def BUFFER_APPEND(buffer,item)
    Append an item to the buffer by value.
    Automatically increases the buffer count.
    It does not check for buffer overflow.
    In case of buffer overflow the behaviour is undefined.
    Use BUFFER_FULL to check if buffer is full before using this macro.
*/
#define BUFFER_APPEND(buffer,item) \
	do {BUFFER_VAL(buffer) = item; BUFFER_NEXT(buffer);}while(0)


#endif /* BUFFER_H_ */
