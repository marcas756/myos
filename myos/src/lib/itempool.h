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
    \file itempool.h

    \brief Provides utilities for managing a pool of pre-allocated items.

    \details This file contains macros and functions to manage an array of
             pre-allocated memory blocks, referred to as an "item pool". The
             purpose is to efficiently allocate and free items without the overhead
             of dynamic memory allocation. It includes functionalities to initialize
             item pools, allocate zero-initialized items, check item statuses,
             deallocate items, and reset the entire pool.
*/
#ifndef ITEMPOOL_H_
#define ITEMPOOL_H_

#include <stdint.h>
#include <stddef.h>
#include <string.h>


#define ITEMPOOL_ITEM_FREE 0
#define ITEMPOOL_ITEM_USED 1


/*!
    \brief Defines a new item pool type.

    This macro allows the creation of an item pool structure, which facilitates
    efficient management and allocation of a fixed number of pre-allocated items.

    \param name The base name used to construct the names of the new types and variables.
    \param type The data type of each individual item in the pool.
    \param size The total number of items that the pool can hold.
*/
#define ITEMPOOL_TYPEDEF(name,type,size) \
    typedef struct { \
        uint8_t status[size]; \
        type items[size]; \
    }name##_itempool_t


/*!
    \brief Simplified macro to use a predefined item pool type.

    This macro provides a convenient way to define an instance of an already
    defined item pool structure without redefining the entire typedef. It assumes
    that the `ITEMPOOL_TYPEDEF` has been used previously with the same name.

    \param name The base name as specified in the `ITEMPOOL_TYPEDEF`.
*/
#define ITEMPOOL_T(name) \
    name##_itempool_t

/*!
    \brief Initializes the status array of an item pool.

    This macro sets all elements in the `status` array of the specified
    item pool to indicate that they are free. It uses the `memset` function
    to fill the entire status array with `ITEMPOOL_ITEM_FREE`.

    \param itempool The variable representing an instance of the item pool.
                    This should be a struct that includes both a status and items
                    arrays as defined by the corresponding `ITEMPOOL_TYPEDEF`.
*/
#define ITEMPOOL_INIT(itempool) \
        memset(ITEMPOOL_STATUS(itempool), \
               ITEMPOOL_ITEM_FREE, \
               ITEMPOOL_SIZE(itempool))
/*!
    \brief Calculates the number of items in the given item pool.

    This macro computes the size of the `status` array within the specified
    item pool. It determines how many individual items are managed by dividing
    the total size of the status array by the size of one status element, which
    is typically a byte representing an item's allocation state (either free or used).

    \param itempool The variable representing an instance of the item pool.
                    This should be a struct that includes a `status` array as
                    defined by the corresponding `ITEMPOOL_TYPEDEF`.
*/
#define ITEMPOOL_SIZE(itempool) \
    (sizeof(ITEMPOOL_STATUS(itempool))/ \
     sizeof(*ITEMPOOL_STATUS(itempool)))

/*!
    \brief Determines the size of each individual item in bytes within the given item pool.

    This macro calculates the size, in bytes, of a single item managed by
    the specified item pool. It does this by taking the size of one element
    from the `items` array of the item pool structure, allowing you to understand
    how much memory each item occupies when allocated or deallocated.

    \param itempool The variable representing an instance of the item pool.
                    This should be a struct that includes an `items` array as
                    defined by the corresponding `ITEMPOOL_TYPEDEF`.
*/
#define ITEMPOOL_ITEM_SIZE(itempool) \
    (sizeof(*ITEMPOOL_ITEMS(itempool)))

/*!
    \brief Accesses the status array of the specified item pool.

    This macro retrieves a pointer to the `status` array within the given
    item pool. The `status` array is used to keep track of which items in
    the pool are currently free or used, allowing efficient management of memory
    allocation and deallocation operations. Each element in this status array typically
    represents an individual item's state (e.g., free or used).

    \param itempool The variable representing an instance of the item pool.
                    This should be a struct that includes a `status` array as
                    defined by the corresponding `ITEMPOOL_TYPEDEF`.
*/
#define ITEMPOOL_STATUS(itempool) \
        ((itempool).status)

/*!
    \brief Accesses the items array of the specified item pool.

    This macro retrieves a pointer to the `items` array within the given
    item pool. The `items` array holds all the actual data or objects that
    are being managed by the item pool, allowing dynamic allocation and deallocation
    while maintaining an organized structure for efficient memory management.

    \param itempool The variable representing an instance of the item pool.
                    This should be a struct that includes an `items` array as
                    defined by the corresponding `ITEMPOOL_TYPEDEF`.
*/
#define ITEMPOOL_ITEMS(itempool) \
        ((itempool).items)

