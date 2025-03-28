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
    \file       crc16.c

    \brief      Implementation of 16-bit Cyclic Redundancy Check (CRC16).

    \details    see header file
*/

#include "crc16.h"

static const crc16_conf_t crc16_conf[] = {

#if defined(CRC16_ENABLE_ARC) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/ARC",
        .result = 0x57BE,
        .check  = 0xBB3D,
#endif
        .poly   = 0x8005,
        .init   = 0x0000,
        .refin  = true,
        .refout = true,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_CDMA2000) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/CDMA2000",
        .result = 0xEABF,
        .check  = 0x4C06,
#endif
        .poly   = 0xC867,
        .init   = 0xFFFF,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_CMS) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/CMS",
        .result = 0x64A5,
        .check  = 0xAEE7,
#endif
        .poly   = 0x8005,
        .init   = 0xFFFF,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_DDS_110) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/DDS-110",
        .result = 0x9765,
        .check  = 0x9ECF,
#endif
        .poly   = 0x8005,
        .init   = 0x800D,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_DECT_R) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/DECT-R",
        .result = 0x23FE,
        .check  = 0x007E,
#endif
        .poly   = 0x0589,
        .init   = 0x0000,
        .refin  = false,
        .refout = false,
        .xorout = 0x0001
    },
#endif

#if defined(CRC16_ENABLE_DECT_X) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/DECT-X",
        .result = 0x23FF,
        .check  = 0x007F,
#endif
        .poly   = 0x0589,
        .init   = 0x0000,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_DNP) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/DNP",
        .result = 0x8A5A,
        .check  = 0xEA82,
#endif
        .poly   = 0x3D65,
        .init   = 0x0000,
        .refin  = true,
        .refout = true,
        .xorout = 0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_EN_13757) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/EN-13757",
        .result = 0x07C0,
        .check  = 0xC2B7,
#endif
        .poly   = 0x3D65,
        .init   = 0x0000,
        .refin  = false,
        .refout = false,
        .xorout = 0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_GENIBUS) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/GENIBUS",
        .result = 0x77D5,
        .check  = 0xD64E,
#endif
        .poly   = 0x1021,
        .init   = 0xFFFF,
        .refin  = false,
        .refout = false,
        .xorout = 0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_GSM) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/GSM",
        .result = 0xF32C,
        .check  = 0xCE3C,
#endif
        .poly   = 0x1021,
        .init   = 0x0000,
        .refin  = false,
        .refout = false,
        .xorout = 0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_IBM_3740) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/IBM-3740",
        .result = 0x882A,
        .check  = 0x29B1,
#endif
        .poly   = 0x1021,
        .init   = 0xFFFF,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_IBM_SDLC) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/IBM-SDLC",
        .result = 0x0BBB,
        .check  = 0x906E,
#endif
        .poly   = 0x1021,
        .init   = 0xFFFF,
        .refin  = true,
        .refout = true,
        .xorout = 0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_ISO_IEC_14443_3_A) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/ISO-IEC-14443-3-A",
        .result = 0x4167,
        .check  = 0xBF05,
#endif
        .poly   = 0x1021,
        .init   = 0xC6C6,
        .refin  = true,
        .refout = true,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_KERMIT) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/KERMIT",
        .result = 0x6B65,
        .check  = 0x2189,
#endif
        .poly   = 0x1021,
        .init   = 0x0000,
        .refin  = true,
        .refout = true,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_LJ1200) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/LJ1200",
        .result = 0xF77A,
        .check  = 0xBDF4,
#endif
        .poly   = 0x6F63,
        .init   = 0x0000,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_M17) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/M17",
        .result = 0x835A,
        .check  = 0x772B,
#endif
        .poly   = 0x5935,
        .init   = 0xFFFF,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_MAXIM_DOW) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/MAXIM-DOW",
        .result = 0xA841,
        .check  = 0x44C2,
#endif
        .poly   = 0x8005,
        .init   = 0x0000,
        .refin  = true,
        .refout = true,
        .xorout = 0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_MCRF4XX) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/MCRF4XX",
        .result = 0xF444,
        .check  = 0x6F91,
#endif
        .poly   = 0x1021,
        .init   = 0xFFFF,
        .refin  = true,
        .refout = true,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_MODBUS) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/MODBUS",
        .result = 0x55DA,
        .check  = 0x4B37,
#endif
        .poly   = 0x8005,
        .init   = 0xFFFF,
        .refin  = true,
        .refout = true,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_NRSC_5) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/NRSC-5",
        .result = 0x7554,
        .check  = 0xA066,
#endif
        .poly   = 0x080B,
        .init   = 0xFFFF,
        .refin  = true,
        .refout = true,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_OPENSAFETY_A) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/OPENSAFETY-A",
        .result = 0x1091,
        .check  = 0x5D38,
#endif
        .poly   = 0x5935,
        .init   = 0x0000,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_OPENSAFETY_B) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/OPENSAFETY-B",
        .result = 0x8162,
        .check  = 0x20FE,
