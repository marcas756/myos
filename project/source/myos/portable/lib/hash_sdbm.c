/*! \copyright
    Copyright (c) 2016, marcas756@gmail.com.
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
    \file   hash_sdbm.c

    \brief

    \details    This algorithm was created for sdbm (a public-domain reimplementation of ndbm) database library.
                It was found to do well in scrambling bits, causing better distribution of the keys and fewer splits.
                It also happens to be a good general hashing function with good distribution. the actual function is

                hash(i) = hash(i - 1) * 65599 + str[i];

                What is included below is the faster version used in gawk. [there is even a faster, duff-device version]
                The magic constant 65599 was picked out of thin air while experimenting with different constants,
                and turns out to be a prime. this is one of the algorithms used in berkeley db (see sleepycat) and elsewhere.

                http://www.cse.yorku.ca/~oz/hash.html
*/

/*! \copyright
    Copyright (c) 2013, marcas756@gmail.com.
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
    \file       hash_sdbm.c
    \authors    marcas756@gmail.com

    \brief      Brief description of the module

    \details    Detailed description of the module
*/

/*! \addtogroup srcsyshdrs Inclusion of system headers */
/*!@{*/
/*!@}*//*srcsyshdrs*/

/*! \addtogroup srcusrhdrs Inclusion of user-defined headers */
/*!@{*/
#include "hash_sdbm.h"

#if DEBUG
#include "debug.h"
#endif

/*!@}*//*srcusrhdrs*/

/*! \addtogroup srcmacros #define macros used only in this file */
/*!@{*/
/*!@}*//*srcmacros*/

/*! \addtogroup srcfuncmacros #define function macros used only in this file */
/*!@{*/
#if DEBUG_MODULE
#define DBG(...) DBG_FUNC(__VA_ARGS__)
#else
#define DBG(...)
#endif
/*!@}*//*srcfucnmacros*/

/*! \addtogroup srctypedefs typedef definitions used only in this file */
/*!@{*/
/*!@}*//*srctypedefs*/

/*! \addtogroup srcenums enum tag definitions used only in this file */
/*!@{*/
/*!@}*//*srcenums*/

/*! \addtogroup srcstructs struct/union tag definitions used only in this file */
/*!@{*/
/*!@}*//*srcstructs*/

/*! \addtogroup srcstatvars static variable declarations shared in this file */
/*!@{*/
/*!@}*//*srcstatvars*/

/*! \addtogroup srcstatfuncs static function declarations*/
/*!@{*/
/*!@}*//*srcstatfuncs*/

/*! \addtogroup srcvardefs variable definitions*/
/*!@{*/
/*!@}*//*srcvardefs*/

/*! \addtogroup srcfuncdefs function definitions*/
/*!@{*/
uint32_t hash_sdbm(uint32_t seed, void *data, size_t size)
{
	int idx;

	for(idx = 0; idx < size; idx++)
	{
		seed = hash_sdbm_acc(seed,((uint8_t*)data)[idx]);		
	}

    	return seed;
}
/*!@}*//*srcfuncdefs*/








