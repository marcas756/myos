/*! \copyright
    Copyright (c) 2017, marcas756@gmail.com
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
    \file       unittest_template.c

    \brief

    \details    A unit test is used in software development to test the
                functional units of computer programs, i.e. to test the proper functionality.
                The term unit test is also understood as an early test phase, where the innermost,
                most detailed components of the software are tested.
*/




#include "unittest.h"
#include "timer.h"
#include <stdio.h>




UNITTEST_TESTCASE(timer)
{
    /* PRECONDITIONS */
   timer_t timer;
   timer_start(&timer, TIMESTAMP_TICKS_PER_SEC);
   int count = 0;

    /* TEST */

   while(1)
   {
      while(!timer_expired(&timer)){};

      timer_restart(&timer);
      printf("%d\n",count++);


   }


    /* POSTCONDITIONS */
}


/* add additional unit test cases here */



UNITTEST_TESTSUITE(/* add name for unit test suite here */)
{
    UNITTEST_TESTSUITE_BEGIN();

    UNITTEST_EXEC_TESTCASE(timer);

    /* add additional unit test cases to be executed here */

    UNITTEST_TESTSUITE_END();
}
