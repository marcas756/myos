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
        "CRC-16/ARC",
        0x57BE,
        0xBB3D,
    #endif
        0x8005,
        0x0000,
        true,
        true,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_CDMA2000) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/CDMA2000",
        0xEABF,
        0x4C06,
    #endif
        0xC867,
        0xFFFF,
        false,
        false,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_CMS) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/CMS",
        0x64A5,
        0xAEE7,
    #endif
        0x8005,
        0xFFFF,
        false,
        false,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_DDS_110) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/DDS-110",
        0x9765,
        0x9ECF,
    #endif
        0x8005,
        0x800D,
        false,
        false,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_DECT_R) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/DECT-R",
        0x23FE,
        0x007E,
    #endif
        0x0589,
        0x0000,
        false,
        false,
        0x0001
    },
#endif

#if defined(CRC16_ENABLE_DECT_X) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/DECT-X",
        0x23FF,
        0x007F,
    #endif
        0x0589,
        0x0000,
        false,
        false,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_DNP) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/DNP",
        0x8A5A,
        0xEA82,
    #endif
        0x3D65,
        0x0000,
        true,
        true,
        0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_EN_13757) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/EN-13757",
        0x07C0,
        0xC2B7,
    #endif
        0x3D65,
        0x0000,
        false,
        false,
        0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_GENIBUS) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/GENIBUS",
        0x77D5,
        0xD64E,
    #endif
        0x1021,
        0xFFFF,
        false,
        false,
        0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_GSM) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/GSM",
        0xF32C,
        0xCE3C,
    #endif
        0x1021,
        0x0000,
        false,
        false,
        0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_IBM_3740) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/IBM-3740",
        0x882A,
        0x29B1,
    #endif
        0x1021,
        0xFFFF,
        false,
        false,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_IBM_SDLC) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/IBM-SDLC",
        0x0BBB,
        0x906E,
    #endif
        0x1021,
        0xFFFF,
        true,
        true,
        0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_ISO_IEC_14443_3_A) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/ISO-IEC-14443-3-A",
        0x4167,
        0xBF05,
    #endif
        0x1021,
        0xC6C6,
        true,
        true,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_KERMIT) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/KERMIT",
        0x6B65,
        0x2189,
    #endif
        0x1021,
        0x0000,
        true,
        true,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_LJ1200) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/LJ1200",
        0xF77A,
        0xBDF4,
    #endif
        0x6F63,
        0x0000,
        false,
        false,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_M17) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/M17",
        0x835A,
        0x772B,
    #endif
        0x5935,
        0xFFFF,
        false,
        false,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_MAXIM_DOW) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/MAXIM-DOW",
        0xA841,
        0x44C2,
    #endif
        0x8005,
        0x0000,
        true,
        true,
        0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_MCRF4XX) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/MCRF4XX",
        0xF444,
        0x6F91,
    #endif
        0x1021,
        0xFFFF,
        true,
        true,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_MODBUS) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/MODBUS",
        0x55DA,
        0x4B37,
    #endif
        0x8005,
        0xFFFF,
        true,
        true,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_NRSC_5) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/NRSC-5",
        0x7554,
        0xA066,
    #endif
        0x080B,
        0xFFFF,
        true,
        true,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_OPENSAFETY_A) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/OPENSAFETY-A",
        0x1091,
        0x5D38,
    #endif
        0x5935,
        0x0000,
        false,
        false,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_OPENSAFETY_B) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/OPENSAFETY-B",
        0x8162,
        0x20FE,
    #endif
        0x755B,
        0x0000,
        false,
        false,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_PROFIBUS) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/PROFIBUS",
        0xD5C0,
        0xA819,
    #endif
        0x1DCF,
        0xFFFF,
        false,
        false,
        0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_RIELLO) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/RIELLO",
        0x014E,
        0x63D0,
    #endif
        0x1021,
        0xB2AA,
        true,
        true,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_SPI_FUJITSU) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/SPI-FUJITSU",
        0xA5B9,
        0xE5CC,
    #endif
        0x1021,
        0x1D0F,
        false,
        false,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_T10_DIF) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/T10-DIF",
        0x9744,
        0xD0DB,
    #endif
        0x8BB7,
        0x0000,
        false,
        false,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_TELEDISK) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/TELEDISK",
        0xB69F,
        0x0FB3,
    #endif
        0xA097,
        0x0000,
        false,
        false,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_TMS37157) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/TMS37157",
        0x6601,
        0x26B1,
    #endif
        0x1021,
        0x89EC,
        true,
        true,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_UMTS) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/UMTS",
        0x42E5,
        0xFEE8,
    #endif
        0x8005,
        0x0000,
        false,
        false,
        0x0000
    },
#endif

#if defined(CRC16_ENABLE_USB) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/USB",
        0xAA25,
        0xB4C8,
    #endif
        0x8005,
        0xFFFF,
        true,
        true,
        0xFFFF
    },
#endif

#if defined(CRC16_ENABLE_XMODEM) || defined(UNITTEST)
    {
    #ifdef UNITTEST
        "CRC-16/XMODEM",
        0x0CD3,
        0x31C3,
    #endif
        0x1021,
        0x0000,
        false,
        false,
        0x0000
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
static uint8_t crc16_reflect8(uint8_t x)
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
static uint16_t crc16_reflect16(uint16_t x)
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




