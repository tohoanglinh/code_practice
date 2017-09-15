/*******************************************************************************
 * Assignment 5: SREC (17-1)
 * @dev: linhth8
 * @mentor: haind1
 * @topic: file handling, debugging
 * srecParse API
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "srecHeader.h"

/*!
 * @brief Get checksum value from two last bytes in a line
 *
 * @param tmp_line a line string as input param.
 *
 * @return checksum information contained in a line
 */
uint8_t srecChecksumGet(char *tmp_line)
{
    uint32_t get_checksum;
    uint8_t i = 0;
    
    /* get length of string tmp_line */
    while (tmp_line[i]!='\0')
    {
        i++;
    }

    /* get checksum from tmp_line */
    get_checksum = hexToDec(tmp_line[i-2], tmp_line[i-1]);
    
    printf("Get Checksum = 0x%X\n", get_checksum);
    
	return get_checksum;
}

/*!
 * @brief Calculate checksum value of a line
 * @howto checksum = bytecount + address + data
 *
 * @param tmp_line a line string as input param.
 *
 * @return checksum information calculated from that string line.
 */
uint8_t srecChecksumCal(char *tmp_line)
{
    uint32_t cal_checksum = 0;
    uint8_t length=0, i;
    
    /* get length of string tmp_line */
    while (tmp_line[length]!='\0')
    {
        length++;
    }
    
    /* byte count */
    g_srecByteCount = hexToDec(tmp_line[2], tmp_line[3]);
    printf("Byte Count = 0x%X\n", g_srecByteCount);
    
    /* Add: add each byte */
    cal_checksum = g_srecByteCount;
    
    for ( i = 4 ; i < (length-2) ; i++ )
    {
        cal_checksum = cal_checksum + hexToDec(tmp_line[i], tmp_line[i+1]);
        i++;
    }
    
    /* Mask: keep the least significant byte of the total */
    cal_checksum = cal_checksum & 0x00FF;
    
    /* Complement: compute ones' complement of the least significant byte */
    cal_checksum = 0xFF - cal_checksum;
    
    printf("Cal Checksum = 0x%X\n", cal_checksum);

    printf("Line  Length = %d\n", length);
    
    return cal_checksum;
}

/*!
 * @brief Extract and display address and data field of each line
 *
 * @param tmp_line.
 * @param type: data type get from srecGetType(tmp_line).
 *
 * @return Display address and data.
 */
void srecDisplayAddressData(char *tmp_line, uint8_t type)
{
    uint8_t start = 3;
    uint8_t i;
    uint32_t address;
    uint8_t length = 0;

    /* get length of string tmp_line */
    while (tmp_line[length]!='\0')
    {
        length++;
    }
    
    if (type == 2)
    {
        printf("Address (%d bytes):\t", type);
        fprintf(g_fsrec_out, "Address (%d bytes):\t", type);
        /* 4, 5, 6, 7 (16 bits) */
        address = hexToDec(tmp_line[start+1],tmp_line[start+2]);
        address = address << 8;
        address = address + hexToDec(tmp_line[start+3],tmp_line[start+4]);
        printf("0x%04X\n", address);
        fprintf(g_fsrec_out, "0x%04X\n", address);

        printf("Data:\t");
        fprintf(g_fsrec_out, "Data:\t");
        for (i = start+5; i < (length-2); i++)
        {
            printf("%c", tmp_line[i]);
            fprintf(g_fsrec_out, "%c", tmp_line[i]);
        }
        printf("\n");
        fprintf(g_fsrec_out, "\n");
    }

    if (type == 3)
    {
        printf("Address (%d bytes):\t", type);
        fprintf(g_fsrec_out,"Address (%d bytes):\t", type);
        /* 4, 5, 6, 7, 8, 9 (24 bits) */
        address = hexToDec(tmp_line[start+1],tmp_line[start+2]);
        address = address << 8;
        address = address + hexToDec(tmp_line[start+3],tmp_line[start+4]);
        address = address << 8;
        address = address + hexToDec(tmp_line[start+5],tmp_line[start+6]);
        printf("0x%X\n", address);
        fprintf(g_fsrec_out, "0x%X\n", address);

        printf("Data:\t");
        fprintf(g_fsrec_out, "Data:\t");
        for (i = start + 7; i < (length-2); i++)
        {
            printf("%c", tmp_line[i]);
            fprintf(g_fsrec_out, "%c", tmp_line[i]);
        }
        printf("\n");
        fprintf(g_fsrec_out, "\n");
        
    }

    if (type == 4)
    {
        printf("Address (%d bytes):\t", type);
        fprintf(g_fsrec_out,"Address (%d bytes):\t", type);
        /* 4, 5, 6, 7, 8, 9, 10, 11 (32 bits) */
        address = hexToDec(tmp_line[start+1],tmp_line[start+2]);
        address = address << 8;
        address = address + hexToDec(tmp_line[start+3],tmp_line[start+4]);
        address = address << 8;
        address = address + hexToDec(tmp_line[start+5],tmp_line[start+6]);
        address = address << 8;
        address = address + hexToDec(tmp_line[start+7],tmp_line[start+8]);
        printf("0x%X\n", address);
        fprintf(g_fsrec_out, "0x%X\n", address);

        printf("Data:\t");
        fprintf(g_fsrec_out, "Data:\t");
        for (i = start + 9; i < (length-2); i++)
        {
            printf("%c", tmp_line[i]);
            fprintf(g_fsrec_out, "%c", tmp_line[i]);
        }
        printf("\n");
        fprintf(g_fsrec_out, "\n");
    }
}

