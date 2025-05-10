/*!
    Copyright (c) 2025, Marco Bacchi <marco@bacchi.at>

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software
       without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS”
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/*!
    \file GenericRingbuffer.h

    \brief Generic Ringbuffer (Queue) Implementation

    \details This file contains an abstract and generic implementation of a ringbuffer,
    also known as a circular queue, using preprocessor macros. The implementation
    is designed to be flexible and adaptable for various data types and sizes.
    It includes macros for defining ringbuffer types, initializing ringbuffers,
    and performing common operations such as adding, reading, and removing items.

    Ringbuffers in General:
    A ringbuffer, or circular queue, is a data structure that uses a single,
    fixed-size buffer as if it were connected end-to-end. This structure lends
    itself to situations where a buffer of constant size is used over and over,
    such as in buffering data streams, implementing queues for data processing,
    or handling communication data packets.

    In a ringbuffer, when the buffer fills up, new data overwrites the oldest data.
    This characteristic makes ringbuffers especially useful in scenarios where
    only the most recent data is of interest, like in logging systems or real-time
    data monitoring and processing.

    This implementation provides a generic way to define and manipulate ringbuffers
    using macros, making it versatile for a wide range of use cases. It allows users
    to define ringbuffers for different data types and sizes and includes necessary
    operations for managing ringbuffer data effectively.

    Usage:
    To use this implementation, include this header file in your project and utilize
    the provided macros to define and work with ringbuffers. Ensure to check
    ringbuffer constraints like fullness or emptiness before performing relevant
    operations.
*/


#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
#include <stdlib.h>


/*!
    \brief Declares a ringbuffer type.

    \details This macro is used to define a ringbuffer type with a specific name,
    item type, and size. It creates a struct that encapsulates the ringbuffer's
    state, including the head and tail indices, the current count of items,
    and an array to store the items.

    The 'head' index indicates the position of the oldest element in the buffer,
    while the 'tail' index points to the position where the next new item will be
    inserted. The 'count' keeps track of the total number of items currently in
    the buffer. The array 'items' holds the actual data of the specified 'type'.

    A ringbuffer is a circular data structure that uses a single, fixed-size buffer
    as if it were connected end-to-end. This structure is useful in situations
    where a buffer needs to be reused once it is filled, like in streaming data
    scenarios.

    \param name The unique identification name for the ringbuffer type. The actual type will be `name##_ringbuffer_t`.
    \param type The data type of the items that the ringbuffer will hold.
    \param size The number of items of \a type that the ringbuffer can hold.
*/
#define RINGBUFFER_TYPEDEF(name,type,size)  \
    typedef struct {                        \
        size_t head;                        \
        size_t tail;                        \
        size_t count;                       \
        type items [size];                  \
    } name##_ringbuffer_t


/*!
    \brief Defines a ringbuffer variable of a specified type.

    \details This macro is used to define a ringbuffer variable of the type created by
    `RINGBUFFER_TYPEDEF`. It simplifies the declaration of ringbuffer variables
    by using the type name defined through `RINGBUFFER_TYPEDEF`. The macro can
    be combined with different storage class specifiers such as static, extern,
    or volatile, to control the storage duration and linkage of the ringbuffer variable.

    The use of this macro ensures consistency in the declaration of ringbuffer
    variables and enhances code readability, especially when working with
    multiple ringbuffers of different types.

    \param name The unique identification name of the ringbuffer type, which corresponds to the name used in `RINGBUFFER_TYPEDEF`.
*/
#define RINGBUFFER_T(name) \
    name##_ringbuffer_t

/*!
    \brief Retrieves a pointer to the items array within a ringbuffer.

    \details This macro provides access to the items contained in a ringbuffer by returning
    a pointer to the first element of the ringbuffer's internal array. The type of
    the returned pointer matches the type of the items in the ringbuffer, as defined
    by the `RINGBUFFER_TYPEDEF` macro. This allows for direct access and manipulation
    of the ringbuffer's items.

    It is useful for operations that require iterating over the ringbuffer items or
    accessing them by index. Since the pointer is of the ringbuffer's item type, it
    ensures type safety and consistency in ringbuffer operations.

    \param ringbuffer The ringbuffer instance from which to retrieve the items pointer.
    \return A pointer of the ringbuffer's item type to the ringbuffer's internal items array.
*/
#define RINGBUFFER_ITEMS(ringbuffer) \
    ((ringbuffer).items)

