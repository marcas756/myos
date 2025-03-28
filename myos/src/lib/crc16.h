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
    \file crc16.h

    \brief Implementation of 16-bit Cyclic Redundancy Check (CRC16).

    A cyclic redundancy check (CRC) is an error-detecting code commonly used in
    digital networks and storage devices to detect accidental changes to digital
    data.[1][2] Blocks of data entering these systems get a short check value attached,
    based on the remainder of a polynomial division of their contents. On retrieval,
    the calculation is repeated and, in the event the check values do not match,
    corrective action can be taken against data corruption. CRCs can be used for error
    correction (see bitfilters).[3]

    CRCs are so called because the check (data verification) value is a redundancy
    (it expands the message without adding information) and the algorithm is based on
    cyclic codes. CRCs are popular because they are simple to implement in binary hardware,
    easy to analyze mathematically, and particularly good at detecting common errors caused
    by noise in transmission channels. Because the check value has a fixed length, the function
    that generates it is occasionally used as a hash function.

    [https://en.wikipedia.org/wiki/Cyclic_redundancy_check]




| CRC-16                     | Result | Check | Poly   | Init   | RefIn | RefOut | XorOut |
|----------------------------|--------|-------|--------|--------|-------|--------|--------|
| CRC-16/ARC                 | 0x57BE | 0xBB3D | 0x8005 | 0x0000 | true  | true   | 0x0000 |
| CRC-16/CDMA2000            | 0xEABF | 0x4C06 | 0xC867 | 0xFFFF | false | false  | 0x0000 |
| CRC-16/CMS                 | 0x64A5 | 0xAEE7 | 0x8005 | 0xFFFF | false | false  | 0x0000 |
| CRC-16/DDS-110             | 0x9765 | 0x9ECF | 0x8005 | 0x800D | false | false  | 0x0000 |
| CRC-16/DECT-R              | 0x23FE | 0x007E | 0x0589 | 0x0000 | false | false  | 0x0001 |
| CRC-16/DECT-X              | 0x23FF | 0x007F | 0x0589 | 0x0000 | false | false  | 0x0000 |
| CRC-16/DNP                 | 0x8A5A | 0xEA82 | 0x3D65 | 0x0000 | true  | true   | 0xFFFF |
| CRC-16/EN-13757            | 0x07C0 | 0xC2B7 | 0x3D65 | 0x0000 | false | false  | 0xFFFF |
| CRC-16/GENIBUS             | 0x77D5 | 0xD64E | 0x1021 | 0xFFFF | false | false  | 0xFFFF |
| CRC-16/GSM                 | 0xF32C | 0xCE3C | 0x1021 | 0x0000 | false | false  | 0xFFFF |
| CRC-16/IBM-3740            | 0x882A | 0x29B1 | 0x1021 | 0xFFFF | false | false  | 0x0000 |
| CRC-16/IBM-SDLC            | 0x0BBB | 0x906E | 0x1021 | 0xFFFF | true  | true   | 0xFFFF |
| CRC-16/ISO-IEC-14443-3-A   | 0x4167 | 0xBF05 | 0x1021 | 0xC6C6 | true  | true   | 0x0000 |
| CRC-16/KERMIT              | 0x6B65 | 0x2189 | 0x1021 | 0x0000 | true  | true   | 0x0000 |
| CRC-16/LJ1200              | 0xF77A | 0xBDF4 | 0x6F63 | 0x0000 | false | false  | 0x0000 |
| CRC-16/M17                 | 0x835A | 0x772B | 0x5935 | 0xFFFF | false | false  | 0x0000 |
| CRC-16/MAXIM-DOW           | 0xA841 | 0x44C2 | 0x8005 | 0x0000 | true  | true   | 0xFFFF |
| CRC-16/MCRF4XX             | 0xF444 | 0x6F91 | 0x1021 | 0xFFFF | true  | true   | 0x0000 |
| CRC-16/MODBUS              | 0x55DA | 0x4B37 | 0x8005 | 0xFFFF | true  | true   | 0x0000 |
| CRC-16/NRSC-5              | 0x7554 | 0xA066 | 0x080B | 0xFFFF | true  | true   | 0x0000 |
| CRC-16/OPENSAFETY-A        | 0x1091 | 0x5D38 | 0x5935 | 0x0000 | false | false  | 0x0000 |
| CRC-16/OPENSAFETY-B        | 0x8162 | 0x20FE | 0x755B | 0x0000 | false | false  | 0x0000 |
| CRC-16/PROFIBUS            | 0xD5C0 | 0xA819 | 0x1DCF | 0xFFFF | false | false  | 0xFFFF |
| CRC-16/RIELLO              | 0x014E | 0x63D0 | 0x1021 | 0xB2AA | true  | true   | 0x0000 |
| CRC-16/SPI-FUJITSU         | 0xA5B9 | 0xE5CC | 0x1021 | 0x1D0F | false | false  | 0x0000 |
| CRC-16/T10-DIF             | 0x9744 | 0xD0DB | 0x8BB7 | 0x0000 | false | false  | 0x0000 |
| CRC-16/TELEDISK            | 0xB69F | 0x0FB3 | 0xA097 | 0x0000 | false | false  | 0x0000 |
| CRC-16/TMS37157            | 0x6601 | 0x26B1 | 0x1021 | 0x89EC | true  | true   | 0x0000 |
| CRC-16/UMTS                | 0x42E5 | 0xFEE8 | 0x8005 | 0x0000 | false | false  | 0x0000 |
| CRC-16/USB                 | 0xAA25 | 0xB4C8 | 0x8005 | 0xFFFF | true  | true   | 0xFFFF |
| CRC-16/XMODEM              | 0x0CD3 | 0x31C3 | 0x1021 | 0x0000 | false | false  | 0x0000 |


*/


#ifndef CRC16_H_
#define CRC16_H_
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
#if defined(CRC16_ENABLE_ARC) || defined(UNITTEST)
    CRC16_ARC,
#endif

#if defined(CRC16_ENABLE_CDMA2000) || defined(UNITTEST)
    CRC16_CDMA2000,
#endif

#if defined(CRC16_ENABLE_CMS) || defined(UNITTEST)
    CRC16_CMS,
#endif

#if defined(CRC16_ENABLE_DDS_110) || defined(UNITTEST)
    CRC16_DDS_110,
#endif

#if defined(CRC16_ENABLE_DECT_R) || defined(UNITTEST)
    CRC16_DECT_R,
#endif

#if defined(CRC16_ENABLE_DECT_X) || defined(UNITTEST)
    CRC16_DECT_X,
#endif

#if defined(CRC16_ENABLE_DNP) || defined(UNITTEST)
    CRC16_DNP,
#endif

#if defined(CRC16_ENABLE_EN_13757) || defined(UNITTEST)
    CRC16_EN_13757,
#endif

#if defined(CRC16_ENABLE_GENIBUS) || defined(UNITTEST)
    CRC16_GENIBUS,
#endif

#if defined(CRC16_ENABLE_GSM) || defined(UNITTEST)
    CRC16_GSM,
#endif

#if defined(CRC16_ENABLE_IBM_3740) || defined(UNITTEST)
    CRC16_IBM_3740,
#endif

#if defined(CRC16_ENABLE_IBM_SDLC) || defined(UNITTEST)
    CRC16_IBM_SDLC,
#endif

#if defined(CRC16_ENABLE_ISO_IEC_14443_3_A) || defined(UNITTEST)
    CRC16_ISO_IEC_14443_3_A,
#endif

#if defined(CRC16_ENABLE_KERMIT) || defined(UNITTEST)
    CRC16_KERMIT,
#endif

#if defined(CRC16_ENABLE_LJ1200) || defined(UNITTEST)
    CRC16_LJ1200,
#endif

#if defined(CRC16_ENABLE_M17) || defined(UNITTEST)
    CRC16_M17,
#endif

#if defined(CRC16_ENABLE_MAXIM_DOW) || defined(UNITTEST)
    CRC16_MAXIM_DOW,
#endif

#if defined(CRC16_ENABLE_MCRF4XX) || defined(UNITTEST)
    CRC16_MCRF4XX,
#endif

#if defined(CRC16_ENABLE_MODBUS) || defined(UNITTEST)
    CRC16_MODBUS,
#endif

#if defined(CRC16_ENABLE_NRSC_5) || defined(UNITTEST)
    CRC16_NRSC_5,
#endif

#if defined(CRC16_ENABLE_OPENSAFETY_A) || defined(UNITTEST)
    CRC16_OPENSAFETY_A,
#endif

#if defined(CRC16_ENABLE_OPENSAFETY_B) || defined(UNITTEST)
    CRC16_OPENSAFETY_B,
#endif

#if defined(CRC16_ENABLE_PROFIBUS) || defined(UNITTEST)
    CRC16_PROFIBUS,
#endif

#if defined(CRC16_ENABLE_RIELLO) || defined(UNITTEST)
    CRC16_RIELLO,
#endif

#if defined(CRC16_ENABLE_SPI_FUJITSU) || defined(UNITTEST)
    CRC16_SPI_FUJITSU,
#endif

#if defined(CRC16_ENABLE_T10_DIF) || defined(UNITTEST)
    CRC16_T10_DIF,
#endif

#if defined(CRC16_ENABLE_TELEDISK) || defined(UNITTEST)
    CRC16_TELEDISK,
#endif

#if defined(CRC16_ENABLE_TMS37157) || defined(UNITTEST)
    CRC16_TMS37157,
#endif

#if defined(CRC16_ENABLE_UMTS) || defined(UNITTEST)
    CRC16_UMTS,
#endif

#if defined(CRC16_ENABLE_USB) || defined(UNITTEST)
    CRC16_USB,
#endif

#if defined(CRC16_ENABLE_XMODEM) || defined(UNITTEST)
    CRC16_XMODEM,
#endif

} crc16_id_t;


