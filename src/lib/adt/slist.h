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
    \file   slist.h

    \brief

    \details
*/

#ifndef SLIST_H_
#define SLIST_H_

#include <stdlib.h>
#include <stdbool.h>
#include "item.h"

typedef struct slist_node_t slist_node_t;

struct slist_node_t {
	slist_node_t *next;
};

typedef struct {
	slist_node_t *head;
}slist_t;

#define slist_node_typedef(type) \
	typedef struct{ \
		slist_node_t *next; \
		type item; \
	}type##_slist_node_t;

#define slist_node_t(type) \
	type##_slist_node_t

#define slist_item(nodeptr) \
		((item_t*)(((slist_node_t*)(nodeptr))+1))

#define slist_next(nodeptr) \
	(((slist_node_t*)(nodeptr))->next)

#define slist_init(slistptr) \
	do{(slistptr)->head=NULL;}while(0)

/*
Insert elements after position
The container is extended by inserting a new element after the element at the specified position.

This effectively increases the list size by 1.
*/
void slist_insert_after(slist_t* slist, void* position, void* node);
/*
Insert elements before position
The container is extended by inserting a new element before the element at the specified position.

This effectively increases the list size by 1.


*/
void slist_insert_before(slist_t* slist, void* position, void* node);

/*
Return iterator to beginning
Returns an iterator pointing to the first element in the list container.
Notice that, unlike member list::front, which returns a reference to the first element,
this function returns a bidirectional iterator pointing to it.

If the container is empty, the returned iterator value shall not be dereferenced.
 */
#define slist_begin(slistptr) ((slistptr)->head)

/*
Return iterator to end
Returns an iterator referring to the past-the-end element in the list container.

The past-the-end element is the theoretical element that would follow the last
element in the list container. It does not point to any element, and thus shall
not be dereferenced.

Because the ranges used by functions of the standard library do not include the
element pointed by their closing iterator, this function is often used in combination
with list::begin to specify a range including all the elements in the container.

If the container is empty, this function returns the same as list::begin.
*/
#define slist_end(slistptr) (NULL)

slist_node_t* slist_tail(slist_t *slist);
slist_node_t* slist_prev(slist_t *slist, slist_node_t *node);

/*
Test whether container is empty
Returns whether the list container is empty (i.e. whether its size is 0).

This function does not modify the container in any way. To clear the content of a
list container, see list::clear.
*/
#define slist_empty(slistptr) (!(slistptr)->head)

/*
Return size
Returns the number of elements in the list container.
 */
size_t slist_size(slist_t *slist);

/*
Access first element
Returns a reference to the first element in the list container.

Unlike member list::begin, which returns an iterator to this same element, this function returns a direct reference.

Calling this function on an empty container causes undefined behavior.
*/
#define slist_front(slistptr) ((void*)((slistptr)->head+1))

/*
Access last element
Returns a reference to the last element in the list container.

Unlike member list::end, which returns an iterator just past this element, this function returns a direct reference.

Calling this function on an empty container causes undefined behavior.
*/
#define slist_back(slistptr) ((void*)(slist_tail(slistptr)+1))

/*
Insert element at beginning
Inserts a new element at the beginning of the list, right before its current first element.

This effectively increases the container size by one.
*/
#define slist_push_front(slistptr,nodeptr) \
	do{(nodeptr)->next = (slistptr)->head;(slistptr)->head = (slist_node_t*)(nodeptr);}while(0)

/*
Delete first element
Removes the first element in the list container, effectively reducing its size by one.
 */
#define slist_pop_front(slistptr) \
	do{if((slistptr)->head)(slistptr)->head=(slistptr)->head->next;}while(0)

/*
Delete last element
Removes the last element in the list container, effectively reducing the container size by one.
*/
void slist_pop_back(slist_t *slist);
/*
Add element at the end
Adds a new element at the end of the list container, after its current last element. The content of val is copied (or moved) to the new element.

This effectively increases the container size by one.
*/
void slist_push_back(slist_t *slist, void *node);

/*
Remove elements with specific value
Removes from the container all the elements that compare equal to val. This calls the destructor of these objects and reduces the container size by the number of elements removed.

Unlike member function list::erase, which erases elements by their position (using an iterator), this function (list::remove) removes elements by their value.
*/
void slist_remove(slist_t* slist, item_compare_t compare, item_t* item);

void slist_unique(slist_t* slist, item_compare_t compare);

void slist_reverse (slist_t * slist);
void slist_sort(slist_t* slist, item_compare_t compare);

slist_node_t* slist_find(slist_t *slist, slist_node_t *node);

#endif /* SLIST_H_ */
