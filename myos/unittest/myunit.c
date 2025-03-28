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
    \file myunit.c
    \brief A lightweight unit testing framework for embedded systems.
    \details
*/

#include "myunit.h"

char *myunit_testsuite_name;                 /*!< Name of the current test suite */
char *myunit_testcase_name;                  /*!< Name of the current test case */
int myunit_testsuite_assert_fail_count;      /*!< Failed assertions in the test suite. */
int myunit_testsuite_assert_success_count;   /*!< Successful assertions in the test suite. */
int myunit_testcase_assert_success_count;    /*!< Successful assertions in the current test case. Reset after each test case. */
int myunit_testcase_assert_fail_count;       /*!< Failed assertions in the current test case. Reset after each test case.*/
int myunit_testcase_success_count;           /*!< Successfully completed test cases in the test suite. */
int myunit_testcase_fail_count;              /*!< Failed test cases in the test suite. */
int myunit_sequence_fail_count;              /*!< Failed test cases in a test sequence */

void (*myunit_action)(void) = NULL;

MYUNIT_CHECKPOINTS(MYUNIT_CHECKPOINT_SIZE);

void myunit_exec_testcase(void(*testcase)(void), char* name)
{
       myunit_testcase_assert_fail_count  = 0;
       myunit_testcase_assert_success_count  = 0;
       myunit_testcase_name = name;
       MYUNIT_PRINTF("%s %s %s\n",myunit_testcase_begin_tag,myunit_testsuite_name,name);
       testcase();
       MYUNIT_PRINTF("%s %s %s %d %d\n",myunit_testcase_end_tag,myunit_testsuite_name,name,myunit_testcase_assert_fail_count,myunit_testcase_assert_success_count);
       myunit_testsuite_assert_fail_count+=myunit_testcase_assert_fail_count;
       myunit_testsuite_assert_success_count+=myunit_testcase_assert_success_count;
       (myunit_testcase_assert_fail_count)?(myunit_testcase_fail_count++):(myunit_testcase_success_count++);
}
