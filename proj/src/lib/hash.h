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
    \file       hash.h

    \brief      Hashing Algorithms

    \details    tbd
*/

#ifndef HASH_H_
#define HASH_H_

#include <stdint.h>
#include <stddef.h>

/*!
    \brief      Accumulates a single byte into an ongoing SDBM hash calculation.

    \details    This macro is a core part of the SDBM hash function. It takes a
                current hash value and a single byte, then applies a specific
                calculation to accumulate the byte into the hash. The calculation
                involves bitwise operations and arithmetic that are characteristic
                of the SDBM algorithm, known for its simplicity and effectiveness
                in distributing hash values.

                This macro is typically used within a loop that processes each byte
                of a data block, contributing to the final hash value.




    \param hash     The current hash value.
    \param byte     The byte to be accumulated into the hash.

    \return         The updated hash value after accumulating the byte.
*/
#define hash_sdbm_acc(hash, byte) \
 ((byte + (hash << 6) + (hash << 16) - hash))

/*!
    \brief      Calculates a hash value using the SDBM algorithm.

    \details    This function computes a hash value by processing each byte in
                the provided data block using the SDBM hashing algorithm.
                It starts with an initial seed value and iterates over each byte
                of data, applying a specific hash accumulation operation defined
                in `hash_sdbm_acc` macro. The function is designed for efficiency
                and simplicity, making it suitable for various hashing needs.

                The SDBM algorithm is known for its simplicity and good
                distribution properties, making it a popular choice in situations
                where a non-cryptographic hash is sufficient.


    \param seed     The initial seed value for the hash computation.
    \param data     Pointer to the data block to be hashed.
    \param size     Size of the data block in bytes.

    \return         The computed hash value as an unsigned 32-bit integer.
*/
uint32_t hash_sdbm(uint32_t seed, void *data, size_t size);




#endif /* HASH_H_ */