/*!
    \brief Returns a raw (untyped) pointer to the ringbuffer items.

    \details This macro provides access to the internal items of the ringbuffer as
    a raw memory pointer. It casts the pointer to the ringbuffer's items to
    `uint8_t` (pointer to unsigned 8-bit integers), enabling operations
    on the ringbuffer's contents at the byte level. This can be useful for
    operations such as serialization, memory manipulation, or when interacting
    with APIs that require byte-level data access.

    The returned pointer points to the start of the ringbuffer's internal array,
    allowing direct access to its raw bytes. This should be used with caution,
    as it bypasses type safety provided by the ringbuffer's defined item type.

    \param ringbuffer The ringbuffer instance from which to retrieve the raw items pointer.
    \return A `uint8_t` pointer to the ringbuffer's internal items array.
*/
#define RINGBUFFER_RAW(ringbuffer) \
    ((uint8_t*)RINGBUFFER_ITEMS(ringbuffer))


/*!
    \brief Returns the total size of the ringbuffer's items in bytes.

    \details This macro calculates the total size of the ringbuffer's items array in bytes.
    It uses the `sizeof` operator on the ringbuffer's internal array to determine
    the total memory footprint of the ringbuffer's content. This size information
    is particularly useful for operations that require knowledge of the memory size,
    such as serialization, copying, or memory allocation.

    It is important to note that this macro provides the size of the entire items
    array within the ringbuffer, not the number of items currently stored or the
    number of free spaces available. The size in bytes is constant and determined by
    the declared capacity of the ringbuffer.

    \param ringbuffer The ringbuffer instance for which to determine the size in bytes.
    \return The total size of the ringbuffer's items array in bytes.
*/
#define RINGBUFFER_SIZEOF(ringbuffer) \
    (sizeof(RINGBUFFER_ITEMS(ringbuffer)))


/*!
    \brief Returns the maximum capacity of the ringbuffer.

    \details This macro calculates the maximum number of items that the ringbuffer can hold.
    It divides the total size of the ringbuffer's items array in bytes (obtained using
    `RINGBUFFER_SIZEOF(ringbuffer)`) by the size of a single item in the array.
    This calculation gives the total capacity of the ringbuffer, indicating how many items
    of the specified type the ringbuffer can store.

    This macro is useful for understanding the limits of the ringbuffer and ensuring
    that operations such as adding items do not exceed its capacity. It is
    particularly important in ringbuffer management logic, where the ringbuffer's capacity
    constraints must be respected to avoid overflows.

    \param ringbuffer The ringbuffer instance for which to determine the maximum capacity.
    \return The maximum number of items that the ringbuffer can hold.
*/
#define RINGBUFFER_SIZE(ringbuffer) \
    (RINGBUFFER_SIZEOF(ringbuffer)/sizeof(RINGBUFFER_ITEMS(ringbuffer)[0]))





/*!
    \brief Returns the current number of items in the ringbuffer.

    \details This macro retrieves the current count of items stored in the ringbuffer.
    The count is maintained within the ringbuffer structure and is updated
    as items are added (pushed) or removed (popped). This macro
    provides a direct way to access this count, which is crucial for understanding
    how many items are currently stored in the ringbuffer and for managing its content.

    The count value is essential for operations such as determining the
    available space in the ringbuffer or when iterating over its contents.
    It provides real-time information on the usage of the ringbuffer's capacity.

    \param ringbuffer The ringbuffer instance for which to determine the current item count.
    \return The number of items currently stored in the ringbuffer.
*/
#define RINGBUFFER_COUNT(ringbuffer) \
        ((ringbuffer).count)

/*!
    \brief Returns the current head index of the ringbuffer.

    \details This macro retrieves the index of the 'head' of the ringbuffer.
    The 'head' represents the position where the oldest element in the
    ringbuffer is located. This index is crucial in ringbuffer operations,
    particularly in scenarios involving reading or removing an item from
    the ringbuffer, as it indicates the starting point for these operations.

    In a ringbuffer, the 'head' index moves forward as items are removed
    (popped) from the buffer. It automatically wraps around to the beginning
    of the buffer when it reaches the end, maintaining the circular nature
    of the ringbuffer.

    \param ringbuffer The ringbuffer instance from which to retrieve the head index.
    \return The index of the 'head' in the ringbuffer.
*/
#define RINGBUFFER_HEAD(ringbuffer) \
    ((ringbuffer).head)

