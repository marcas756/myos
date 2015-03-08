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
    \file   dlist.h

    \brief

    \details




+--------+
| dlist  |
| +----+ |      +----+
| |Head|-+----->|Null|
| +----+ |      +----+
| |Tail|-+----->|Null|
| +----+ |      +----+
+--------+

+--------+
| dlist  |
| +----+ |
|-|Head|-+-------.
| +----+ |       |
| |Tail|-+-----. |
| +----+ |     | |
+--------+     v v       (end)
             +----+      +----+
             |Next|----->|Null|
 +----+      +----+      +----+
 |Null|<-----|Prev|
 +----+      +----+
             |    |
             |Item|
             |    |
             +----+
             (begin)
             (tail)


                      +--------+
                      | dlist  |
                      | +----+ |
              .-------+-|Head| |
              |       | +----+ |
              |       | |Tail|-+------.
              |       | +----+ |      |
              |       +--------+      |
              |                       |
              v                       v         (end)
            +----+      +----+      +----+      +----+
            |Next|----->|Next|----->|Next|----->|Null|
+----+      +----+      +----+      +----+      +----+
|Null|<-----|Prev|<-----|Prev|<-----|Prev|
+----+      +----+      +----+      +----+
            |    |      |    |      |    |
            |Item|      |Item|      |Item|
            |    |      |    |      |    |
            +----+      +----+      +----+
            (begin)                 (tail)


*/

#ifndef DLIST_H_
#define DLIST_H_

#include <stddef.h>
#include <stdbool.h>
#include "item.h"

typedef struct dlist_node_t dlist_node_t;


/*
    Within a structure object, the non-bit-field members and the units in
    which bit-fields reside have addresses that increase in the order in which
    they are declared. A pointer to a structure object, suitably converted,
    points to its initial member (or if that member is a bit-field, then to the
    unit in which it resides), and vice versa. There may be unnamed padding within
    a structure object, but not at its beginning.
*/
struct dlist_node_t {
    dlist_node_t *next;
    dlist_node_t *prev;
};

typedef struct {
    dlist_node_t *head;
    dlist_node_t *tail;
}dlist_t;

#define dlist_node_typedef(type) \
    typedef struct{ \
        dlist_node_t link; \
        type item; \
    }type##_dlist_node_t;

#define dlist_node_t(type) \
    type##_dlist_node_t

#define dlist_init(dlistptr) \
    do { \
        (dlistptr)->head = NULL; \
        (dlistptr)->tail = NULL; \
    }while(0)

#define dlist_clear(dlistptr) dlist_init(dlistptr)

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
void dlist_erase(dlist_t *dlist, void *node);
void dlist_remove(dlist_t* dlist, item_compare_t compare, item_t* item);
void dlist_unique(dlist_t* dlist, item_compare_t compare);
void dlist_reverse (dlist_t * dlist);
void dlist_sort(dlist_t* dlist, item_compare_t compare);
dlist_node_t* dlist_find(dlist_t* dlist, void* node);
void dlist_swap(dlist_t *list1, dlist_t *list2);
#endif /* DLIST_H_ */
