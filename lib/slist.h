/*! \copyright
 
   https://opensource.org/licenses/BSD-3-Clause
 
   Copyright 2013-2021 Marco Bacchi <marco@bacchi.at>
   
   Redistribution and use in source and binary forms, with or without 
   modification, are permitted provided that the following conditions are met:
   
   1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.
   
   2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

   3. Neither the name of the copyright holder nor the names of its 
   contributors may be used to endorse or promote products derived from this 
   software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
   POSSIBILITY OF SUCH DAMAGE.
*/


/*!
    \file       slist.h

    \brief      Circular singly linked list

    \details    In computer science, a linked list is a linear collection of data elements,
                whose order is not given by their physical placement in memory.
                Instead, each element points to the next. It is a data structure consisting
                of a collection of nodes which together represent a sequence. In its most basic form,
                each node contains: data, and a reference (in other words, a link) to the next node
                in the sequence. This structure allows for efficient insertion or removal of elements
                from any position in the sequence during iteration.
                [https://en.wikipedia.org/wiki/Linked_list]

                Singly linked lists contain nodes which have a data field as well as 'next' field,
                which points to the next node in line of nodes. Operations that can be performed on
                singly linked lists include insertion, deletion and traversal.
                [https://en.wikipedia.org/wiki/Linked_list#Singly_linked_list]

                In the last node of a list, the link field often contains a null reference, a
                special value is used to indicate the lack of further nodes. A less common convention
                is to make it point to the first node of the list; in that case, the list is said to
                be 'circular' or 'circularly linked'; otherwise, it is said to be 'open' or 'linear'.
                It is a list where the last pointer points to the first node.
                [https://en.wikipedia.org/wiki/Linked_list#Circular_linked_list]
*/

#ifndef SLIST_H_
#define SLIST_H_

#include <stddef.h>
#include <stdbool.h>

/*! Add SLIST_NODE_TYPE as first member of a structure to make it a list node */
#define SLIST_NODE_TYPE slist_node_t slist_node


/*!
    \brief      Get next list node

    \param      slist   List
    \param      node    Current node

    \return     Successor of current node
*/
#define slist_next(slist,node) \
    (((slist_node_t*)(node))->next)

/*!
    \brief      Initialize list
    \details    An empty list only contains the list instance pointing to itself.
                It is important not to forget to initialize the list, otherwise there
                may be undefined behavior with list functions and function like macros.

    \param      slist  List to initialize
*/
#define slist_init(slist) \
    do{slist_next(slist,slist) = (slist);}while(0)

/*!
    \brief      Return iterator to beginning
    \details    Returns an iterator pointing to the first element in the list container.
                If the container is empty, the returned iterator value shall not be dereferenced.

    \param      slistptr    List

    \return     Pointer to the first node or on the list itself.
*/
#define slist_begin(slist) ((slist)->next)
#define slist_front(slist) (slist_begin(slist))



/*!
    \brief      Return iterator to end
    \details    Returns an iterator referring to the past-the-end element in the list container.
                It does not point to any element, and thus shall not be dereferenced.
                This function is often used in combination with list_begin to specify a range including
                all the elements in the container. As the Successor of the last element is the list itself,
                it returns the list itself.

    \param      slist    List

    \return     Iterator referring to the past-the-end element
*/
#define slist_end(slist) (slist)


/*!
    \brief      Iterate through whole list
    \details    Iterates from first to last element in the list container.

    \param      slistptr    List
    \param      iterator
*/
#define slist_foreach(slist,iterator) \
    for(iterator = (void*)slist_begin(slist); ((slist_node_t*)iterator) != slist_end(slist); iterator=(void*)slist_next(slist,iterator))


/*!
    \brief      Test whether container is empty
    \details    Returns whether the list container is empty or not.

    \param      slistptr    List
    \returns    0 if it is not empty or 1 if it is empty
*/
#define slist_empty(slist) ((slist)->next==(slist))



