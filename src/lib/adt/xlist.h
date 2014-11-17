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


*/

#ifndef XLIST_H_
#define XLIST_H_

#include <stdlib.h>
#include <stdbool.h>
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

#define xlist_link(predecessor,successor) \
    ((predecessor)^(successor))

#define xlist_successor(nodeptr,predecessor) \
    ((nodeptr)->nextprev^(predecessor))

#define xlist_predecessor(nodeptr,successor) \
    ((nodeptr)->nextprev^(successor))

#define xlist_node_typedef(type) \
    typedef struct{ \
        xlist_node_t* nextprev; \
        type item; \
    }type##_xlist_node_t;

#define xlist_node_t(type) \
    type##_xlist_node_t

#define xlist_init(xlistptr) \
    do{ \
        (xlistptr)->head = NULL; \
        (xlistptr)->tail = NULL; \
    }while(0)


#define dlist_next(dlistptr,nodeptr) \
    (((dlist_node_t*)(nodeptr))->next)

#define dlist_prev(dlistptr,nodeptr) \
    (((dlist_node_t*)(nodeptr))->prev)

#define dlist_item(nodeptr) \
    ((item_t*)(((dlist_node_t*)(nodeptr))+1))


#define dlist_begin(dlistptr) \
    (((dlist_t*)(dlistptr))->head)

#define dlist_end(dlistptr) \
    (((dlist_t*)(dlistptr))->tail)

#define dlist_empty(dlistptr) \
    (!(dlistptr)->head)

size_t dlist_size(dlist_t *dlist);

#define dlist_front(dlistptr) \
    ((void*)(dlist_begin(dlistptr)+1))

#define dlist_back(dlistptr) \
    ((void*)(dlist_end(dlistptr)+1))

void dlist_push_front(dlist_t* dlist, void* node);
void dlist_pop_front(dlist_t* dlist);
void dlist_push_back(dlist_t* dlist, void* node);
void dlist_pop_back(dlist_t* dlist);
void dlist_insert_after(dlist_t* dlist, void* position, void* node);
void dlist_insert_before(dlist_t* dlist, void* position, void* node);
void dlist_clear(dlist_t* dlist);
void dlist_erase(dlist_t *dlist, void *node);
void dlist_remove(dlist_t* dlist, item_compare_t compare, item_t* item);
void dlist_unique(dlist_t* dlist, item_compare_t compare);
void dlist_reverse (dlist_t * dlist);
void dlist_sort(dlist_t* dlist, item_compare_t compare);
dlist_node_t* dlist_find(dlist_t* dlist, void* node);
void dlist_swap(dlist_t *list1, dlist_t *list2);
#endif /* DLIST_H_ */
