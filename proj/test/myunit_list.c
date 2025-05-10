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
   \file      dlist_tests.c

   \brief     Unit tests for the circular linked list implementation.

   \details   This file contains a comprehensive suite of unit tests designed to
               verify the correctness of the circular linked list
               implementation.  The tests cover a wide range of scenarios,
               including list initialization, node insertion, deletion, traversal,
               and searching.  Each test case is designed to isolate and validate
               specific functionalities of the dlist.

   \details   The following test cases are included:

     - initial_check_of_all_nodes: Verifies that all nodes in a pre-populated list are valid.
     - list_initialization: Checks that a newly initialized list is empty.
     - foreach: Tests the correct iteration through all nodes in a populated list using the foreach macro.
     - foreach_empty: Verifies that the foreach macro behaves correctly on an empty list.
     - next_prev_stepbystep:  Tests the `next` and `prev` functions by stepping through the list.
     - prev_prev_empty: Checks the `prev` function when called on an empty list.
     - prev_prev_1_node: Checks the `prev` function when called on a list with only one node.
     - prev_prev_2_nodes: Checks the `prev` function when called on a list with two nodes.
     - front_back_two_nodes: Tests accessing the front and back nodes of a two-node list.
     - front_back_single_node: Tests accessing the front and back nodes of a single-node list.
     - push_back_pop_back: Tests adding and removing elements from the back of the list.
     - push_back_pop_front: Tests adding to the back and removing from the front.
     - push_front_pop_front: Tests adding and removing elements from the front of the list.
     - push_front_pop_back: Tests adding to the front and removing from the back.
     - insert_after: Tests inserting a new node after a specified node.
     - insert_before: Tests inserting a new node before a specified node.
     - erase: Tests deleting a node from the list.
     - find_empty_list: Tests searching for a node in an empty list.
     - find_node_present: Tests searching for a node that exists in the list.
     - find_node_not_present: Tests searching for a node that does not exist in the list.
     - find_first_node: Tests finding the first node in the list.
     - find_last_node: Tests finding the last node in the list.
     - size_empty_list: Tests the size of an empty list.
     - size_multiple_elements: Tests the size of a list with multiple elements.
*/

#include "myunit.h"
#include <stdint.h>

#include "utils.h"

#define UNITTEST_LIST_TYPE_SLIST 0
#define UNITTEST_LIST_TYPE_DLIST 1

#if ( UNITTEST_LIST_TYPE == UNITTEST_LIST_TYPE_SLIST )
    #include"myunit_slist.h"
#elif ( UNITTEST_LIST_TYPE == UNITTEST_LIST_TYPE_DLIST )
    #include"myunit_dlist.h"
#else
    #error "Unknown list type"
#endif

/*!
 \brief Represents a node within a doubly linked list, along with associated data.

 \details This structure encapsulates a `list_node_t` for use in a doubly linked list,
          augmented by additional fields that provide metadata and validation capabilities:
          - `nodeid`: A unique identifier for the node (uint8_t). It is used to validate
            the node's position within an array of nodes, ensuring consistency between
            memory location and logical structure.
          - `before`: A data field (uint32_t) stored before the list node. Typically holds a
            constant value (`PATTERN`) for integrity checks.
          - `node`: The actual `list_node_t` structure, which facilitates linking into
            the doubly linked list.
          - `after`: A data field (uint32_t) stored after the list node. Like `before`, it
            holds a constant value (`PATTERN`) to aid in validation and ensure that the
            node's state remains consistent.

 \note   The structure is designed for use with the `list_t` doubly linked list implementation.
         It leverages additional fields for debugging, validation, and state management.
*/
typedef struct {
    uint8_t nodeid;      //!< Unique identifier for the node, used for consistency checks
    uint32_t before;     //!< Data field stored before the list node, often used for validation (e.g., holds `PATTERN`)
    list_node_t node;   //!< The actual doubly linked list node structure
    uint32_t after;      //!< Data field stored after the list node, typically used for integrity checks (e.g., holds `PATTERN`)
} mynode_t;

typedef enum {
    NODE0 = 0,
    NODE1,
    NODE2,
    NODES
}nodeid_t;

/*!
 \brief Constant pattern for validation and debugging.

 \details `PATTERN` is set to `0x55555555 = 01010101 01010101 01010101 01010101 binary`. It serves as a recognizable marker
          for consistency checks in node fields like `before` and `after`, aiding
          in detecting unintended modifications or memory corruption.
*/
#define PATTERN 0x55555555