/*!
    \brief Returns the current tail index of the ringbuffer.

    \details This macro retrieves the index of the 'tail' of the ringbuffer.
    The 'tail' represents the position where the next new item will be
    inserted in the ringbuffer. This index is crucial for ringbuffer operations,
    especially for adding (pushing) new items, as it indicates where the new
    item should be placed.

    In a ringbuffer, the 'tail' index moves forward as new items are added
    to the buffer. It automatically wraps around to the beginning of the buffer
    when it reaches the end, ensuring the continuous circular nature of the
    ringbuffer.

    \param ringbuffer The ringbuffer instance from which to retrieve the tail index.
    \return The index of the 'tail' in the ringbuffer.
*/
#define RINGBUFFER_TAIL(ringbuffer) \
    ((ringbuffer).tail)

/*!
    \brief Initializes the ringbuffer.

    \details This macro initializes the specified ringbuffer by setting its head, tail,
    and count to zero. This operation is essential for setting the ringbuffer
    to a known starting state before any items are added or removed.
    Initializing the ringbuffer in this manner ensures that the head and tail
    indices are correctly aligned at the beginning, and the count accurately
    reflects an empty buffer.

    Proper initialization is crucial to avoid unpredictable behavior, especially
    in a ringbuffer where the positions of head and tail are integral to its
    functionality. This macro encapsulates the necessary steps for initialization
    into a single, convenient command.

    \param ringbuffer The ringbuffer instance to be initialized.
*/
#define RINGBUFFER_INIT(ringbuffer)     \
    do{                                 \
        RINGBUFFER_COUNT(ringbuffer)=0; \
        RINGBUFFER_HEAD(ringbuffer)=0;  \
        RINGBUFFER_TAIL(ringbuffer)=0;  \
    }while(0)

/*!
    \brief Returns a reference to the current tail item in the ringbuffer.

    \details This macro provides access to the item at the 'tail' position in the
    ringbuffer. The 'tail' position is where the next new item will be
    added to the ringbuffer. This macro is typically used for directly
    reading or writing the value of the item at the tail position.

    The returned reference can be used to modify the tail item before
    it is officially added (pushed) into the ringbuffer. It is important
    to ensure that the ringbuffer is not full before using this macro
    to write a new item, as doing so when the ringbuffer is full could
    lead to an unintentional overwrite of existing data.

    \param ringbuffer The ringbuffer instance from which to retrieve the current tail item.
    \return A reference to the item at the current tail position in the ringbuffer.
*/
#define RINGBUFFER_TAIL_VAL(ringbuffer) \
    (RINGBUFFER_ITEMS(ringbuffer)[RINGBUFFER_TAIL(ringbuffer)])

/*!
    \brief Returns a pointer to the current tail item in the ringbuffer.

    \details This macro provides a pointer to the item at the 'tail' position of
    the ringbuffer. The tail is where the next new item will be added.
    This macro is particularly useful for directly manipulating the item
    at the tail position, such as modifying its value before it is
    officially pushed into the ringbuffer.

    The returned pointer allows for more complex operations on the tail
    item, like modifying its fields if it is a struct. As with
    `RINGBUFFER_TAIL_VAL`, it is important to ensure that the ringbuffer
    is not full before using this macro to write a new item, to avoid
    unintended overwrites.

    \param ringbuffer The ringbuffer instance from which to retrieve a pointer to the current tail item.
    \return A pointer to the item at the current tail position in the ringbuffer.
*/
#define RINGBUFFER_TAIL_PTR(ringbuffer) \
    (&RINGBUFFER_TAIL_VAL(ringbuffer))