typedef struct {
#ifdef UNITTEST
    char *text;
    uint16_t result;
    uint16_t check;
#endif
    uint16_t poly;
    uint16_t init;
    bool refin;
    bool refout;
    uint16_t xorout;
}crc16_conf_t;



/*!
    \brief Accumulates a CRC16 checksum for a single byte.

    This function computes the CRC16 checksum of a single byte, using a provided seed value
    and polynomial. It's typically used in a loop to calculate the CRC16 checksum of a data stream
    byte by byte.

    \param seed The initial or previously accumulated CRC16 value.
    \param polynom The polynomial used for the CRC calculation. This value determines the specific
    CRC16 algorithm being implemented.
    \param byte The byte of data for which the CRC16 checksum is to be computed.

    \return The updated CRC16 checksum after processing the given byte.


    \note This function processes one byte at a time and can be called iteratively to calculate
    the CRC of a sequence of bytes.
*/
uint16_t crc16_update_byte(crc16_id_t id, uint16_t seed, uint8_t byte);
uint16_t crc16_update(crc16_id_t id, uint16_t seed, uint8_t *data, size_t size);
uint16_t crc16_finalize (crc16_id_t id, uint16_t seed);
const crc16_conf_t* crc16_get_conf(crc16_id_t id);
int crc16_conf_count(void);


    /*!
        \brief Computes the CRC16 checksum for a data array.

        This function calculates the CRC16 checksum using a specified polynomial and an initial seed value.
        It processes each byte in the provided data array, accumulating the CRC16 checksum. This function is
        typically used in communication protocols to ensure data integrity.

        \param seed The initial CRC value, typically 0xFFFF or another specified seed.
        \param polynom The polynomial used for the CRC calculation. Different standards may use different
        polynomials.
        \param data Pointer to the data array over which the CRC16 is to be computed.
        \param size The size of the data array in bytes.

        \return The CRC16 checksum of the data array.

        \note This function uses the crc16_acc function internally to process each byte.
    */
uint16_t crc16 (crc16_id_t id, uint8_t *data, size_t size);


#endif /* CRC16_H_ */