/*!
 \brief Initializes an array of `mynode_t` structures.

 \details This static array, `mynodes`, contains a predefined number of nodes (`NODES`).
          Each node is initialized with:
          - A unique identifier (`nodeid`) set to its index (e.g., `NODE0`, `NODE1`).
          - The `before` and `after` fields are initialized with the constant value `PATTERN`.
          - The `list_node_t node` member is zero-initialized, setting up an empty list node.

 \note   This initialization ensures that each node starts in a consistent state,
         ready to be linked into a doubly linked list. The use of `PATTERN` helps
         validate the integrity of nodes during operations.
*/
static mynode_t mynodes[NODES] = {
    {NODE0, PATTERN, {0}, PATTERN},
    {NODE1, PATTERN, {0}, PATTERN},
    {NODE2, PATTERN, {0}, PATTERN}
};

/*!
 \brief  Validates a `list_node_t` node and its associated `mynode_t` structure.

 \details This function performs several checks to ensure the integrity of a given `list_node_t` node:
         - Checks if the node pointer is NULL.
         - Retrieves the associated `mynode_t` structure using the `container_of` macro.
         - Verifies that the `nodeid` member of the `mynode_t` structure matches the index of the node in the `mynodes` array.
         - Confirms that the `before` and `after` members of the `mynode_t` structure are equal to the defined `PATTERN` value.

 \param node A pointer to the `list_node_t` node to validate.

 \return `true` if the node is valid and all checks pass, `false` otherwise.

 \note   This function assumes that the `mynodes` array is properly initialized and that the `PATTERN` value is defined.
*/
bool mynode_check(list_node_t *node, uint8_t expectedid)
{
    mynode_t *mynode;

    if (node == NULL)
    {
        return false;
    }

    mynode = container_of(node, mynode_t, node);

    if (mynode == NULL)
    {
        return false;
    }

    if ((mynode-mynodes) != mynode->nodeid)
    {
        return false;
    }

    if ( expectedid != mynode->nodeid )
    {
        return false;
    }

    if (( mynode->after != PATTERN )||( mynode->before != PATTERN ))
    {
        return false;
    }


    return true;
}

/*! Enumeration defining fixture setup types for testing. */
typedef enum {
    FIXTURE_EMPTY,  //!< Represents an empty list fixture.
    FIXTURE_NORMAL, //!< Represents a list with normal (forward) order.
    FIXTURE_INVERS  //!< Represents a list with reversed (inverse) order.
}fixture_setup_t;

/*!
    \brief      Sets up a test fixture for a circularly linked list.

    \details    Initializes `list_t` using `fixture_setup_t`. Prepares the list with
                nodes in normal or inverse order based on the fixture configuration.

    \param  fixture      Configuration details for setting up the list.
    \param  list         Pointer to the `list_t` structure to be set up.

    \return void
*/
void test_fixture_setup(fixture_setup_t fixture, list_t *list)
{
    list_init(list);

    switch (fixture)
    {
        case FIXTURE_NORMAL :
            list_push_back(list,&mynodes[NODE0].node);
            list_push_back(list,&mynodes[NODE1].node);
            list_push_back(list,&mynodes[NODE2].node);
            break;
        case FIXTURE_INVERS :
            list_push_front(list,&mynodes[NODE0].node);
            list_push_front(list,&mynodes[NODE1].node);
            list_push_front(list,&mynodes[NODE2].node);
            break;
        default:
            break;

    }

}


/*!
   \brief     Tests the list_foreach macro with a predefined list.

   \details   This test case initializes a circular doubly linked list with a
              fixed number of nodes and then uses the list_foreach macro to
              iterate through the list. It asserts that the mynode_check
              function returns true for each node and that the node count
              matches the expected number of nodes. It also verifies that the
              list size remains consistent.
*/
MYUNIT_TESTCASE(foreach)
{
   // PRECONDITIONS :
   // -------------------------------------------------
   list_node_t *iterator;
   size_t nodecount = 0;

   list_t list;
   test_fixture_setup(FIXTURE_NORMAL, &list);




   // EXECUTE TESTCASE :
   // -------------------------------------------------


   // Use the dlist_foreach macro to iterate through the list
   list_foreach(&list, iterator)
   {
       MYUNIT_ASSERT_TRUE(mynode_check(iterator,nodecount));
       nodecount++;
   }


   // POSTCONDITIONS :
   // -------------------------------------------------
   MYUNIT_ASSERT_EQUAL(nodecount, NODES);
   MYUNIT_ASSERT_EQUAL(list_size(&list),NODES);
}



/*!
  \brief    Tests the list_foreach macro with an empty list.

  \details  This test case initializes an empty circular doubly linked list and
            then uses the list_foreach macro to iterate through it. It asserts
            that the node count remains zero, the list size is zero, and the
            list is empty.

  \note     This test case verifies the behavior of list_foreach when the list
            is initially empty.
*/
MYUNIT_TESTCASE(foreach_empty)
{
    // PRECONDITIONS :
      // -------------------------------------------------
      list_t list;
      list_node_t *iterator;
      size_t nodecount = 0;
      test_fixture_setup(FIXTURE_EMPTY, &list);


      // EXECUTE TESTCASE :
      // -------------------------------------------------


      // Use the dlist_foreach macro to iterate through the list
      list_foreach(&list, iterator)
      {
          MYUNIT_ASSERT_TRUE(mynode_check(iterator, nodecount));
          nodecount++;
      }

      // POSTCONDITIONS :
      // -------------------------------------------------
      MYUNIT_ASSERT_EQUAL(nodecount, 0);
      MYUNIT_ASSERT_EQUAL(list_size(&list),0);
      MYUNIT_ASSERT_TRUE(list_empty(&list));
}


