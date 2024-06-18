/**
 * \file crc.c
 * Functions and types for CRC checks.
 *
 * Generated on Sun Dec 18 16:52:06 2016,
 * by pycrc v0.9, https://pycrc.org
 * using the configuration:
 *    Width         = 32
 *    Poly          = 0x04c11db7
 *    Xor_In        = 0xffffffff
 *    ReflectIn     = True
 *    Xor_Out       = 0xffffffff
 *    ReflectOut    = True
 *    Algorithm     = table-driven
 *****************************************************************************/
#include "crc.h"     /* include the header file generated with pycrc */
#include <stdlib.h>
#include <stdint.h>

/**
 * Static table used for the table_driven implementation.
 *****************************************************************************/
static const crc_t crc_table[16] = {
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};

/**
 * Update the crc value with new data.
 *
 * \param crc      The current crc value.
 * \param data     Pointer to a buffer of \a data_len bytes.
 * \param data_len Number of bytes in the \a data buffer.
 * \return         The updated crc value.
 *****************************************************************************/
crc_t crc_update(crc_t crc, const void *data, size_t data_len)
{
    const unsigned char *d = (const unsigned char *)data;
    unsigned int tbl_idx;

    while (data_len--) {
        tbl_idx = crc ^ (*d >> (0 * 4));
        crc = crc_table[tbl_idx & 0x0f] ^ (crc >> 4);
        tbl_idx = crc ^ (*d >> (1 * 4));
        crc = crc_table[tbl_idx & 0x0f] ^ (crc >> 4);

        d++;
    }
    return crc & 0xffffffff;
}


