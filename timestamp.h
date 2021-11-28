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
    \file       timestamp.h

    \brief      Provides definitions to access and evaluate the systems time stamp counter

    \details    Provides the architecture independent part to access and evaluate the systems
                time stamp counter. For architecture dependent part see "timestamp_arch.h"
                of the corresponding architectural part.

                Time stamps are the base for all non real time timers used by the os.

*/
#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include "timestamp_arch.h"

#define TIMESTAMP_TICKS_PER_SEC TIMESTAMP_ARCH_TICKS_PER_SEC
#define TIMESTAMP_DIFF TIMESTAMP_ARCH_DIFF

typedef timestamp_arch_t timestamp_t;
typedef timestamp_t timespan_t;

#define timestamp_module_init  timestamp_arch_module_init

#define timestamp_now timestamp_arch_now



/*!
    \brief      Checks if a provided time stamp is in the past
    \details    Checks if the time stamp counter passed a provided time stamp yet.

    \param[in]      timestamp       Time stamp to check
    \returns 1 if time stamp is in the past, otherwise 0
*/
#define timestamp_passed(timestamp) \
    (timestamp_now()>(timestamp)) /* >= ? */

#define timestamp_less_than(a,b)    (TIMESTAMP_DIFF((a),(b)) < 0)


/*!
    \brief      Blocks until the time stamp provided is in the past
    \param[in]      timestamp       Time stamp to wait for
*/
#define timestamp_block_until(timestamp) \
    do{}while(!timestamp_passed(timestamp))

/*!
    \brief      Blocks for some time
    \param[in]      timespan      Time to block
*/
#define timestamp_block_for(timespan)                       \
    do{                                                     \
        timestamp_block_until(timestamp_now()+(timespan));                      \
    }while(0)



#endif /* TIMESTAMP_H_ */

