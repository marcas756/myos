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
#include "myunit.h"
#include <stdint.h>
#include "itempool.h"

ITEMPOOL_TYPEDEF(bytepool,uint8_t,3);
ITEMPOOL_TYPEDEF(shortpool,uint16_t,3);
ITEMPOOL_TYPEDEF(intpool,uint32_t,3);
ITEMPOOL_TYPEDEF(longpool,uint64_t,3);

#define STATUS_GARBAGE 0xAA
#define ITEM_GARBAGE 0xAAAAAAAA



typedef enum {
    PATTERN_GARBAGE=0,
    PATTERN_GARBAGE_INITIALIZED,
    PATTERN_STATUS_ENUMERATION,
    PATTERN_ITEM_ENUMERATION,

}pattern_t;

const ITEMPOOL_T(intpool) patterns [] = {
        {{ STATUS_GARBAGE,    STATUS_GARBAGE,    STATUS_GARBAGE     },{ ITEM_GARBAGE,ITEM_GARBAGE,ITEM_GARBAGE }}, //PATTERN_GARBAGE
        {{ ITEMPOOL_ITEM_FREE,ITEMPOOL_ITEM_FREE,ITEMPOOL_ITEM_FREE },{ ITEM_GARBAGE,ITEM_GARBAGE,ITEM_GARBAGE }}, //PATTERN_GARBAGE_INITIALIZED
        {{ 0,                 1,                 2                  },{ ITEM_GARBAGE,ITEM_GARBAGE,ITEM_GARBAGE }}, //PATTERN_STATUS_ENUMERATION
        {{ STATUS_GARBAGE,    STATUS_GARBAGE,    STATUS_GARBAGE     },{ 0,           1,           2            }}, //PATTERN_ITEM_ENUMERATION



};




MYUNIT_TESTCASE(itempool_size_returns_pool_capacity)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool;

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_SIZE(intpool),3);

    // POSTCONDITIONS:
    // -------------------------------------------------

}

MYUNIT_TESTCASE(itempool_size_is_independent_of_item_type_size)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(bytepool) bytepool;
    ITEMPOOL_T(shortpool) shortpool;
    ITEMPOOL_T(intpool) intpool;
    ITEMPOOL_T(longpool) longpool;

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_SIZE(intpool),ITEMPOOL_SIZE(bytepool));
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_SIZE(intpool),ITEMPOOL_SIZE(shortpool));
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_SIZE(intpool),ITEMPOOL_SIZE(longpool));

    // POSTCONDITIONS:
    // -------------------------------------------------

}


MYUNIT_TESTCASE(itempool_size_matches_manual_status_array_length)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool;

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_SIZE(intpool),sizeof(intpool.items)/sizeof(*intpool.items));
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_SIZE(intpool),sizeof(intpool.status)/sizeof(*intpool.status));

    // POSTCONDITIONS:
    // -------------------------------------------------

}



MYUNIT_TESTCASE(itempool_item_size_matches_expected_type_size)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(bytepool) bytepool;
    ITEMPOOL_T(shortpool) shortpool;
    ITEMPOOL_T(intpool) intpool;
    ITEMPOOL_T(longpool) longpool;

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEM_SIZE(bytepool),sizeof(uint8_t));
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEM_SIZE(shortpool),sizeof(uint16_t));
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEM_SIZE(intpool),sizeof(uint32_t));
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEM_SIZE(longpool),sizeof(uint64_t));

    // POSTCONDITIONS:
    // -------------------------------------------------

}



MYUNIT_TESTCASE(itempool_item_size_varies_with_type)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(bytepool) bytepool;
    ITEMPOOL_T(shortpool) shortpool;
    ITEMPOOL_T(intpool) intpool;
    ITEMPOOL_T(longpool) longpool;

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    /*
        Not guaranteed to return different values for integer types — it depends on platform, ABI, alignment.
        Different sizes — this is common and expected on most modern platforms.
        However, on exotic, embedded, or non-standard platforms, it's possible (though rare) for:
        All uint*_t types to have padding or be treated the same size by ABI constraints
        For example, sizeof(uint8_t) and sizeof(uint16_t) might both return 2 if alignment constraints force them into 16-bit slots
    */

    MYUNIT_ASSERT_DIFFER(ITEMPOOL_ITEM_SIZE(bytepool),ITEMPOOL_ITEM_SIZE(shortpool));
    MYUNIT_ASSERT_DIFFER(ITEMPOOL_ITEM_SIZE(bytepool),ITEMPOOL_ITEM_SIZE(intpool));
    MYUNIT_ASSERT_DIFFER(ITEMPOOL_ITEM_SIZE(bytepool),ITEMPOOL_ITEM_SIZE(longpool));

    MYUNIT_ASSERT_DIFFER(ITEMPOOL_ITEM_SIZE(shortpool),ITEMPOOL_ITEM_SIZE(intpool));
    MYUNIT_ASSERT_DIFFER(ITEMPOOL_ITEM_SIZE(shortpool),ITEMPOOL_ITEM_SIZE(longpool));

    MYUNIT_ASSERT_DIFFER(ITEMPOOL_ITEM_SIZE(intpool),ITEMPOOL_ITEM_SIZE(longpool));


    // POSTCONDITIONS:
    // -------------------------------------------------

}