/*!
    \brief      Tests forward and backward iteration in a circularly linked list.

    \details    This test case verifies the correctness of traversing a circularly
                linked list using `dlist_next` and `dlist_prev`. It checks if each node
                can be accessed sequentially, and ensures that after reaching the end,
                iterating further returns to the start. The iteration is performed step-by-step
                and validated against expected nodes.
*/
MYUNIT_TESTCASE(next_prev_stepbystep)
{
  // PRECONDITIONS :
    // -------------------------------------------------
    list_t list;
    list_node_t *iterator = &list;
    test_fixture_setup(FIXTURE_NORMAL, &list);


    // EXECUTE TESTCASE :
    // -------------------------------------------------

  // Forward iteration using dlist_next
  MYUNIT_ASSERT_EQUAL(iterator, &list);
  iterator = list_next(&list, iterator);
  MYUNIT_ASSERT_TRUE(mynode_check(iterator, NODE0));
  iterator = list_next(&list, iterator);
  MYUNIT_ASSERT_TRUE(mynode_check(iterator, NODE1));
  iterator = list_next(&list, iterator);
  MYUNIT_ASSERT_TRUE(mynode_check(iterator, NODE2));
  iterator = list_next(&list, iterator);
  MYUNIT_ASSERT_EQUAL(iterator, &list);

  // Reverse iteration using dlist_prev
  MYUNIT_ASSERT_EQUAL(iterator, &list);
  iterator = list_prev(&list, iterator);
  MYUNIT_ASSERT_TRUE(mynode_check(iterator, NODE2));
  iterator = list_prev(&list, iterator);
  MYUNIT_ASSERT_TRUE(mynode_check(iterator, NODE1));
  iterator = list_prev(&list, iterator);
  MYUNIT_ASSERT_TRUE(mynode_check(iterator, NODE0));
  iterator = list_prev(&list, iterator);
  MYUNIT_ASSERT_EQUAL(iterator, &list);


  // POSTCONDITIONS :
  // -------------------------------------------------
  MYUNIT_ASSERT_EQUAL(iterator, &list);
}



/*!
   \brief     Tests `list_prev_prev` on an empty list.

   \details   This test case verifies the behavior of the `list_prev_prev` function when
               called on an empty circularly linked list. It checks that the function
               correctly returns the list itself as the "previous previous" node in this
               edge case, as there are no actual previous nodes to traverse.
*/
MYUNIT_TESTCASE(prev_prev_empty) {
   // PRECONDITIONS:
   list_t list;
   list_node_t* result;
   test_fixture_setup(FIXTURE_EMPTY, &list);

   // EXECUTE TESTCASE:
    result = list_prev_prev(&list, &list);

   // POSTCONDITIONS:
   MYUNIT_ASSERT_EQUAL(result, &list);
}

/*!
  \brief    Tests `list_prev_prev` on a list with a single node.

  \details  This test case verifies the behavior of the `list_prev_prev` function when
             called on a circularly linked list containing only one node. It checks that
             the function correctly returns the single node itself as the "previous previous"
             node, as it's the only node available in the list.
*/
MYUNIT_TESTCASE(prev_prev_1_node)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    list_t list;
    list_node_t* result;
    list_init(&list);
    list_push_back(&list,&mynodes[NODE0].node);

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    result = list_prev_prev(&list, &mynodes[NODE0].node);

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(result, &mynodes[NODE0].node);
}

/*!
 \brief   Tests `list_prev_prev` on a list with two nodes.

 \details This test case verifies the behavior of the `list_prev_prev` function when
          called on a circularly linked list containing two nodes (NODE0 and NODE1).
          It checks that the function correctly returns the second node (NODE1) as the
          "previous previous" node of the first node (NODE0).
*/
MYUNIT_TESTCASE(prev_prev_2_nodes)
{
   // PRECONDITIONS:
   list_t list;
   list_node_t* result;
   list_init(&list);
   list_push_back(&list,&mynodes[NODE0].node);
   list_push_back(&list,&mynodes[NODE1].node);

   // EXECUTE TESTCASE:
   result = list_prev_prev(&list, &mynodes[NODE0].node);

   // POSTCONDITIONS:
   MYUNIT_ASSERT_EQUAL(result, &mynodes[NODE1].node);
}




