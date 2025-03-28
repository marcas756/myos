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
    \file       slist.h

    \brief      Circular singly linked list header file

    \details    In computer science, a linked list is a linear collection of data elements,
                whose order is not given by their physical placement in memory.
                Instead, each element points to the next. It is a data structure consisting
                of a collection of nodes which together represent a sequence. In its most basic form,
                each node contains: data, and a reference (in other words, a link) to the next node
                in the sequence. This structure allows for efficient insertion or removal of elements
                from any position in the sequence during iteration.
                [Wikipedia - Linked list](https://en.wikipedia.org/wiki/Linked_list)

                Singly linked lists contain nodes which have a data field as well as 'next' field,
                which points to the next node in line of nodes. Operations that can be performed on
                singly linked lists include insertion, deletion and traversal.
                [Wikipedia - Singly linked list](https://en.wikipedia.org/wiki/Linked_list#Singly_linked_list)

                In the last node of a list, the link field often contains a null reference, a
                special value is used to indicate the lack of further nodes. A less common convention
                is to make it point to the first node of the list; in that case, the list is said to
                be 'circular' or 'circularly linked'; otherwise, it is said to be 'open' or 'linear'.
                It is a list where the last pointer points to the first node.
                [Wikipedia - Circular linked list](https://en.wikipedia.org/wiki/Linked_list#Circular_linked_list)
*/

#ifndef SLIST_H_
#define SLIST_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct slist_node_t slist_node_t;

/*!
    \brief      Singly Linked List Node Structure
    \details    Represents a node within a singly linked list.

                Each node contains a pointer to the next node,
                allowing for traversal through the list.
*/
struct slist_node_t {
    slist_node_t *next;    //!< Pointer to the next node in the list
};

/*!
   \brief     Type Definition for Singly Linked List
   \details   Creates an alias for 'slist_node_t', representing the entire
              singly linked list.

              This allows the list to be treated as a single entity, simplifying
              function signatures and variable declarations. The first node in the
              list serves as the list's head.
*/
typedef slist_node_t slist_t;

/*!
   \brief     Iterates through a singly linked list.
   \details   Defines a convenient macro for iterating through all nodes in a
              singly linked list. It initializes an iterator to the beginning
              of the list and continues until the end is reached, advancing
              the iterator to the next node in each step.

   \param list      A pointer to the list's control node
   \param iterator   A pointer to a `slist_node_t` that will be used as the iterator.
*/
#define slist_foreach(list,iterator) \
    for(iterator = slist_begin(list); (iterator) != slist_end(list); iterator=slist_next(list,iterator))

/*!
  \brief    Retrieves the next node in a singly linked list.

  \details  Returns a pointer to the node following the given node in the list.

  \param list A pointer to the list's control node
  \param node  A pointer to the current node.

  \return A pointer to the next node in the list.
*/
inline slist_node_t* slist_next(slist_t* list, slist_node_t* node)
{
    return node->next;
}

/*!
 \brief  Retrieves the node preceding the given node in a circular singly linked list.

 \details Returns a pointer to the node before the given node in a circular singly linked list.
          In a circular list, the last node's next pointer points back to the first node.
          Returns the list control node itself if the list is empty or if the given node is the first node in the list.

 \param list A pointer to the list control node.
 \param node A pointer to the node whose predecessor is to be found.

 \return A pointer to the node preceding the given node, or the list control node if the list is empty or the given node is the first node.
*/
slist_node_t* slist_prev(slist_t *list, slist_node_t* node);


/*!
 \brief Initializes a list control node.

 \details Initializes a list control node, preparing it for use.

 \param list A pointer to the list control node to initialize.
*/
inline void slist_init(slist_t* list)
{
    list->next = list;
}


/*!
 \brief Returns a pointer to the first data node in a circular singly linked list.

 \details Returns a pointer to the node immediately following the list control node.
         If the list is empty (control node points to itself), it returns a pointer to the list control node itself.

 \param list A pointer to the list control node.

 \return A pointer to the first data node in the list, or a pointer to the list control node if the list is empty.
*/
inline slist_node_t* slist_begin(slist_t* list)
{
    return list->next;
}

/*!
 \brief Returns a pointer to the first data node in a circular singly linked list.

 \details This function is an alias for `slist_begin`. It returns a pointer to the node immediately following the list control node.
         If the list is empty (control node points to itself), it returns a pointer to the list control node itself.

 \param list A pointer to the list control node.

 \return A pointer to the first data node in the list, or a pointer to the list control node if the list is empty.
*/
inline slist_node_t* slist_front(slist_t* list)
{
    return list->next;
}

/*!
 \brief Returns a pointer to the past-the-end element in the list.

 \details Returns a pointer to the list control block itself, which serves as a sentinel value to mark the end of the list.
       See the `slist_foreach` macro for example usage.

 \param list A pointer to the list control node.

 \return A pointer to the list control node, representing the end of the list.
*/
inline slist_node_t* slist_end(slist_t* list)
{
    return list;
}

/*!
 \brief Returns a pointer to the last data node in the list.

 \details Returns a pointer to the node immediately preceding the list control block.
       If the list is empty, it returns a pointer to the list control block itself.

 \param list A pointer to the list control node.

 \return A pointer to the last data node in the list, or the list control node if the list is empty.
*/
inline slist_node_t* slist_back(slist_t* list)
{
    return slist_prev(list,list);
}

/*!
 \brief Checks if the list is empty.

 \details Returns true if the list contains no data nodes. Otherwise, returns false.

 \param list A pointer to the list control node.

 \return True if the list is empty, false otherwise.
*/
inline bool slist_empty(slist_t* list)
{
    return list->next == list;
}

/*!
 \brief Inserts a new node at the beginning of the list.

 \details Inserts a new node at the beginning of the list.

 \param list A pointer to the list control node.
 \param node A pointer to the new node to be inserted.
*/
inline void slist_push_front(slist_t* list, slist_node_t* node)
{
    node->next = list->next;
    list->next = node;
}

/*!
 \brief Removes the first node from the list.

 \details Removes the first node from the list.

 \param list A pointer to the list control node.
*/
inline void slist_pop_front(slist_t* list)
{
    list->next = list->next->next;
}


/*!
 \brief Inserts a new node at the end of the list.

 \details Inserts a new node at the end of the list.

 \param list A pointer to the list control node.
 \param node A pointer to the new node to be inserted.
*/
inline void slist_push_back(slist_t* list, slist_node_t* node)
{
    slist_back(list)->next = node;
    node->next = list;
}


/*!
 \brief Returns a pointer to the node before the predecessor of the given node.

 \details Returns a pointer to the node that precedes the predecessor of the given node.
     This function efficiently finds the node two positions before the given node by calling `slist_prev` twice.

 \param list A pointer to the list control node.
 \param node A pointer to the node for which to find the node two positions before.

 \return A pointer to the node two positions before the given node.
*/
inline slist_node_t* slist_prev_prev(slist_t *list, slist_node_t* node)
{
    // Optimize! Current O = 2*n
    return slist_prev(list,slist_prev(list,node));
}


/*!
 \brief Removes the last node from the list.

 \details Removes the last node from the list.

 \param list A pointer to the list control node.
*/
inline void slist_pop_back(slist_t* list)
{
    slist_prev_prev(list,list)->next = (list);
}

/*!
 \brief Removes a node from the list.

 \details Removes the given node from the list.


 \param list A pointer to the list control node.
 \param node A pointer to the node to be removed from the list.
*/
inline void slist_erase(slist_t* list, slist_node_t* node)
{
    slist_prev(list,node)->next = node->next;
}

/*!
 \brief Inserts a new node after a given position in the list.

 \details Inserts the given node after the specified position.

 \param list A pointer to the list control node.
 \param pos A pointer to the node after which the new node should be inserted.
 \param node A pointer to the new node to be inserted.
*/
inline void slist_insert_after(slist_t* list, slist_node_t* pos, slist_node_t* node)
{
    node->next = pos->next;
    pos->next = node;
}

/*!
 \brief Inserts a new node before a given position in the list.

 \details Inserts the given node before the specified position.

 \param list A pointer to the list control node.
 \param pos A pointer to the node before which the new node should be inserted.
 \param node A pointer to the new node to be inserted.
*/
inline void slist_insert_before(slist_t* list, slist_node_t* pos, slist_node_t* node)
{
    slist_prev(list,pos)->next = node;
    node->next = pos;
}

/*!
 \brief Returns the number of nodes in the list.

 \details Returns the number of nodes currently in the list.

 \param list A pointer to the list control node.

 \return The number of nodes in the list.
*/
size_t slist_size(slist_t *list);

/*!
 \brief Searches for a node within the list.

 \details Searches for a specific node within the list.

 \param list A pointer to the list control node.
 \param node The node to search for.

 \return A pointer to the found node if it exists in the list, otherwise NULL.
*/
slist_node_t* slist_find(slist_t* list, slist_node_t* node);

#endif /* SLIST_H_ */