MYUNIT_TESTCASE(itempool_status_returns_valid_pointer)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool;

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    MYUNIT_ASSERT_NOT_NULL(ITEMPOOL_STATUS(intpool));


    // POSTCONDITIONS:
    // -------------------------------------------------

}


MYUNIT_TESTCASE(itempool_status_points_to_correct_memory_region)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool;

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool),intpool.status);


    // POSTCONDITIONS:
    // -------------------------------------------------


}



MYUNIT_TESTCASE(itempool_status_allows_direct_modification_of_status_entries)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool = patterns[PATTERN_GARBAGE];
    MYUNIT_ASSERT_MEM_EQUAL(&intpool,&patterns[PATTERN_GARBAGE], sizeof(ITEMPOOL_T(intpool)));

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    ITEMPOOL_STATUS(intpool)[0] = ITEMPOOL_ITEM_FREE;
    ITEMPOOL_STATUS(intpool)[1] = ITEMPOOL_ITEM_FREE;
    ITEMPOOL_STATUS(intpool)[2] = ITEMPOOL_ITEM_FREE;

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_MEM_EQUAL(&intpool,&patterns[PATTERN_GARBAGE_INITIALIZED], sizeof(ITEMPOOL_T(intpool)));
}


MYUNIT_TESTCASE(itempool_status_allows_access_to_all_status_fields)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool = patterns[PATTERN_GARBAGE];
    MYUNIT_ASSERT_MEM_EQUAL(&intpool,&patterns[PATTERN_GARBAGE], sizeof(ITEMPOOL_T(intpool)));

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    for(int idx = 0; idx < ITEMPOOL_SIZE(intpool); idx++)
    {
        ITEMPOOL_STATUS(intpool)[idx] = idx;
    }

    MYUNIT_ASSERT_MEM_EQUAL(&intpool,&patterns[PATTERN_STATUS_ENUMERATION], sizeof(ITEMPOOL_T(intpool)));


    // POSTCONDITIONS:
    // -------------------------------------------------

}



MYUNIT_TESTCASE(itempool_items_returns_valid_pointer)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool;

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    MYUNIT_ASSERT_NOT_NULL(ITEMPOOL_ITEMS(intpool));

    // POSTCONDITIONS:
    // -------------------------------------------------

}



MYUNIT_TESTCASE(itempool_items_points_to_correct_memory_region)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool;

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEMS(intpool),intpool.items);

    // POSTCONDITIONS:
    // -------------------------------------------------

}



MYUNIT_TESTCASE(itempool_items_allows_access_to_all_items)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool = patterns[PATTERN_GARBAGE];
    MYUNIT_ASSERT_MEM_EQUAL(&intpool,&patterns[PATTERN_GARBAGE], sizeof(ITEMPOOL_T(intpool)));

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    for(int idx = 0; idx < ITEMPOOL_SIZE(intpool); idx++)
    {
        ITEMPOOL_ITEMS(intpool)[idx] = idx;
    }

    MYUNIT_ASSERT_MEM_EQUAL(&intpool,&patterns[PATTERN_ITEM_ENUMERATION], sizeof(ITEMPOOL_T(intpool)));


    // POSTCONDITIONS:
    // -------------------------------------------------

}


MYUNIT_TESTCASE(itempool_init_sets_all_status_entries_to_free)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool = patterns[PATTERN_GARBAGE];
    MYUNIT_ASSERT_MEM_EQUAL(&intpool,&patterns[PATTERN_GARBAGE], sizeof(ITEMPOOL_T(intpool)));

    // EXECUTE TESTCASE:
    // -------------------------------------------------
    ITEMPOOL_INIT(intpool);


    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_MEM_EQUAL(&intpool,&patterns[PATTERN_GARBAGE_INITIALIZED], sizeof(ITEMPOOL_T(intpool)));
}






MYUNIT_TESTCASE(itempool_alloc_returns_unique_pointers_until_pool_exhausted)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool;
    ITEMPOOL_INIT(intpool);

    // EXECUTE TESTCASE:
    // -------------------------------------------------


    for(int idx = 0; idx < ITEMPOOL_SIZE(intpool); idx++)
    {
       MYUNIT_ASSERT_NOT_NULL(ITEMPOOL_ALLOC(intpool));
    }


    // POSTCONDITIONS:
    // -------------------------------------------------

    MYUNIT_ASSERT_IS_NULL(ITEMPOOL_ALLOC(intpool));
}