/*!
     \brief   Performs initial checks on all nodes in the `mynodes` array.

     \details This test case iterates through the `mynodes` array and performs the following checks for each node:
          - Verifies that the `mynode_check` function returns `true` for the node, indicating that the node is valid.
          - Asserts that the `next` pointer of the node is 0, indicating that it is not yet linked to any other node.
          - Asserts that the `prev` pointer of the node is 0, indicating that it is not yet linked to any other node.

          This test case is designed to ensure that the nodes are initialized correctly before any list operations are performed.
*/
MYUNIT_TESTCASE(initial_check_of_all_nodes)
{
    int idx;

    for (idx = NODE0; idx < NODES; idx++)
    {
        MYUNIT_ASSERT_EQUAL(mynode_check(&mynodes[idx].node,idx), true);
        MYUNIT_ASSERT_EQUAL(mynodes[idx].node.next, 0);

#if ( UNITTEST_LIST_TYPE == UNITTEST_LIST_TYPE_DLIST )
        MYUNIT_ASSERT_EQUAL(mynodes[idx].node.prev, 0);
#endif

    }
}


/*!
 \brief Checks if a newly initialized list is in the expected initial state.

 \details This function performs a series of assertions to verify that a list
          immediately after initialization is empty and that its iterators and
          accessors return the list itself, indicating an empty list.

 \param list A pointer to the list to be checked.

 \return True if all assertions pass, indicating the list is correctly initialized;
         false otherwise.
*/
bool list_check_initialized(list_t* list)
{

return true;
}


/*!
    \brief      Tests the initialization of a circular doubly linked list.
    \details    This test case verifies that a newly initialized `list_t`:
                     - Is empty (returns true from `list_empty`).
                     - Has a size of zero (returns 0 from `list_size`).
                     - Behaves correctly in its circular nature by ensuring that the next and
                       previous pointers of the sentinel node (the list itself) refer back to itself.
                     - The `list_begin`, `list_front`, `list_end`, and `list_back` functions all return the sentinel node itself.
*/
MYUNIT_TESTCASE(list_initialization)
{
    list_t list;
    list_init(&list);

    MYUNIT_ASSERT_TRUE(list_check_initialized(&list));
}



/*!
    \brief      Tests front and back node access in a circularly linked list with two nodes.

    \details    This test case verifies that accessing the first and last nodes of a
                circularly linked list using `list_front` and `list_back` functions works correctly.
                The list is initialized with exactly two nodes, ensuring proper functionality
                of front and back access methods in this scenario.
*/
MYUNIT_TESTCASE(front_back_two_nodes)
{
  // PRECONDITIONS:
    list_t list;
    list_node_t* node;
    list_init(&list);
    list_push_back(&list,&mynodes[NODE0].node);
    list_push_back(&list,&mynodes[NODE1].node);

    node = NULL;


  // Test dlist_front()
  node = list_front(&list);
  mynode_check(node, NODE0);

  node = NULL;

  // Test dlist_back()
  node = list_back(&list);
  mynode_check(node, NODE1);
}

/*!
    \brief      Tests front and back node access in a circularly linked list with a single node.

    \details    This test case verifies that accessing the first (and only) node of a
                circularly linked list using `list_front` and `list_back` functions works correctly.
                The list is initialized with exactly one node, ensuring proper functionality
                of front and back access methods in this minimal scenario.
*/
MYUNIT_TESTCASE(front_back_single_node)
{
  // PRECONDITIONS:
    list_t list;
    list_node_t* node;
    list_init(&list);

    list_push_back(&list,&mynodes[NODE0].node);
/*
inlined from ‘myunit_testcase_front_back_single_node’ at ../src/myunit_list.c:390:5:
../src/dlist.h:93:16: warning: storing the address of local variable ‘list’ in ‘mynodes[0].node.prev’ [-Wdangling-pointer=]
   93 |     node->prev = list->prev;
      |     ~~~~~~~~~~~^~~~~~~~~~~~
../src/myunit_list.c: In function ‘myunit_testcase_front_back_single_node’:
../src/myunit_list.c:388:12: note: ‘list’ declared here
  388 |     list_t list;
      |            ^~~~
../src/myunit_list.c:77:17: note: ‘mynodes’ declared here
   77 | static mynode_t mynodes[NODES] = {
      |                 ^~~~~~~
*/

  node = NULL;

  // Test dlist_front()
  node = list_front(&list);
  mynode_check(node, NODE0);

  node = NULL;

  // Test dlist_back()
  node = list_back(&list);
  mynode_check(node, NODE0);
}