/*!
    \brief Allocates an item from the specified item pool.

    This macro uses the `itempool_alloc` function to allocate a single
    item from the given item pool. It sets up the necessary parameters for
    calling `itempool_alloc`, including pointers to the items and status arrays,
    the size of each individual item, and the total number of items in the pool.

    \param itempool The variable representing an instance of the item pool.
                    This should be a struct that includes both `items` and `status`
                    arrays as defined by the corresponding `ITEMPOOL_TYPEDEF`.

    \return A pointer to the allocated item if successful, or `NULL` if no free
            items are available in the pool.
*/
#define ITEMPOOL_ALLOC(itempool) \
    itempool_alloc( \
        (uint8_t*)ITEMPOOL_ITEMS(itempool), \
        ITEMPOOL_STATUS(itempool), \
        ITEMPOOL_ITEM_SIZE(itempool), \
        ITEMPOOL_SIZE(itempool))

/*!
    \brief Allocates and initializes an item from the specified item pool.

    This macro uses the `itempool_calloc` function to allocate a single
    item from the given item pool, similar to `ITEMPOOL_ALLOC`. In addition,
    it ensures that the allocated memory is set to zero using `memset`.

    \param itempool The variable representing an instance of the item pool.
                    This should be a struct that includes both `items` and `status`
                    arrays as defined by the corresponding `ITEMPOOL_TYPEDEF`.

    \return A pointer to the allocated and zero-initialized item if successful,
            or `NULL` if no free items are available in the pool.
*/
#define ITEMPOOL_CALLOC(itempool) \
    itempool_calloc( \
        (uint8_t*)ITEMPOOL_ITEMS(itempool), \
        ITEMPOOL_STATUS(itempool), \
        ITEMPOOL_ITEM_SIZE(itempool), \
        ITEMPOOL_SIZE(itempool))


/*!
    \brief Frees a previously allocated item from the specified item pool.

    This macro marks an item in the item pool as free by updating its status
    in the `status` array. It calculates the index of the item based on the pointer
    difference between the provided item pointer (`itemptr`) and the start of the
    `items` array, then sets that entry in the `status` array to `ITEMPOOL_ITEM_FREE`.

    \param itempool The variable representing an instance of the item pool.
                    This should be a struct that includes both `items` and `status`
                    arrays as defined by the corresponding `ITEMPOOL_TYPEDEF`.
    \param itemptr A pointer to the item within the item pool that is to be freed.
*/
#define ITEMPOOL_FREE(itempool,itemptr) \
        do{ITEMPOOL_STATUS(itempool) \
            [((uint8_t*)itemptr-(uint8_t*)ITEMPOOL_ITEMS(itempool))/ \
             ITEMPOOL_ITEM_SIZE(itempool)] \
             =ITEMPOOL_ITEM_FREE;}while(0)

/*!
    \brief Allocates an item from a pool of pre-allocated items.

    This function searches through the specified array of status indicators to
    find the first free item (indicated by `ITEMPOOL_ITEM_FREE`). It then marks
    this item as used and returns a pointer to it. If no free item is found, the
    function returns NULL.

    \param items A pointer to the beginning of an array that holds pre-allocated
                 items in memory.
    \param status A pointer to an array indicating the allocation status (free or used)
                  of each corresponding item in the `items` array.
    \param itemsize The size, in bytes, of a single item within the pool. This allows
                    for correctly advancing the pointer through the array of items.
    \param poolsize The total number of items in the pool.

    \return A pointer to an allocated item if one is available; otherwise, NULL.
*/
void* itempool_alloc(uint8_t* items, uint8_t* status, size_t itemsize, size_t poolsize);

/*!
    \brief Allocates and initializes an item from a pool of pre-allocated items.

    This function first attempts to allocate an item using `itempool_alloc`. If successful,
    it additionally initializes the allocated memory block to zero, ensuring that all
    bytes in the allocated space are set to zero. This is particularly useful for avoiding
    uninitialized data issues.

    \param items A pointer to the beginning of an array that holds pre-allocated items
                 in memory.
    \param status A pointer to an array indicating the allocation status (free or used)
                  of each corresponding item in the `items` array.
    \param itemsize The size, in bytes, of a single item within the pool. This allows for
                    correctly advancing the pointer through the array of items during allocation.
    \param poolsize The total number of items in the pool.

    \return A pointer to an allocated and zero-initialized item if one is available;
            otherwise, NULL if no free items are found.
*/
void* itempool_calloc(uint8_t* items, uint8_t* status, size_t itemsize, size_t poolsize);

#endif /* ITEMPOOL_H_ */