/*!
    \brief Returns a reference to the current head item in the ringbuffer.

    \details This macro provides access to the item at the 'head' position in the
    ringbuffer. The 'head' position is where the oldest item in the buffer is located.
    This macro is commonly used for reading the value of the head item,
    typically in scenarios where you need to process or examine the oldest item
    in the ringbuffer.

    The reference returned by this macro can be used to directly access or
    modify the head item. However, any modification should be done with caution
    as it directly affects the data within the buffer. Typically, the head item
    is read or removed (popped) rather than modified in place.

    \param ringbuffer The ringbuffer instance from which to retrieve the current head item.
    \return A reference to the item at the current head position in the ringbuffer.
*/
#define RINGBUFFER_HEAD_VAL(ringbuffer) \
    (RINGBUFFER_ITEMS(ringbuffer)[RINGBUFFER_HEAD(ringbuffer)])

/*!
    \brief Returns a pointer to the current head item in the ringbuffer.

    \details This macro provides a pointer to the item at the 'head' position of
    the ringbuffer. The head is where the oldest item in the buffer is located.
    This pointer can be used for direct manipulation or inspection of the head item.
    It is particularly useful when the item is a complex data type, such as a struct,
    and you need to access its members.

    While this provides direct access to the head item, caution should be exercised
    when modifying its content, as it affects the data structure's integrity. Typically,
    head items are read or removed (popped) rather than modified in place.

    \param ringbuffer The ringbuffer instance from which to retrieve a pointer to the current head item.
    \return A pointer to the item at the current head position in the ringbuffer.
*/
#define RINGBUFFER_HEAD_PTR(ringbuffer) \
    (&RINGBUFFER_HEAD_VAL(ringbuffer))

/*!
    \brief Pushes the current tail item in the ringbuffer.

    \details This macro increases the tail index to move to the next position in
    the ringbuffer, effectively 'pushing' the current tail item into the
    buffer. It automatically wraps around the tail index if it reaches the
    end of the buffer, maintaining the circular nature of the ringbuffer.
    The macro also increments the count of items in the ringbuffer by one.

    The 'push' operation is typically used after setting a value at the
    ringbuffer's tail position. This macro ensures the tail index is
    correctly updated and keeps the count of items in sync. The automatic
    wrap-around at the end of the buffer is a key feature of the ringbuffer,
    allowing continuous use without needing to manually reset indices.

    It's important to check if the ringbuffer is full before performing a
    push operation to prevent overwriting existing items inadvertently.

    \param ringbuffer The ringbuffer instance in which to push the current tail item.
*/
#define RINGBUFFER_PUSH(ringbuffer)                                         \
    do {                                                                    \
        if(++RINGBUFFER_TAIL(ringbuffer) == RINGBUFFER_SIZE(ringbuffer))    \
        {                                                                   \
             RINGBUFFER_TAIL(ringbuffer) = 0;                               \
        }                                                                   \
                                                                            \
        RINGBUFFER_COUNT(ringbuffer)++;                                     \
    }while (0)


/*!
    \brief Pops the current head item in the ringbuffer.

    \details This macro increases the head index to move to the next position in
    the ringbuffer, effectively 'popping' the current head item out of the
    buffer. It automatically wraps around the head index if it reaches the
    end of the buffer, thus maintaining the circular nature of the ringbuffer.
    Additionally, this macro decrements the count of items in the ringbuffer by one.

    The 'pop' operation is typically used to remove or process the oldest item
    in the ringbuffer. By advancing the head index and adjusting the item count,
    this macro ensures that the ringbuffer's state accurately reflects the removal
    of an item. The automatic wrap-around at the end of the buffer enables continuous
    operation without manual index resetting.

    Ensure that the ringbuffer is not empty before performing a pop operation to avoid
    underflow or accessing uninitialized data.

    \param ringbuffer The ringbuffer instance from which to pop the current head item.
*/
#define RINGBUFFER_POP(ringbuffer)                                          \
    do {                                                                    \
        if(++RINGBUFFER_HEAD(ringbuffer) == RINGBUFFER_SIZE(ringbuffer))    \
        {                                                                   \
             RINGBUFFER_HEAD(ringbuffer) = 0;                               \
        }                                                                   \
                                                                            \
        RINGBUFFER_COUNT(ringbuffer)--;                                     \
    }while (0)