/*!
 \brief Tests the push_back and pop_back operations on a list.

 \details This test case initializes an empty list, then pushes several nodes onto the back
         of the list using `list_push_back`. It then verifies the size of the list and
         the value of the last node.  The test then repeatedly pops nodes from the back
         using `list_pop_back`, verifying the size of the list and the value of the
         last node after each pop.  Finally, it verifies that the list is empty and
         correctly initialized after all nodes have been popped.

 \param None

 \return None
*/
MYUNIT_TESTCASE(push_back_pop_back)
{
    list_t list;
    list_init(&list);

    MYUNIT_ASSERT_TRUE(list_check_initialized(&list));

    list_push_back(&list,&mynodes[NODE0].node);
    list_push_back(&list,&mynodes[NODE1].node);
    list_push_back(&list,&mynodes[NODE2].node);

    MYUNIT_ASSERT_EQUAL(list_size(&list),NODES);

    MYUNIT_ASSERT_TRUE( mynode_check(list_back(&list), NODE2) );
    list_pop_back(&list);
    MYUNIT_ASSERT_EQUAL(list_size(&list),2);;

    MYUNIT_ASSERT_TRUE( mynode_check(list_back(&list), NODE1) );
    list_pop_back(&list);
    MYUNIT_ASSERT_EQUAL(list_size(&list),1);

    MYUNIT_ASSERT_TRUE( mynode_check(list_back(&list), NODE0) );
    list_pop_back(&list);
    MYUNIT_ASSERT_EQUAL(list_size(&list),0);


    MYUNIT_ASSERT_TRUE(list_check_initialized(&list));
}

/*!
 \brief Tests the push_back and pop_front operations on a list.

 \details This test case initializes an empty list, then pushes several nodes onto the back
        of the list using `list_push_back`. It then verifies the size of the list and
        the value of the first node. The test then repeatedly pops nodes from the front
        using `list_pop_front`, verifying the size of the list and the value of the
        first node after each pop. Finally, it verifies that the list is empty and
        correctly initialized after all nodes have been popped.
*/
MYUNIT_TESTCASE(push_back_pop_front)
{
    list_t list;
    list_init(&list);

    MYUNIT_ASSERT_TRUE(list_check_initialized(&list));

    list_push_back(&list,&mynodes[NODE0].node);
    list_push_back(&list,&mynodes[NODE1].node);
    list_push_back(&list,&mynodes[NODE2].node);

    MYUNIT_ASSERT_EQUAL(list_size(&list),3);

    MYUNIT_ASSERT_TRUE( mynode_check(list_front(&list), NODE0) );
    list_pop_front(&list);
    MYUNIT_ASSERT_EQUAL(list_size(&list),2);;

    MYUNIT_ASSERT_TRUE( mynode_check(list_front(&list), NODE1) );
    list_pop_front(&list);
    MYUNIT_ASSERT_EQUAL(list_size(&list),1);

    MYUNIT_ASSERT_TRUE( mynode_check(list_front(&list), NODE2) );
    list_pop_front(&list);
    MYUNIT_ASSERT_EQUAL(list_size(&list),0);


    MYUNIT_ASSERT_TRUE(list_check_initialized(&list));
}


/*!
 \brief Tests the push_front and pop_front operations on a list.

 \details This test case initializes an empty list, then pushes several nodes onto the front
       of the list using `list_push_front`. It then verifies the size of the list and
       the value of the first node. The test then repeatedly pops nodes from the front
       using `list_pop_front`, verifying the size of the list and the value of the
       first node after each pop. Finally, it verifies that the list is empty and
       correctly initialized after all nodes have been popped.
*/
MYUNIT_TESTCASE(push_front_pop_front)
{
    list_t list;
    list_init(&list);

    MYUNIT_ASSERT_TRUE(list_check_initialized(&list));

    list_push_front(&list,&mynodes[NODE0].node);
    list_push_front(&list,&mynodes[NODE1].node);
    list_push_front(&list,&mynodes[NODE2].node);

    MYUNIT_ASSERT_EQUAL(list_size(&list),3);

    MYUNIT_ASSERT_TRUE( mynode_check(list_front(&list), NODE2) );
    list_pop_front(&list);
    MYUNIT_ASSERT_EQUAL(list_size(&list),2);;

    MYUNIT_ASSERT_TRUE( mynode_check(list_front(&list), NODE1) );
    list_pop_front(&list);
    MYUNIT_ASSERT_EQUAL(list_size(&list),1);

    MYUNIT_ASSERT_TRUE( mynode_check(list_front(&list), NODE0) );
    list_pop_front(&list);
    MYUNIT_ASSERT_EQUAL(list_size(&list),0);


    MYUNIT_ASSERT_TRUE(list_check_initialized(&list));
}


