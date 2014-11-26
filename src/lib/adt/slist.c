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
    \file   slist.c

    \brief

    \details
*/

#include "slist.h"
#include <stdbool.h>

slist_node_t* slist_find(slist_t *slist, void *node)
{
	slist_node_t *iterator = slist->head;

	while(iterator)
	{
		if (iterator == node) break;
		iterator = iterator->next;
	}

	return iterator;
}

slist_node_t* slist_end(slist_t *slist)
{
	slist_node_t *iterator = slist->head;

	if(!iterator) return NULL;

	while(iterator->next)
		iterator = iterator->next;

	return iterator;
}

slist_node_t* slist_prev(slist_t *slist, slist_node_t* node)
{
	slist_node_t *iterator = slist->head;

	if(!iterator) return NULL;

    while(iterator->next)
    {
        if(iterator->next == node)
            return iterator;

        iterator = iterator->next;

    }

	return NULL;
}

size_t slist_size(slist_t *slist)
{
	slist_node_t *iterator = slist->head;
	size_t size = 0;

	while(iterator)
	{
		size++;
		iterator = iterator->next;
	}

	return size;
}


/*
Add element at the end
Adds a new element at the end of the list container, after its current last element. The content of val is copied (or moved) to the new element.

This effectively increases the container size by one.
*/
void slist_push_back(slist_t *slist, void *node)
{
	slist_node_t* iterator = slist_end(slist);

	((slist_node_t*)node)->next = NULL;

	if(iterator)
		iterator->next=node;
	else
		slist->head=node;
}

void slist_pop_back(slist_t *slist)
{
	slist_node_t* iterator = slist->head;

	if (!iterator) return;
	if (!iterator->next)
	{
		slist->head = NULL;
		return;
	}

	while(iterator->next->next)
		iterator = iterator->next;

	iterator->next = NULL;
}



void slist_insert_before(slist_t* slist, void* position, void* node)
{
	slist_node_t* iterator = slist->head;

	if(iterator == position)
	{
		slist_push_front(slist,(slist_node_t*)node);
		return;
	}

	((slist_node_t*)node)->next = position;

	while(iterator->next != position)
		iterator = iterator->next;

	iterator->next = node;
}


void slist_insert_after(slist_t* slist, void* position, void* node)
{
	((slist_node_t*)node)->next = ((slist_node_t*)position)->next;
	((slist_node_t*)position)->next = node;
}


void slist_erase(slist_t *slist, void *node)
{
	slist_node_t *iterator = slist_prev(slist,node);

	if (iterator)
		iterator->next = ((slist_node_t*)node)->next;
	else
		slist->head = ((slist_node_t*)node)->next;
}

/*
Swap content
Exchanges the content of the container by the content of x, which is another list of the same type. Sizes may differ.

After the call to this member function, the elements in this container are those which were in x before the call, and the elements of x are those which were in this. All iterators, references and pointers remain valid for the swapped objects.
*/
void slist_swap(slist_t *list1, slist_t *list2)
{
	slist_node_t *tmp = list1->head;
	list1->head = list2->head;
	list2->head = tmp;
}



/*
Reverse the order of elements
Reverses the order of the elements in the list container.
*/
void slist_reverse (slist_t * slist)
{
	slist_t tmp;
	slist_node_t* iterator;

	slist_init(&tmp);

	while(slist_begin(slist))
	{
		iterator = slist_begin(slist);
		slist_pop_front(slist);
		slist_push_front(&tmp,iterator);

	}

	slist_swap(slist,&tmp);
}

/*
Merge sorted lists
Merges x into the list by transferring all of its elements at their respective ordered positions into the container (both containers shall already be ordered).

This effectively removes all the elements in x (which becomes empty), and inserts them into their ordered position within container (which expands in size by the number of elements transferred). The operation is performed without constructing nor destroying any element: they are transferred, no matter whether x is an lvalue or an rvalue, or whether the value_type supports move-construction or not.
*/
void slist_merge(slist_t* dest, slist_t* src)
{
	if(slist_begin(dest))
	{
		slist_end(dest)->next = src->head;
		src->head = NULL;
	}
	else
	{
		slist_swap(dest,src);
	}
}

/*
Remove elements with specific value
Removes from the container all the elements that compare equal to val. This calls the destructor of these objects and reduces the container size by the number of elements removed.

Unlike member function list::erase, which erases elements by their position (using an iterator), this function (list::remove) removes elements by their value.
*/
void slist_remove(slist_t* slist, item_compare_t compare, item_t* item)
{
	slist_node_t *iterator = slist->head;

	while(iterator)
	{
		if(compare(slist_item(iterator),item) == ITEM_EQUALS_TO)
			slist_erase(slist,iterator);

		iterator = iterator->next;
	}
}

/*
Remove duplicate values
The version with no parameters (1), removes all but the first element from every consecutive group of equal elements in the container.

Notice that an element is only removed from the list container if it compares equal to the element immediately preceding it. Thus, this function is especially useful for sorted lists.
*/
void slist_unique(slist_t* slist, item_compare_t compare)
{

}

/*
 Swaps to nodes in a list
 Behaviour is undefined, if one or both nodes are not member of the list.
*/
void slist_swap_nodes(slist_t* slist, void* node1, void* node2)
{
    slist_node_t *prev1,*prev2,*tmp;

    if (node1 == node2) return;

    prev1 = slist_prev(slist,node1); //!!!
    prev2 = slist_prev(slist,node2); //!!!

    tmp = ((slist_node_t*)node2)->next;
    ((slist_node_t*)node2)->next = ((slist_node_t*)node1)->next;
    ((slist_node_t*)node1)->next = tmp;

    if(prev1 && prev2)
    {
        prev1->next = node2;
        prev2->next = node1;
        return;
    }

    if(!prev1)
    {
        slist->head = node2;
        prev2->next = node1;
    }
    else // !prev2
    {
        slist->head = node1;
        prev1->next = node2;
    }

}


/*
Sort elements in container
Sorts the elements in the list, altering their position within the container.

The sorting is performed by applying an algorithm that uses either operator< (in version (1)) or comp (in version (2)) to compare elements. This comparison shall produce a strict weak ordering of the elements (i.e., a consistent transitive comparison, without considering its reflexiveness).

The resulting order of equivalent elements is IN-stable: i.e., equivalent elements preserve the relative order they had before the call.
 */
void slist_sort(slist_t* slist, item_compare_t compare)
{
    slist_node_t *iterator;
    slist_node_t *largest;
    slist_t sorted;

    // list sorted yet?
    if(!slist->head || !slist->head->next)
        return;

    slist_init(&sorted);

    while(slist->head)
    {
        iterator = slist->head;
        largest = iterator;

        while(iterator)
        {
            if(compare(slist_item(iterator),slist_item(largest)) != ITEM_LESS_THAN)
                largest = iterator;

            iterator = iterator->next;
        }


        slist_erase(slist,largest);
        slist_push_front(&sorted,largest);
    }

    slist_swap(&sorted,slist);
}