/*!
 * @brief Get data type of a line
 *
 * @param tmp_line .
 *
 * @return Address data types (2 bytes, 3 bytes, 4 bytes)
 */
uint8_t srecGetType(char *tmp_line)
{
    /* S0-S1-S5-S9: 2 bytes, S2-S6-S8: 3 bytes, S3-S7: 4 bytes
     * S1, S2, S3 (2,3,4)
     * S5, S6, S7 (2,3,4)
     * S0, S8, S9 (2,3,2)
     */

    if (tmp_line[1]=='0' || tmp_line[1]=='1' || tmp_line[1]=='5' || tmp_line[1]=='9')
    {
        return 2; /* 2 bytes address field (S0-S1-S5-S9) */
    }
    
    if (tmp_line[1]=='2' || tmp_line[1]=='6' || tmp_line[1]=='8')
    {
        return 3; /* 3 bytes address field (S2-S6-S8) */
    }
    
    if (tmp_line[1]=='3' || tmp_line[1]=='7')
    {
        return 4; /* 4 bytes address field (S3-S7) */
    }
    
    return 0;
}

/*!
 * @brief Test format of a line as SREC or not
 *
 * @param tmp_line .
 *
 * @return 1 if SREC, 0 if non-SREC.
 */
uint8_t srecFormat(char *tmp_line)
{
    if (tmp_line[0] == 'S')
    {
        return 1;       /*valid srec format (start with S)*/
    }
    else
    {
        return 0;       /*invalid format*/
    }
}

/*!
 * @brief Convert a character to a number
 *
 * @param c: character.
 *
 * @return '0' --> 0; 'A' --> 10.
 */
uint8_t charToNum(char c)
{
    /* convert character c to number */
    /* 0 --> 9 */
    /* A --> F */

    if ( c >= '0' && c <= '9' )
    {
        c = c - '0'; /* '0' --> 0 */
    }
    
    if ( c >= 'A' && c <= 'F')
    {
        c = c - 'A' + 10; /* 'A' --> 10 */
    }

    return c;
}

/*!
 * @brief Convert hex number (character) to decimal
 *
 * @param a: character a.
 * @param b: character b.
 *
 * @return decimal value of hex number 0xAB.
 */
uint32_t hexToDec(char a, char b)
{
    /* left shift 4 is analogue to multiplied by 16 (Hexa to Decimal conversion)
     * addition is higher priority than bitwise operator */
    return((charToNum(a) << 4) + charToNum(b));
}
