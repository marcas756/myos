/*
 * unittest_rtimer.c
 *
 *  Created on: 07.07.2021
 *      Author: marco
 */

#include "unittest.h"
#include "myos.h"

rtimer_t rtimer;

void rtimer_callback(void* data)
{
   int *tmp = data;

   printf("%d\n",*tmp);
   (*tmp)++;

   rtimer_reset(&rtimer);

}

UNITTEST_TESTCASE(rtimer)
{
    /* PRECONDITIONS */

   rtimer_module_init();

    int tmp = 123;

    while(!rtimer_lock()) {};

    rtimer_start(&rtimer,RTIMER_TICKS_PER_SEC,rtimer_callback,&tmp);

    while(1){}


    /* POSTCONDITIONS */
}


/* add additional unit test cases here */



UNITTEST_TESTSUITE(/* add name for unit test suite here */)
{
    UNITTEST_TESTSUITE_BEGIN();

    UNITTEST_EXEC_TESTCASE(rtimer);

    /* add additional unit test cases to be executed here */

    UNITTEST_TESTSUITE_END();
}
