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
    \file   xlist.h

    \brief

    \details


                               +--------+
                               | dlist  |
                               | +----+ |
                 .-------------+-|Head| |
                 |             | +----+ |
                 |             | |Tail|-+------------.
                 |             | +----+ |            |
                 |             +--------+            |
                 |                                   |
                 v                                   v
   +----+      +----+      +----+      +----+      +----+      +----+
   |Null|<-----|0^B |<---->|A^C |<---->|B^D |<---->|C^0 |----->|Null|
   +----+      +----+      +----+      +----+      +----+      +----+
               |    |      |    |      |    |      |    |
               |Item|      |Item|      |Item|      |Item|
               |    |      |    |      |    |      |    |
               +----+      +----+      +----+      +----+
               (begin)                             (end)
                 A           B           C           D


*/

#ifndef XLIST_H_
#define XLIST_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "item.h"

typedef struct xlist_node_t xlist_node_t;

/*
    Within a structure object, the non-bit-field members and the units in
    which bit-fields reside have addresses that increase in the order in which
    they are declared. A pointer to a structure object, suitably converted,
    points to its initial member (or if that member is a bit-field, then to the
    unit in which it resides), and vice versa. There may be unnamed padding within
    a structure object, but not at its beginning.
*/
struct xlist_node_t {
    xlist_node_t *nextprev;
};

typedef struct {
    xlist_node_t *head;
    xlist_node_t *tail;
}xlist_t;

#define xlist_xor(predecessor,successor) \
        ((xlist_node_t*)(((uintptr_t)(predecessor))^((uintptr_t)(successor))))

#define xlist_node_typedef(type) \
    typedef struct{ \
        xlist_node_t link; \
        type item; \
    }type##_xlist_node_t;

#define xlist_node_t(type) \
    type##_xlist_node_t

#define xlist_init(xlistptr) \
    do{ \
        (xlistptr)->head = NULL; \
        (xlistptr)->tail = NULL; \
    }while(0)

xlist_node_t* xlist_prev(xlist_t* xlist, xlist_node_t* node);
xlist_node_t* xlist_next(xlist_t* xlist, xlist_node_t* node);

#define xlist_item(nodeptr) \
    ((item_t*)(((xlist_node_t*)(nodeptr))+1))


#define xlist_begin(xlistptr) \
    (((xlist_t*)(xlistptr))->head)

#define xlist_end(xlistptr) \
    (((xlist_t*)(xlistptr))->tail)

#define xlist_empty(xlistptr) \
    (!(xlistptr)->head)

size_t xlist_size(xlist_t *xlist);


#define xlist_front(xlistptr) \
    ((void*)(xlist_begin(xlistptr)+1))

#define xlist_back(xlistptr) \
    ((void*)(xlist_end(xlistptr)+1))

void xlist_push_front(xlist_t* xlist, void* node);
void xlist_pop_front(xlist_t* xlist);

void xlist_push_back(xlist_t* xlist, void* node);
void xlist_pop_back(xlist_t* xlist);

void xlist_insert_after(xlist_t* xlist, void* position, void* node);
void xlist_insert_before(xlist_t* xlist, void* position, void* node);


#define  xlist_clear(xlistptr) xlist_init(xlistptr)


void xlist_erase(xlist_t *xlist, void *node);
void xlist_remove(xlist_t* xlist, item_compare_t compare, item_t* item);

void xlist_unique(xlist_t* xlist, item_compare_t compare);
void xlist_reverse (xlist_t * xlist);
void xlist_sort(xlist_t* xlist, item_compare_t compare);

xlist_node_t* xlist_find(xlist_t* xlist, void* node);

void xlist_swap(xlist_t *list1, xlist_t *list2);

#endif /* DLIST_H_ */
