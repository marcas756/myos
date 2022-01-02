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
    \file       dlist.h
    \authors    marco@bacchi.at

    \brief      Circular doubly linked list

    \details    In computer science, a linked list is a linear collection of data elements,
                whose order is not given by their physical placement in memory.
                Instead, each element points to the next. It is a data structure consisting
                of a collection of nodes which together represent a sequence. In its most basic form,
                each node contains: data, and a reference (in other words, a link) to the next node
                in the sequence. This structure allows for efficient insertion or removal of elements
                from any position in the sequence during iteration.
                [https://en.wikipedia.org/wiki/Linked_list]

                In a 'doubly linked list', each node contains, besides the next-node link, a second link field
                pointing to the 'previous' node in the sequence. The two links may be called 'forward('s') and
                'backwards', or 'next' and 'prev'('previous').
                [https://en.wikipedia.org/wiki/Linked_list#Doubly_linked_list]

                In the last node of a list, the link field often contains a null reference, a
                special value is used to indicate the lack of further nodes. A less common convention
                is to make it point to the first node of the list; in that case, the list is said to
                be 'circular' or 'circularly linked'; otherwise, it is said to be 'open' or 'linear'.
                It is a list where the last pointer points to the first node.
                [https://en.wikipedia.org/wiki/Linked_list#Circular_linked_list]
*/

#ifndef DLIST_H_
#define DLIST_H_

#include <stddef.h>

/*! Add DLIST_NODE_TYPE as first member of a structure to make it a list node */
#define DLIST_NODE_TYPE dlist_node_t dlist_node


/*!
    \brief      Get next list node

    \param      list   List
    \param      node    Current node

    \return     Successor of current node
*/
#define dlist_next(dlist,existing_node) \
    (((dlist_node_t*)(existing_node))->next)

/*!
    \brief      Get previous list node

    \param      list   List
    \param      node    Current node

    \return     Precessor of current node
*/
#define dlist_prev(dlist,existing_node) \
    (((dlist_node_t*)(existing_node))->prev)

/*!
    \brief      Initialize list
    \details    An empty list only contains the list instance pointing to itself.
                It is important not to forget to initialize the list, otherwise there
                may be undefined behavior with list functions and function like macros.

    \param      list  List to initialize
*/
#define dlist_init(dlist) \
    do{ \
        (dlist)->next = (dlist); \
        (dlist)->prev = (dlist); \
    }while(0)

/*!
    \brief      Return iterator to beginning
    \details    Returns an iterator pointing to the first element in the list container.
                If the container is empty, the returned iterator value shall not be dereferenced.

    \param      list    Listsize_t dlist_size(dlist_t *dlist);

    \return     Pointer to the first node or on the list itself.
*/
#define dlist_begin(dlist) ((dlist)->next)
#define dlist_front(dlist) (dlist_begin(dlist))

/*!
    \brief      Return iterator to end
    \details    Returns an iterator referring to the past-the-end element in the list container.
                It does not point to any element, and thus shall not be dereferenced.
                This function is often used in combination with list_begin to specify a range including
                all the elements in the container. As the Successor of the last element is the list itself,
                it returns the list itself.

    \param      list    List

    \return     Iterator referring to the past-the-end element
*/
#define dlist_end(dlist) (dlist)

/*
    \brief      Returns last node
    \details    This function returns an iterator on the last node in list.

    \param      list    List
    \returns    Iterator on last node in list
*/
#define dlist_back(dlist) (dlist_prev(dlist,dlist))


/*!
    \brief      Iterate through whole list
    \details    Iterates from first to last element in the list container.

    \param      slistptr    List
    \param      iterator
*/
#define dlist_foreach(dlist,iterator) \
    for(iterator = (void*)dlist_begin(dlist); ((dlist_node_t*)iterator) != dlist_end(dlist); iterator=(void*)dlist_next(dlist,iterator))


/*!
    \brief      Test whether container is empty
    \details    Returns whether the list container is empty or not.

    \param       list    List
    \returns    0 if it is not empty or 1 if it is empty
*/
#define dlist_empty(dlist) ((dlist)->next==(dlist))


/*!
    \brief      Insert element at beginning
    \details    Inserts a new node at the beginning of the list, right before its current first element.
    \param      list    List
    \Param      node_to_add     Node to add to the list
*/
#define dlist_push_front(dlist,node_to_add) \
    do{ \
        ((dlist_node_t*)(node_to_add))->next = (dlist)->next; \
        ((dlist_node_t*)(node_to_add))->prev = (dlist); \
        (dlist)->next->prev = ((dlist_node_t*)(node_to_add)); \
        (dlist)->next = ((dlist_node_t*)(node_to_add)); \
    }while(0);

/*!
    \brief      Delete first node
    \details    Removes the first node of the list container.
 */
#define dlist_pop_front(dlist) \
    do{ \
        (dlist)->next = (dlist)->next->next; \
        (dlist)->next->prev = (dlist); \
    }while(0);



/*!
    \brief      Insert element at end
    \details    Inserts a new node at the end of the list, right after the current back node.
    \param      list   List
    \param      node    Node to add to the list
*/
#define dlist_push_back(dlist, node_to_add) \
    do { \
        ((dlist_node_t*)(node_to_add))->next = (dlist); \
        ((dlist_node_t*)(node_to_add))->prev = (dlist)->prev; \
        (dlist)->prev->next = ((dlist_node_t*)(node_to_add)); \
        (dlist)->prev = ((dlist_node_t*)(node_to_add)); \
    }while(0)



/*
Delete last elementRemove last element from list
Removes the last element in the list container, effectively reducing the container size by one.
*/
#define dlist_pop_back(dlist) \
    do { \
        (dlist)->prev = (dlist)->prev->prev; \
        (dlist)->prev->next = (dlist); \
    }while(0)


/*!
    \brief      Removes a specific node from list
    \details    Removes a specific node from list. Node has to be a member of the list, otherwise
                erasing the node results in undefined behavior

    \param      list     List
    \param      nodep     Node to remove from list
*/
#define dlist_erase(dlist, existing_node) \
    do{ \
        ((dlist_node_t*)existing_node)->prev->next = ((dlist_node_t*)existing_node)->next; \
        ((dlist_node_t*)existing_node)->next->prev = ((dlist_node_t*)existing_node)->prev; \
    } while(0)


/*!
    \brief      Insert elements after position
    \details    The container is extended by inserting a new element after the element at the specified position.
    \param      list        List
    \param      existing_node    Node to insert new node after
    \param      node_to_insert   Node to insert
*/
#define dlist_insert_after(dlist, existing_node, node_to_insert) \
    do{ \
        ((dlist_node_t*)node_to_insert)->next = ((dlist_node_t*)existing_node)->next; \
        ((dlist_node_t*)node_to_insert)->prev = existing_node; \
        ((dlist_node_t*)existing_node)->next->prev = node_to_insert; \
        ((dlist_node_t*)existing_node)->next = node_to_insert; \
    } while(0)

/*!
    \brief      Insert element before position
    \details    The container is extended by inserting a new element before the element at the specified position.
    \param      list        List
    \param      existing_node    Node to insert new node before
    \param      node_to_insert   Node to insert
*/
#define dlist_insert_before(dlist, existing_node, node_to_insert) \
    do{ \
        ((dlist_node_t*)node_to_insert)->next = existing_node; \
        ((dlist_node_t*)node_to_insert)->prev = ((dlist_node_t*)existing_node)->prev; \
        ((dlist_node_t*)existing_node)->prev->next = node_to_insert; \
        ((dlist_node_t*)existing_node)->prev = node_to_insert; \
    } while(0)


typedef struct dlist_node_t dlist_node_t;

struct dlist_node_t {
    dlist_node_t *next;
    dlist_node_t *prev;
};

typedef dlist_node_t dlist_t; /*!< List instance is also a member of the list */

/*
    \brief      Counts number of nodes in list
    \details    Returns the number of elements in the list container. List node itself
                is not counted.

    \param      dlist       List
    \returns    Returns the number of elements in the list container.
 */
size_t dlist_size(dlist_t *dlist);


/*
    \brief      Checks if a node is in the list
    \details    Iterates through list and checks if a specific node is in the list

    \param      dlist       List
    \param      node        Node to search for
    \returns    Pointer to node if it exist, NULL otherwise
 */
dlist_node_t* dlist_find(dlist_t* dlist, void* node);

#endif /* DLIST_H_ */



