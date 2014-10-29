/*! \copyright
    Copyright (c) 2014, marcas756@gmail.com.
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
    \file   unittest_itempool.c

    \brief

    \details
*/

#define UNITTEST_CONF_VERBOSE

#include "unittest.h"
#include "itempool.h"

UNITTEST_TESTSUITE_INIT();

#define SIZE 5
#define RANDOM_SEED     12345
#define GARBAGE 0xAA
#define EMPTY 0x00

ITEMPOOL_TYPEDEF(intpool,int,SIZE);
ITEMPOOL_T(intpool) MyPool;



UNITTEST_TESTCASE_BEGIN(itempool_init)

UNITTEST_TESTCASE_END()



UNITTEST_TESTSUITE_BEGIN(itempool)

UNITTEST_ADD_TESTCASE(itempool_init);

UNITTEST_TESTSUITE_END()
