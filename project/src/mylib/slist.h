/*! \copyright
    Copyright (c) 2013-2018, marcas756@gmail.com.
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
    \file       slist.h
    \authors    marcas756@gmail.com

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

/*! \addtogroup hdrsyshdrs Inclusion of system headers */
/*!@{*/
#include <stddef.h>
#include <stdbool.h>
/*!@}*//*hdrsyshdrs*/

/*! \addtogroup hdrusrhdrs Inclusion of user-defined headers */
/*!@{*/
/*!@}*//*hdrusrhdrs*/

/*! \addtogroup hdrmacros #define macros */
/*!@{*/

/*! Add SLIST_NODE_TYPE as first member of a structure to make it a list node */
#define SLIST_NODE_TYPE slist_node_t slist_node;
/*!@}*//*hdrmacros*/

/*! \addtogroup hdrfuncmacros #define function macros */
/*!@{*/

/*!
    \brief      Initialize list
    \details    An empty list only contains the list instance pointing to itself.
                It is important not to forget to initialize the list, as otherwise there
                will be undefined behavior with list functions and function like macros.

    \param      slistptr   List to initialize
*/
#define slist_init(slistptr) \
    do{(slistptr)->next = (slistptr);}while(0)

/*!
    \brief      Get next list node

    \param      slistptr   List
    \param      nodeptr    Current node

    \return     Successor of current node
*/
#define slist_next(slistptr,nodeptr) \
    (((slist_node_t*)(nodeptr))->next)

/*!
    \brief      Return iterator to beginning
    \details    Returns an iterator pointing to the first element in the list container.
                If the container is empty, the returned iterator value shall not be dereferenced.

    \param      slistptr    List

    \return     Pointer to the first node or on the list itself.
*/
#define slist_begin(slistptr) ((slistptr)->next)
#define slist_front(slistptr) (slist_begin(slistptr))



/*!
    \brief      Return iterator to end
    \details    Returns an iterator referring to the past-the-end element in the list container.
                It does not point to any element, and thus shall not be dereferenced.
                This function is often used in combination with list_begin to specify a range including
                all the elements in the container. As the Successor of the last element is the list itself,
                it returns the list itself.

    \param      slistptr    List

    \return     Iterator referring to the past-the-end element
*/
#define slist_end(slistptr) (slistptr)


/*!
    \brief      Iterate through whole list
    \details    Iterates from first to last element in the list container.

    \param      slistptr    List
    \param      iterator
*/
#define slist_foreach(slistptr,iterator) \
    for(iterator = slist_begin(slistptr); iterator != slist_end(slistptr); iterator=slist_next(slistptr,iterator))


/*!
    \brief      Test whether container is empty
    \details    Returns whether the list container is empty or not.

    \param      slistptr    List
    \returns    0 if it is not empty or 1 if it is empty
*/
#define slist_empty(slistptr) ((slistptr)->next==(slistptr))



/*!
    \brief      Insert element at beginning
    \details    Inserts a new node at the beginning of the list, right before its current first element.
    \param      slistptr    List
    \Param      nodeptr     Node to add to the list
*/
#define slist_push_front(slistptr,nodeptr) \
    do{ \
        ((slist_node_t*)(nodeptr))->next = (slistptr)->next; \
        (slistptr)->next=((slist_node_t*)(nodeptr)); \
    }while(0);

/*!
    \brief      Delete first node
    \details    Removes the first node of the list container.
 */
#define slist_pop_front(slistptr) \
    do{(slistptr)->next = (slistptr)->next->next;}while(0)

/*!
    \brief      Insert element at end
    \details    Inserts a new node at the end of the list, right after its current last node.
    \param      slistptr    List
    \Param      nodeptr     Node to add to the list
*/
#define slist_push_back(slistptr, nodeptr) \
    do { \
        ((slist_node_t*)(nodeptr))->next = slist_back(slistptr)->next; \
        ((slist_node_t*)(nodeptr))->next->next = ((slist_node_t*)(nodeptr)); \
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
    \param      slistptr    List
    \Param      nodeptr     Node to add to the list
*/
#define slist_insert_before(slistptr, posptr, nodeptr) \
    do{ \
        slist_prev(slistptr,posptr)->next = (slist_node_t*)(nodeptr); \
        ((slist_node_t*)(nodeptr))->next = posptr; \
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


/*!@}*//*hdrfucnmacros*/

/*! \addtogroup hdrtypedefs typedef definitions (type definitions for basic types such as int or char) */
/*!@{*/
/*!@}*//*hdrtypedefs*/

/*! \addtogroup hdrenums enum tag definitions (together with typedef ) */
/*!@{*/
/*!@}*//*hdrenums*/

/*! \addtogroup hdrstructs struct/union tag definitions (together with typedef) */
/*!@{*/

typedef struct slist_node_t slist_node_t;

struct slist_node_t {
    slist_node_t *next;
};

typedef slist_node_t slist_t; /*!< List instance is also a member of the list */

/*!@}*//*hdrstructs*/

/*! \addtogroup hdrextvars extern variable declarations */
/*!@{*/
/*!@}*//*hdrextvars*/

/*! \addtogroup hdrfuncproto Function prototype declarations */
/*!@{*/


/*!
    \brief      Get previous list node

    \param      slistptr    List
    \param      node        Current node

    \return     Predecessor of current node
*/
slist_node_t* slist_prev(slist_t *slist, void *node);

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
Delete last element
Removes the last element in the list container, effectively reducing the container size by one.
*/
void slist_pop_back(slist_t *slist);


/*
Remove elements with specific value
Removes from the container all the elements that compare equal to val. This calls the destructor of these objects and reduces the container size by the number of elements removed.

Unlike member function list::erase, which erases elements by their position (using an iterator), this function (list::remove) removes elements by their value.
*/
void slist_remove(slist_t* slist, bool (*equal) (void* node, void* value), void* value);

/*
Remove duplicate values
Removes all but the first element from every consecutive group of equal elements in the container.

Notice that an element is only removed from the list container if it compares equal to the element immediately preceding it. Thus, this function is especially useful for sorted lists.
*/
void slist_unique(slist_t* slist, bool (*equal) (void* node1, void* value));

/*
Reverse the order of elements
Reverses the order of the elements in the list container.
*/
void slist_reverse (slist_t * slist);

/*
Sort elements in container
Sorts the elements in the list, altering their position within the container.

The sorting is performed by applying an algorithm that uses either operator< (in version (1)) or comp (in version (2)) to compare elements. This comparison shall produce a strict weak ordering of the elements (i.e., a consistent transitive comparison, without considering its reflexiveness).

The resulting order of equivalent elements is  stable: i.e., equivalent elements preserve the relative order they had before the call.
 */
void slist_sort(slist_t* slist, bool (*swap) (void* node1, void* node2));

slist_node_t* slist_find(slist_t *slist, void *node);

/*!@}*//*hdrfuncproto*/

/*! \addtogroup hdrinlines Function Inline functions */
/*!@{*/
/*!@}*//*hdrinlines*/

#endif /* SLIST_H_ */