/*!
 \brief Tests the push_front and pop_back operations on a list.

 \details This test case initializes an empty list, then pushes several nodes onto the front
      of the list using `list_push_front`. It then verifies the size of the list and
      the value of the last node. The test then repeatedly pops nodes from the back
      using `list_pop_back`, verifying the size of the list and the value of the
      last node after each pop. Finally, it verifies that the list is empty and
      correctly initialized after all nodes have been popped.
*/
MYUNIT_TESTCASE(push_front_pop_back)
{
    list_t list;
    list_init(&list);

    MYUNIT_ASSERT_TRUE(list_check_initialized(&list));

    list_push_front(&list,&mynodes[NODE0].node);
    list_push_front(&list,&mynodes[NODE1].node);
    list_push_front(&list,&mynodes[NODE2].node);

    MYUNIT_ASSERT_EQUAL(list_size(&list),3);

    MYUNIT_ASSERT_TRUE( mynode_check(list_back(&list), NODE0) );
    list_pop_back(&list);
    MYUNIT_ASSERT_EQUAL(list_size(&list),2);;

    MYUNIT_ASSERT_TRUE( mynode_check(list_back(&list), NODE1) );
    list_pop_back(&list);
    MYUNIT_ASSERT_EQUAL(list_size(&list),1);

    MYUNIT_ASSERT_TRUE( mynode_check(list_back(&list), NODE2) );
    list_pop_back(&list);
    MYUNIT_ASSERT_EQUAL(list_size(&list),0);


    MYUNIT_ASSERT_TRUE(list_check_initialized(&list));
}



/*!
    \brief      Tests inserting a node after another in a circularly linked list.

    \details    This test case verifies that a new node can be correctly inserted
                immediately after an existing node using the `list_insert_after` function.
                It initializes a list with two nodes and then inserts a third node
                between them. The correctness of the insertion is validated by checking
                the order and size of the list.
*/
MYUNIT_TESTCASE(insert_after)
{
  // PRECONDITIONS:

   list_t list;
   list_node_t *node;
   list_init(&list);

   // 1.) List initialized with nodes 0 and 2
   list_push_back(&list,&mynodes[NODE0].node);
   list_push_back(&list,&mynodes[NODE2].node);

   // 3.) Check size
  MYUNIT_ASSERT_EQUAL(list_size(&list), 2);

  // 4.) Insert node 1 after node 0
  list_insert_after(&list, &mynodes[NODE0].node, &mynodes[NODE1].node  );

  // 5.) Check size
  MYUNIT_ASSERT_EQUAL(list_size(&list), NODES);

  // 6.) Check node order
  node = list_begin(&list);
  MYUNIT_ASSERT_TRUE( mynode_check(node, NODE0) );
  node = list_next(&list,node);
  MYUNIT_ASSERT_TRUE( mynode_check(node, NODE1) );
  node = list_next(&list,node);
  MYUNIT_ASSERT_TRUE( mynode_check(node, NODE2) );

  node = list_next(&list,node);
  MYUNIT_ASSERT_TRUE( node == list_end(&list) );
  node = list_prev(&list,node);
  MYUNIT_ASSERT_TRUE( mynode_check(node, NODE2) );
  node = list_prev(&list,node);
  MYUNIT_ASSERT_TRUE( mynode_check(node, NODE1) );
  node = list_prev(&list,node);
  MYUNIT_ASSERT_TRUE( mynode_check(node, NODE0) );
  node = list_prev(&list,node);
  MYUNIT_ASSERT_TRUE( node == list_end(&list) );

}

/*!
    \brief      Tests inserting a node before another in a circularly linked list.

    \details    This test case verifies that a new node can be correctly inserted
                immediately before an existing node using the `list_insert_before` function.
                It initializes a list with two nodes and then inserts a third node
                between them. The correctness of the insertion is validated by checking
                the order and size of the list.
*/
MYUNIT_TESTCASE(insert_before)
{
  // PRECONDITIONS:

   list_t list;
   list_node_t *node;
   list_init(&list);

   // 1.) List initialized with nodes 0 and 2
   list_push_back(&list,&mynodes[NODE0].node);
   list_push_back(&list,&mynodes[NODE2].node);

   // 3.) Check size
  MYUNIT_ASSERT_EQUAL(list_size(&list), 2);

  // 4.) Insert node 1 before node 2
  list_insert_before(&list, &mynodes[NODE2].node, &mynodes[NODE1].node  );

  // 5.) Check size
  MYUNIT_ASSERT_EQUAL(list_size(&list), NODES);

  // 6.) Check node order
  node = list_begin(&list);
  MYUNIT_ASSERT_TRUE( mynode_check(node, NODE0) );
  node = list_next(&list,node);
  MYUNIT_ASSERT_TRUE( mynode_check(node, NODE1) );
  node = list_next(&list,node);
  MYUNIT_ASSERT_TRUE( mynode_check(node, NODE2) );

  node = list_next(&list,node);
  MYUNIT_ASSERT_TRUE( node == list_end(&list) );
  node = list_prev(&list,node);
  MYUNIT_ASSERT_TRUE( mynode_check(node, NODE2) );
  node = list_prev(&list,node);
  MYUNIT_ASSERT_TRUE( mynode_check(node, NODE1) );
  node = list_prev(&list,node);
  MYUNIT_ASSERT_TRUE( mynode_check(node, NODE0) );
  node = list_prev(&list,node);
  MYUNIT_ASSERT_TRUE( node == list_end(&list) );

}