/*!
    \brief      Insert element at beginning
    \details    Inserts a new node at the beginning of the list, right before its current first element.
    \param      slistptr    List
    \param      nodeptr     Node to add to the list
*/
#define slist_push_front(slist,node_to_add) \
    do{ \
        ((slist_node_t*)(node_to_add))->next = (slist)->next; \
        (slist)->next=((slist_node_t*)(node_to_add)); \
    }while(0);

/*!
    \brief      Delete first node
    \details    Removes the first node of the list container.
 */
#define slist_pop_front(slist) \
    do{(slist)->next = (slist)->next->next;}while(0)

/*!
    \brief      Insert element at end
    \details    Inserts a new node at the end of the list, right after the current back node.
    \param      slistptr    List
    \param      nodeptr     Node to add to the list
*/
#define slist_push_back(slist, node_to_add) \
    do { \
        ((slist_node_t*)(node_to_add))->next = slist_back(slist); \
        ((slist_node_t*)(node_to_add))->next->next = ((slist_node_t*)(node_to_add)); \
        ((slist_node_t*)(node_to_add))->next = slist_end(slist);\
    }while(0)




/*!
    \brief      Insert elements after position
    \details    The container is extended by inserting a new element after the element at the specified position.
    \param      slistptr    List
    \Param      nodeptr     Node to add to the list
*/
#define slist_insert_after(slistptr, posptr, nodeptr) \
    do{ \
        ((slist_node_t*)(nodeptr))->next = ((slist_node_t*)(posptr))->next; \
        ((slist_node_t*)(posptr))->next = ((slist_node_t*)(nodeptr)); \
    }while(0)



/*!
    \brief      Insert elements before position
    \details    The container is extended by inserting a new element before the element at the specified position.
    \param      slist    			List
    \Param      node_to_insert    	Node to add to the list
*/
#define slist_insert_before(slist, existing_node, node_to_insert) \
    do{ \
        slist_prev(slist,existing_node)->next = (slist_node_t*)(node_to_insert); \
        ((slist_node_t*)node_to_insert))->next = existing_node; \
    }while(0)



/*!
    \brief      Clear content
    \details    Removes all elements from the list container, and leaving the container with a size of 0.
    \param      slistptr    List
*/
#define  slist_clear(slistptr) \
    slist_init(slistptr)

/*!
    \brief      Removes a specific node from list
    \details    Removes a specific node from list. Node has to be a member of the list, otherwise
                erasing the node results in undefined behavior

    \param      slistptr    List
    \Param      nodeptr     Node to remove from list
*/
#define slist_erase(slistptr, nodeptr) \
    do{ \
        slist_prev(slistptr,nodeptr)->next = ((slist_node_t*)(nodeptr))->next; \
    }while(0)

typedef struct slist_node_t slist_node_t;

struct slist_node_t {
    slist_node_t *next;
};

typedef slist_node_t slist_t; /*!< List instance is also a member of the list */


/*!
    \brief      Get previous list node

    \param      slistptr    List
    \param      node        Current node

    \return     Predecessor of current node
*/
slist_node_t* slist_prev(slist_t *slist, void *existing_node);

/*
    \brief      Counts number of nodes nb list
    \details    Returns the number of elements in the list container. List node itself
                is not counted.

    \param      slist       List
    \returns    Returns the number of elements in the list container.
 */
size_t slist_size(slist_t *slist);



/*
    \brief      Returns last node
    \details    This function returns an iterator on the last node in list.

    \param      slistptr    List
    \returns    Iterator on last node in list
*/
slist_node_t* slist_back(slist_t* slist);


/*
   \brief       Delete last element
   \details     Removes the last element in the list container, effectively reducing the container size by one.

   \param       slistptr    List
*/
void slist_pop_back(slist_t *slist);


/*
    \brief      Checks if a node is in the list
    \details    Iterates through list and checks if a specific node is in the list

    \param      dlist       List
    \param      node        Node to search for
    \returns    Pointer to node if it exist, NULL otherwise
 */
slist_node_t* slist_find(slist_t *slist, void *node);

#endif /* SLIST_H_ */