#endif
        .poly   = 0x755B,
        .init   = 0x0000,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_PROFIBUS) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/PROFIBUS",
        .result = 0xD5C0,
        .check  = 0xA819,
#endif
        .poly   = 0x1DCF,
        .init   = 0xFFFF,
        .refin  = false,
        .refout = false,
        .xorout = 0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_RIELLO) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/RIELLO",
        .result = 0x014E,
        .check  = 0x63D0,
#endif
        .poly   = 0x1021,
        .init   = 0xB2AA,
        .refin  = true,
        .refout = true,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_SPI_FUJITSU) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/SPI-FUJITSU",
        .result = 0xA5B9,
        .check  = 0xE5CC,
#endif
        .poly   = 0x1021,
        .init   = 0x1D0F,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_T10_DIF) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/T10-DIF",
        .result = 0x9744,
        .check  = 0xD0DB,
#endif
        .poly   = 0x8BB7,
        .init   = 0x0000,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_TELEDISK) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/TELEDISK",
        .result = 0xB69F,
        .check  = 0x0FB3,
#endif
        .poly   = 0xA097,
        .init   = 0x0000,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_TMS37157) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/TMS37157",
        .result = 0x6601,
        .check  = 0x26B1,
#endif
        .poly   = 0x1021,
        .init   = 0x89EC,
        .refin  = true,
        .refout = true,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_UMTS) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/UMTS",
        .result = 0x42E5,
        .check  = 0xFEE8,
#endif
        .poly   = 0x8005,
        .init   = 0x0000,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

#if defined(CRC16_ENABLE_USB) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/USB",
        .result = 0xAA25,
        .check  = 0xB4C8,
#endif
        .poly   = 0x8005,
        .init   = 0xFFFF,
        .refin  = true,
        .refout = true,
        .xorout = 0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_XMODEM) || defined(UNITTEST)
    {
#ifdef UNITTEST
        .text   = "CRC-16/XMODEM",
        .result = 0x0CD3,
        .check  = 0x31C3,
#endif
        .poly   = 0x1021,
        .init   = 0x0000,
        .refin  = false,
        .refout = false,
        .xorout = 0x0000
    },
#endif

};

const crc16_conf_t* crc16_get_conf(crc16_id_t id)
{
    if ( id >= crc16_conf_count() )
    {
        return NULL;
    }

    return &crc16_conf[id];
}

int crc16_conf_count(void)
{
    return sizeof(crc16_conf)/sizeof(*crc16_conf);
}


/* Hilfsfunktion zum Spiegeln eines Bytes (Bitreihenfolge umkehren) */
inline static uint8_t crc16_reflect8(uint8_t x)
{
    /* Variante mit „bitweiser“ Umkehr durch Masken und Verschieben */
    x = (uint8_t)((x & 0xF0) >> 4 | (x & 0x0F) << 4);
    x = (uint8_t)((x & 0xCC) >> 2 | (x & 0x33) << 2);
    x = (uint8_t)((x & 0xAA) >> 1 | (x & 0x55) << 1);
    return x;
}

uint16_t crc16_update_byte(crc16_id_t id, uint16_t seed, uint8_t byte)
{
    unsigned char i;

    /* Wenn RefIn = true, Byte vor der CRC-Berechnung spiegeln */
    if (crc16_conf[id].refin) {
        byte = crc16_reflect8(byte);
    }

    for (i = 0; i < 8; i++) {

        if (((seed & 0x8000) >> 8) ^ (byte & 0x80)){
            seed = (seed << 1)  ^ crc16_conf[id].poly;
        }else{
            seed = (seed << 1);
        }

        byte <<= 1;
    }

    return seed;
}

uint16_t crc16_update(crc16_id_t id, uint16_t seed, uint8_t *data, size_t size)
{

    while (size--)
    {
        seed = crc16_update_byte(id, seed, *data++);
    }

    return seed;
}


/* Hilfsfunktion zum Spiegeln eines 16-Bit-Werts */
inline static uint16_t crc16_reflect16(uint16_t x)
{
    /* Methode analog zum Reflect von 8 Bit, nur auf 16 Bit ausgeweitet */
    x = (uint16_t)((x & 0xFF00) >> 8 | (x & 0x00FF) << 8);
    x = (uint16_t)((x & 0xF0F0) >> 4 | (x & 0x0F0F) << 4);
    x = (uint16_t)((x & 0xCCCC) >> 2 | (x & 0x3333) << 2);
    x = (uint16_t)((x & 0xAAAA) >> 1 | (x & 0x5555) << 1);
    return x;
}


uint16_t crc16_finalize (crc16_id_t id, uint16_t seed)
{
    /* Wenn RefOut = true, erst den 16-Bit-Wert spiegeln */
    if (crc16_conf[id].refout)
    {
        seed = crc16_reflect16(seed);
    }

    /* Dann den XorOut-Wert anwenden */

    return seed^crc16_conf[id].xorout;
}

uint16_t crc16 (crc16_id_t id, uint8_t *data, size_t size)
{
    return crc16_finalize(id, crc16_update(id, crc16_conf[id].init, data, size));
}