MYUNIT_TESTCASE(itempool_alloc_marks_item_as_used_in_status_array)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool;
    ITEMPOOL_INIT(intpool);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    MYUNIT_ASSERT_NOT_NULL(ITEMPOOL_ALLOC(intpool));

    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);

    MYUNIT_ASSERT_NOT_NULL(ITEMPOOL_ALLOC(intpool));

    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);

    MYUNIT_ASSERT_NOT_NULL(ITEMPOOL_ALLOC(intpool));


    // POSTCONDITIONS:
    // -------------------------------------------------

    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_USED);
}



MYUNIT_TESTCASE(itempool_calloc_returns_unique_pointers_until_pool_exhausted)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool;
    ITEMPOOL_INIT(intpool);

    // EXECUTE TESTCASE:
    // -------------------------------------------------


    for(int idx = 0; idx < ITEMPOOL_SIZE(intpool); idx++)
    {
       MYUNIT_ASSERT_NOT_NULL(ITEMPOOL_CALLOC(intpool));
    }


    // POSTCONDITIONS:
    // -------------------------------------------------

    MYUNIT_ASSERT_IS_NULL(ITEMPOOL_CALLOC(intpool));
}

MYUNIT_TESTCASE(itempool_calloc_marks_item_as_used_in_status_array)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool;
    ITEMPOOL_INIT(intpool);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    MYUNIT_ASSERT_NOT_NULL(ITEMPOOL_CALLOC(intpool));

    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);

    MYUNIT_ASSERT_NOT_NULL(ITEMPOOL_CALLOC(intpool));

    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);

    MYUNIT_ASSERT_NOT_NULL(ITEMPOOL_CALLOC(intpool));


    // POSTCONDITIONS:
    // -------------------------------------------------

    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_USED);
}



MYUNIT_TESTCASE(itempool_calloc_zeroes_out_allocated_item_memory)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool = patterns[PATTERN_GARBAGE_INITIALIZED];
    MYUNIT_ASSERT_MEM_EQUAL(&intpool,&patterns[PATTERN_GARBAGE_INITIALIZED], sizeof(ITEMPOOL_T(intpool)));


    // EXECUTE TESTCASE:
    // -------------------------------------------------

    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEMS(intpool)[0], ITEM_GARBAGE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEMS(intpool)[1], ITEM_GARBAGE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEMS(intpool)[2], ITEM_GARBAGE);

    MYUNIT_ASSERT_NOT_NULL(ITEMPOOL_CALLOC(intpool));

    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEMS(intpool)[0], 0);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEMS(intpool)[1], ITEM_GARBAGE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEMS(intpool)[2], ITEM_GARBAGE);

    MYUNIT_ASSERT_NOT_NULL(ITEMPOOL_CALLOC(intpool));

    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEMS(intpool)[0], 0);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEMS(intpool)[1], 0);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEMS(intpool)[2], ITEM_GARBAGE);

    MYUNIT_ASSERT_NOT_NULL(ITEMPOOL_CALLOC(intpool));

    // POSTCONDITIONS:
    // -------------------------------------------------

    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEMS(intpool)[0], 0);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEMS(intpool)[1], 0);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ITEMS(intpool)[2], 0);
}



MYUNIT_TESTCASE(itempool_calloc_returns_unique_zeroed_items)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool = patterns[PATTERN_GARBAGE_INITIALIZED];
    MYUNIT_ASSERT_MEM_EQUAL(&intpool,&patterns[PATTERN_GARBAGE_INITIALIZED], sizeof(ITEMPOOL_T(intpool)));


    // EXECUTE TESTCASE:
    // -------------------------------------------------

    MYUNIT_ASSERT_EQUAL( *(uint32_t*)ITEMPOOL_CALLOC(intpool), 0);
    MYUNIT_ASSERT_EQUAL( *(uint32_t*)ITEMPOOL_CALLOC(intpool), 0);
    MYUNIT_ASSERT_EQUAL( *(uint32_t*)ITEMPOOL_CALLOC(intpool), 0);

    // POSTCONDITIONS:
    // -------------------------------------------------

}



MYUNIT_TESTCASE(itempool_free_marks_status_entry_as_free)
{
    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool;
    ITEMPOOL_INIT(intpool);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    uint32_t *tmp = ITEMPOOL_ALLOC(intpool);

    MYUNIT_ASSERT_NOT_NULL(tmp);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);

    ITEMPOOL_FREE(intpool,tmp);

    // POSTCONDITIONS:
    // -------------------------------------------------
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);

}