/*!
    \brief      Tests node removal from a circularly linked list.

    \details    This test case verifies that nodes can be correctly removed
                from a circularly linked list using the `list_erase` function. It initializes
                the list with several nodes and then removes one, ensuring that the list's
                integrity is maintained after the deletion. The correctness of removal is validated
                by checking the order and size of the remaining list.
*/
MYUNIT_TESTCASE(erase)
{
  // PRECONDITIONS:

   list_t list;
   list_node_t* node;
   test_fixture_setup(FIXTURE_NORMAL, &list);

   MYUNIT_ASSERT_EQUAL(list_size(&list), NODES);

   MYUNIT_ASSERT_DIFFER(list_find(&list,&mynodes[NODE1].node),NULL);

   list_erase(&list,&mynodes[NODE1].node);

   MYUNIT_ASSERT_EQUAL(list_size(&list), 2);
   MYUNIT_ASSERT_EQUAL(list_find(&list,&mynodes[NODE1].node),NULL);

   node = list_front(&list);

   MYUNIT_ASSERT_DIFFER(list_find(&list,node),NULL);
   list_erase(&list,node);

   MYUNIT_ASSERT_EQUAL(list_size(&list), 1);
   MYUNIT_ASSERT_EQUAL(list_find(&list,node),NULL);

   node = list_back(&list);


   MYUNIT_ASSERT_DIFFER(list_find(&list,node),NULL);
   list_erase(&list,node);

   MYUNIT_ASSERT_EQUAL(list_size(&list), 0);
   MYUNIT_ASSERT_EQUAL(list_find(&list,node),NULL);
   MYUNIT_ASSERT_TRUE(list_empty(&list));
}





/*!
   \brief     Tests finding a node in an empty list.

   \details   Initializes an empty list and attempts to find a node within it.
               Asserts that the returned pointer is NULL, as the list is empty.
*/
MYUNIT_TESTCASE(find_empty_list)
{
   // PRECONDITIONS :
   // -------------------------------------------------
   list_t list;
   list_node_t* found;
   test_fixture_setup(FIXTURE_EMPTY, &list);

   // EXECUTE TESTCASE :
   // -------------------------------------------------
   found = list_find(&list, &mynodes[NODE0].node);

   // POSTCONDITIONS :
   // -------------------------------------------------
   MYUNIT_ASSERT_IS_NULL(found);
}

/*!
  \brief    Tests finding a node that exists in the list.

  \details  Initializes a list with several nodes, then searches for a specific node
             that is known to be present. Asserts that the found node is not NULL and
             that it matches the expected node.
*/
MYUNIT_TESTCASE(find_node_present)
{
   // PRECONDITIONS :
   // -------------------------------------------------
   list_t list;
   list_node_t* found;
   test_fixture_setup(FIXTURE_NORMAL, &list);

   // EXECUTE TESTCASE :
   // -------------------------------------------------
   found = list_find(&list, &mynodes[NODE1].node);

   // POSTCONDITIONS :
   // -------------------------------------------------
   MYUNIT_ASSERT_NOT_NULL(found);
   MYUNIT_ASSERT_EQUAL(found, &mynodes[NODE1].node);
}

/*!
 \brief   Tests finding a node that does not exist in the list.

 \details Initializes a list with several nodes, then searches for a node that is
          not present in the list. Asserts that the returned pointer is NULL.
*/
MYUNIT_TESTCASE(find_node_not_present)
{
   // PRECONDITIONS :
   // -------------------------------------------------
   list_t list;
   list_node_t* found;
   list_init(&list);
   list_push_back(&list,&mynodes[NODE0].node);
   list_push_back(&list,&mynodes[NODE1].node);

   // EXECUTE TESTCASE :
   // -------------------------------------------------
   found = list_find(&list, &mynodes[NODE2].node);

   // POSTCONDITIONS :
   // -------------------------------------------------
   MYUNIT_ASSERT_IS_NULL(found);
}

/*!
 \brief  Tests finding the first node in the list.

 \details Initializes a list with several nodes and searches for the first node.
         Asserts that the found node is not NULL, that it matches the expected first node,
         and that it is the same as the node returned by `list_front`.
*/
MYUNIT_TESTCASE(find_first_node)
{
   // PRECONDITIONS :
   // -------------------------------------------------
   list_t list;
   list_node_t* found;
   test_fixture_setup(FIXTURE_NORMAL, &list);

   // EXECUTE TESTCASE :
   // -------------------------------------------------
   found = list_find(&list, &mynodes[NODE0].node);

   // POSTCONDITIONS :
   // -------------------------------------------------
   MYUNIT_ASSERT_NOT_NULL(found);
   MYUNIT_ASSERT_EQUAL(found, &mynodes[NODE0].node);
   MYUNIT_ASSERT_EQUAL(found, list_front(&list));
}

