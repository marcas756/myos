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
    \file       hash.h

    \brief      Provides hash functions

    \details    A hash function is any function that can be used to map data of arbitrary size
                to data of fixed size. The values returned by a hash function are called hash values,
                hash codes, hash sums, or simply hashes. One use is a data structure called a hash table,
                widely used in computer software for rapid data lookup. Hash functions accelerate table
                or database lookup by detecting duplicated records in a large file. An example is finding
                similar stretches in DNA sequences. They are also useful in cryptography. A cryptographic
                hash function allows one to easily verify that some input data maps to a given hash value,
                but if the input data is unknown, it is deliberately difficult to reconstruct it
                (or equivalent alternatives) by knowing the stored hash value. This is used for assuring
                integrity of transmitted data, and is the building block for HMACs, which provide message
                authentication. (wikipedia)

                Hash functions are related to (and often confused with) checksums, check digits, fingerprints,
                randomization functions, error-correcting codes, and ciphers. Although these concepts overlap
                to some extent, each has its own uses and requirements and is designed and optimized differently.
                The Hash Keeper database maintained by the American National Drug Intelligence Center, for instance,
                is more aptly described as a catalogue of file fingerprints than of hash values. (wikipedia)

                https://en.wikipedia.org/wiki/Hash_function
*/


#ifndef HASH_H_
#define HASH_H_

#include <stdint.h>
#include <stddef.h>

extern uint32_t hash_sdbm(uint32_t seed, void *data, size_t size);


#endif /* HASH_H_ */