MYUNIT_TESTCASE(itempool_free_allows_reallocation_of_freed_item)
{

    // itempool_free_allows_reallocation_of_freed_item
    // itempool_free_frees_correct_index_for_middle_item

    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool;
    ITEMPOOL_INIT(intpool);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);

    // EXECUTE TESTCASE:
    // -------------------------------------------------

    ITEMPOOL_ALLOC(intpool);
    uint32_t *tmp = ITEMPOOL_ALLOC(intpool);
    ITEMPOOL_ALLOC(intpool);

    MYUNIT_ASSERT_NOT_NULL(tmp);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_USED);

    ITEMPOOL_FREE(intpool,tmp);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_USED);

    MYUNIT_ASSERT_EQUAL(ITEMPOOL_ALLOC(intpool), tmp);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_USED);


    // POSTCONDITIONS:
    // -------------------------------------------------
}





MYUNIT_TESTCASE(itempool_free_multiple_items_correctly_marks_all_as_free)
{

    // itempool_free_allows_reallocation_of_freed_item
    // itempool_free_frees_correct_index_for_middle_item

    // PRECONDITIONS:
    // -------------------------------------------------
    ITEMPOOL_T(intpool) intpool;
    ITEMPOOL_INIT(intpool);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);

    // EXECUTE TESTCASE:
    // -------------------------------------------------


    uint32_t *tmp1 = ITEMPOOL_ALLOC(intpool);
    MYUNIT_ASSERT_NOT_NULL(tmp1);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);

    uint32_t *tmp2 = ITEMPOOL_ALLOC(intpool);
    MYUNIT_ASSERT_NOT_NULL(tmp2);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);

    uint32_t *tmp3 = ITEMPOOL_ALLOC(intpool);
    MYUNIT_ASSERT_NOT_NULL(tmp3);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_USED);

    ITEMPOOL_FREE(intpool,tmp2);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_USED);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_USED);

    ITEMPOOL_FREE(intpool,tmp1);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_USED);

    ITEMPOOL_FREE(intpool,tmp3);

    // POSTCONDITIONS:
    // -------------------------------------------------

    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[0], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[1], ITEMPOOL_ITEM_FREE);
    MYUNIT_ASSERT_EQUAL(ITEMPOOL_STATUS(intpool)[2], ITEMPOOL_ITEM_FREE);
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


MYUNIT_TESTSUITE(itempool)
{
    MYUNIT_TESTSUITE_BEGIN();

    MYUNIT_EXEC_TESTCASE(itempool_size_returns_pool_capacity);
    MYUNIT_EXEC_TESTCASE(itempool_size_is_independent_of_item_type_size);
    MYUNIT_EXEC_TESTCASE(itempool_size_matches_manual_status_array_length);
    MYUNIT_EXEC_TESTCASE(itempool_item_size_matches_expected_type_size);

    MYUNIT_EXEC_TESTCASE(itempool_status_returns_valid_pointer);
    MYUNIT_EXEC_TESTCASE(itempool_status_points_to_correct_memory_region);
    MYUNIT_EXEC_TESTCASE(itempool_status_allows_direct_modification_of_status_entries);
    MYUNIT_EXEC_TESTCASE(itempool_status_allows_access_to_all_status_fields);

    MYUNIT_EXEC_TESTCASE(itempool_items_returns_valid_pointer);
    MYUNIT_EXEC_TESTCASE(itempool_items_points_to_correct_memory_region);
    MYUNIT_EXEC_TESTCASE(itempool_items_allows_access_to_all_items);

    MYUNIT_EXEC_TESTCASE(itempool_init_sets_all_status_entries_to_free);

    MYUNIT_EXEC_TESTCASE(itempool_alloc_returns_unique_pointers_until_pool_exhausted);
    MYUNIT_EXEC_TESTCASE(itempool_alloc_marks_item_as_used_in_status_array);

    MYUNIT_EXEC_TESTCASE(itempool_calloc_returns_unique_pointers_until_pool_exhausted);
    MYUNIT_EXEC_TESTCASE(itempool_calloc_marks_item_as_used_in_status_array);
    MYUNIT_EXEC_TESTCASE(itempool_calloc_zeroes_out_allocated_item_memory);
    MYUNIT_EXEC_TESTCASE(itempool_calloc_returns_unique_zeroed_items);

    MYUNIT_EXEC_TESTCASE(itempool_free_marks_status_entry_as_free);
    MYUNIT_EXEC_TESTCASE(itempool_free_allows_reallocation_of_freed_item);
    MYUNIT_EXEC_TESTCASE(itempool_free_multiple_items_correctly_marks_all_as_free);

    MYUNIT_TESTSUITE_END();
}
