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
   \file      bits.h

   \brief     Bitwise operations header file.

   \details   This file defines several macros for performing bitwise operations
               on integer variables. These macros provide a concise way to
               extract, test, set, clear, and toggle specific bits within an integer.
               They are designed to improve code readability and maintainability
               when working with bit-level manipulations.
*/

#ifndef BITS_H_
#define BITS_H_

/*!
    \brief Extract specific bits from an integer.

    \details This macro performs a bitwise AND operation between the input value and a mask,
             effectively extracting only those bits that are set in both the input and the mask.
             It is commonly used for operations on bit fields or flags within an integer.

    \param x The input integer value from which bits are to be extracted.
    \param m A mask specifying which bits of `x` should be retained. Only the bits
             that are set (1) in this mask will be kept after applying the operation.

    \return An integer with only the bits set that were common between `x` and `m`.
*/
#define BITS(x,m)           ((x)&(m))


/*!
    \brief Inverts all bits of an integer.

    \details This macro performs a bitwise NOT operation on the input value, flipping
             every bit. It effectively computes the one's complement of the number,
             where each 0 becomes 1 and each 1 becomes 0.

    \param x The integer whose bits are to be inverted.

    \return An integer with all bits inverted from `x`.
*/
#define BITS_INVERT(x)      (~x)

/*!
    \brief Tests if all specified bits are set in an integer.

    \details This macro checks whether every bit that is set (1) in the mask `m`
             is also set in the input value `x`. It does so by performing a bitwise AND
             between `x` and `m`, then comparing the result to `m`. If they are equal,
             it indicates all bits specified by the mask are present in `x`.

    \param x The integer to be tested.
    \param m A mask specifying which bits of `x` should be checked. It represents
             the required set of bits that must be present in `x`.

    \return \c true (non-zero) if all bits specified by `m` are set in `x`,
            otherwise \c false (zero).
*/
#define BITS_TEST(x,m)      (((x)&(m))==(m))

/*!
    \brief Sets specific bits in an integer using a bitmask.

    \details This macro applies a bitwise OR operation between the input value `x`
             and the mask `m`, then assigns the result back to `x`. The effect is that
             all bits specified by the mask are set (turned on) in `x`, without altering
             any other bits.

    \param x The integer whose bits will be modified. This variable is altered directly.
    \param m A bitmask specifying which bits of `x` should be set to 1. Each bit that
             is set (1) in this mask will be turned on in `x`.
*/
#define BITS_SET(x,m)       ((x)|=(m))

/*!
    \brief Clears specific bits in an integer using a bitmask.

    \details This macro performs a bitwise AND operation between the input value `x`
             and the negated mask `m`. The effect is that all bits specified by the
             original mask are cleared (turned off) in `x`, while leaving other bits unchanged.

    \param x The integer whose bits will be modified. This variable is altered directly.
    \param m A bitmask specifying which bits of `x` should be cleared to 0. Each bit that
             is set (1) in this mask will be turned off in `x`.
*/
#define BITS_CLEAR(x,m)     ((x)&=~(m))

/*!
    \brief Toggles specific bits in an integer using a bitmask.

    \details This macro performs a bitwise XOR operation between the input value `x`
             and the mask `m`, then assigns the result back to `x`. The effect is that
             all bits specified by the mask are toggled (switched between 0 and 1) in `x`,
             while leaving other bits unchanged.

    \param x The integer whose bits will be modified. This variable is altered directly.
    \param m A bitmask specifying which bits of `x` should be toggled. Each bit that
             is set (1) in this mask will have its corresponding bit in `x` switched
             from 0 to 1 or from 1 to 0.
*/
#define BITS_TOGGLE(x,m)    ((x)^=(m))

#endif /* BITS_H_ */