/*!
 \brief Tests finding the last node in the list.

 \details Initializes a list with several nodes and searches for the last node.
         Asserts that the found node is not NULL, that it matches the expected last node,
         and that it is the same as the node returned by `list_back`.
*/
MYUNIT_TESTCASE(find_last_node)
{
    // PRECONDITIONS :
    // -------------------------------------------------
    list_t list;
    list_node_t* found;
    test_fixture_setup(FIXTURE_NORMAL, &list);

    // EXECUTE TESTCASE :
    // -------------------------------------------------
    found = list_find(&list, &mynodes[NODE2].node);

    // POSTCONDITIONS :
    // -------------------------------------------------
    MYUNIT_ASSERT_NOT_NULL(found);
    MYUNIT_ASSERT_EQUAL(found, &mynodes[NODE2].node);
    MYUNIT_ASSERT_EQUAL(found, list_back(&list));
}

/*!
 \brief Tests the list_size function on an empty list.

 \details This test case initializes an empty list and then calls the `list_size` function
      to get the size of the list. It asserts that the size of an empty list is 0.
*/
MYUNIT_TESTCASE(size_empty_list) {
    // PRECONDITIONS :
    // -------------------------------------------------
    list_t list;
    size_t size;
    list_init(&list);

    // EXECUTE TESTCASE :
    // -------------------------------------------------
    size = list_size(&list);

    // POSTCONDITIONS :
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(size, 0);
}



/*!
    \brief      Tests list size calculation with multiple elements.

    \details    This test case verifies that the size of a circularly linked list
                is correctly calculated when it contains multiple nodes. It initializes
                the list with all possible nodes (NODE0, NODE1, NODE2) and checks if
                both `list_size` function and manual iteration yield consistent results.
*/
MYUNIT_TESTCASE(size_multiple_elements) {
    // PRECONDITIONS :
    // -------------------------------------------------
    list_t list;
    size_t size;
    test_fixture_setup(FIXTURE_NORMAL, &list);

    // EXECUTE TESTCASE :
    // -------------------------------------------------
    size = list_size(&list);

    // POSTCONDITIONS :
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(size, 3);
}

/*!
    \brief      Sets up the unit test suite environment.

    \details    This function initializes necessary resources and configurations
                required to run the unit tests. It prepares any global structures,
                allocates memory, or performs other setup tasks needed before executing
                individual test cases.
*/
void myunit_testsuite_setup()
{


}
/*!
    \brief      Cleans up resources after unit test suite execution.

    \details    This function deallocates any memory, releases resources, and performs
                necessary cleanup tasks that were set up during the initialization of the
                test suite. It ensures that no residual state is left behind that could
                affect subsequent tests or system stability.
*/
void myunit_testsuite_teardown()
{

}


#define MYUNIT_TESTSUITE_EXP(x) \
    MYUNIT_TESTSUITE(x)

MYUNIT_TESTSUITE_EXP(myunit_list_type)
{
    MYUNIT_TESTSUITE_BEGIN();

    MYUNIT_EXEC_TESTCASE(initial_check_of_all_nodes);
    MYUNIT_EXEC_TESTCASE(list_initialization);

    MYUNIT_EXEC_TESTCASE(foreach);
    MYUNIT_EXEC_TESTCASE(foreach_empty);

    MYUNIT_EXEC_TESTCASE(next_prev_stepbystep);
    MYUNIT_EXEC_TESTCASE(prev_prev_empty);
    MYUNIT_EXEC_TESTCASE(prev_prev_1_node);
    MYUNIT_EXEC_TESTCASE(prev_prev_2_nodes);

    MYUNIT_EXEC_TESTCASE(front_back_two_nodes);
    MYUNIT_EXEC_TESTCASE(front_back_single_node);

    MYUNIT_EXEC_TESTCASE(push_back_pop_back);
    MYUNIT_EXEC_TESTCASE(push_back_pop_front);
    MYUNIT_EXEC_TESTCASE(push_front_pop_front);
    MYUNIT_EXEC_TESTCASE(push_front_pop_back);

    MYUNIT_EXEC_TESTCASE(insert_after);
    MYUNIT_EXEC_TESTCASE(insert_before);

    MYUNIT_EXEC_TESTCASE(erase);

    MYUNIT_EXEC_TESTCASE(find_empty_list);
    MYUNIT_EXEC_TESTCASE(find_node_present);
    MYUNIT_EXEC_TESTCASE(find_node_not_present);
    MYUNIT_EXEC_TESTCASE(find_first_node);
    MYUNIT_EXEC_TESTCASE(find_last_node);

    MYUNIT_EXEC_TESTCASE(size_empty_list);
    MYUNIT_EXEC_TESTCASE(size_multiple_elements);

    MYUNIT_TESTSUITE_END();
}