/*!
    \brief Checks if the ringbuffer is full.

    \details This macro determines whether the ringbuffer has reached its maximum capacity
    for storing items. It compares the current count of items in the ringbuffer
    (obtained via `RINGBUFFER_COUNT(ringbuffer)`) with the ringbuffer's total
    capacity (obtained via `RINGBUFFER_SIZE(ringbuffer)`). If the count is greater
    than or equal to the capacity, the ringbuffer is considered full, and the macro
    returns 1, indicating no further items can be added without overwriting existing
    data. Otherwise, it returns 0.

    Checking if the ringbuffer is full is crucial before performing add (push)
    operations. This check helps prevent overwriting existing items and ensures
    data integrity within the ringbuffer.

    \param ringbuffer The ringbuffer instance to check for fullness.
    \return 1 if the ringbuffer is full, 0 otherwise.
*/
#define RINGBUFFER_FULL(ringbuffer) \
    (RINGBUFFER_COUNT(ringbuffer)>=RINGBUFFER_SIZE(ringbuffer))


/*!
    \brief Checks if the ringbuffer is empty.

    \details This macro determines whether the ringbuffer currently contains no items.
    It evaluates the current count of items in the ringbuffer (using
    `RINGBUFFER_COUNT(ringbuffer)`) and returns 1 (true) if the count is zero,
    indicating that the ringbuffer is empty. If the ringbuffer contains one or
    more items, it returns 0 (false).

    This check is useful for operations that require knowledge of whether the
    ringbuffer has any data in it, such as avoiding underflows when attempting
    to remove or process items from the ringbuffer. Using this macro ensures
    safe and efficient ringbuffer management by providing a clear and concise
    check for the ringbuffer's emptiness.

    \param ringbuffer The ringbuffer instance to check for emptiness.
    \return 1 if the ringbuffer is empty, 0 otherwise.
*/
#define RINGBUFFER_EMPTY(ringbuffer) \
    (!RINGBUFFER_COUNT(ringbuffer))


/*!
    \brief Reads one item from the ringbuffer into a variable.

    \details This macro is used to read the oldest item (the item at the head position)
    from the ringbuffer into a specified variable. It first assigns the value
    of the head item to the given variable and then automatically pops the
    ringbuffer to remove that item and advance the head index.

    It is essential for the application to ensure that the ringbuffer is not
    empty before using this macro, as attempting to read from an empty ringbuffer
    could result in undefined behavior. The application should check the ringbuffer's
    status using `RINGBUFFER_EMPTY(ringbufferptr)` prior to reading.

    This macro provides a convenient way to both read and remove an item from
    the ringbuffer in a single operation, making it particularly useful in
    scenarios like processing queues where items are consumed and then discarded.

    \param ringbufferptr Pointer to the ringbuffer instance from which to read the item.
    \param var The variable into which the head item's value will be read.
*/
#define RINGBUFFER_READ(ringbufferptr,var)          \
    do {                                            \
        var = RINGBUFFER_HEAD_VAL(ringbufferptr);   \
        RINGBUFFER_POP(ringbufferptr);              \
    }while(0)

/*!
    \brief Writes one item into the ringbuffer.

    \details This macro is used to write a given item into the ringbuffer. It first sets
    the value at the ringbuffer's tail position to the provided value and then
    automatically pushes the ringbuffer to advance the tail index. If the
    ringbuffer is full, this operation will overwrite the oldest element.

    The application has the option to check if the ringbuffer is full using
    `RINGBUFFER_FULL(ringbufferptr)` before performing the write operation. This
    check allows the application to decide whether to overwrite existing data
    or to take some other action, such as expanding the buffer or discarding
    the new data.

    This macro simplifies the process of adding new items to the ringbuffer,
    ensuring the ringbuffer's state is correctly updated after each insertion.
    The automatic handling of overwrites when full is a characteristic behavior
    of ringbuffers, particularly useful in scenarios like logging where newer
    data is more critical than older data.

    \param ringbufferptr Pointer to the ringbuffer instance into which the item will be written.
    \param value The value to write into the ringbuffer.
*/
#define RINGBUFFER_WRITE(ringbufferptr,value)           \
    do {                                                \
        RINGBUFFER_TAIL_VAL(ringbufferptr) = value;     \
        RINGBUFFER_PUSH(ringbufferptr);                 \
    }while(0)


#endif /* RINGBUFFER_H_ */
