/**
 * @file      srec.c
 * @developer LinhTH8
 * @mentor    HaiND1
 * @topic     MockTest2-File Handling and Debug
 * @requires  S-Record Parse to Address & Data
 */

#include "srec.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * SREC_PARSE_FUNCTION_Code
 ******************************************************************************/
/**
 * @brief: Parse (extract) SREC information
 * @input *tmp_line: a string
 * @output: saved into a struct pointer tmp_srec
 */
void SREC_Parse(char *tmp_line, SREC_struct_t *tmp_srec)
{
    if (SREC_Format(tmp_line))
    {
        if (SREC_GetCheckSum(tmp_line) == SREC_CalCheckSum(tmp_line))
        {
            /* extract all information and save into pointer tmp_srec */
            tmp_srec->type = SREC_GetType(tmp_line);
            tmp_srec->length = SREC_GetLength(tmp_line);
            tmp_srec->bytecount = SREC_GetByteCount(tmp_line);
            tmp_srec->address = SREC_GetAddress(tmp_line,tmp_srec->type);
            tmp_srec->data = SREC_GetData(tmp_line, tmp_srec->type);
            tmp_srec->checksum = SREC_GetCheckSum(tmp_line);
        }
        else
        {
            /* incorrect srec checksum */
        }
    }
    else
    {
        /* incorrect srec format */
    }
}
/*******************************************************************************
 * SREC_MAIN_FUNCTIONS_Code
 ******************************************************************************/
/**
 * @brief: Check format of string is SREC or not
 * @input *tmp_line: a string
 * @output:
 *      1   valid
 *      0   invalid
 */
uint8_t SREC_Format(char *tmp_line)
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

/**
 * @brief: Get length of a string line
 * @input *tmp_line: a string
 * @output: length of string in number of characters
 */
uint8_t SREC_GetLength(char *tmp_line)
{
    uint8_t length = 0;

    while (tmp_line[length] != '\0')
    {
        length++;
    }

    return length;
}
/**
 * @brief: Get type of SREC line
 *  S0-S1-S5-S9: 2 bytes, S2-S6-S8: 3 bytes, S3-S7: 4 bytes
    S1, S2, S3 (2,3,4)
    S5, S6, S7 (2,3,4)
    S0, S8, S9 (2,3,2)
 * @input *tmp_line: a string
 * @output: a number uint8_t represents type of SREC line.
 */
uint8_t SREC_GetType(char *tmp_line)
{
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

/**
 * @brief: Get Byte Count in Hex
 * @input *tmp_line: a string
 * @output: byte count (a bytes after record type).
 */
uint8_t SREC_GetByteCount(char *tmp_line)
{
    return HexToDec(tmp_line[2], tmp_line[3]);
}

/**
 * @brief: Get Address in Hex
 * @input *tmp_line: a string
 * @input type: number of bytes for address, represents different types
 * @output: address field.
 */
uint32_t SREC_GetAddress(char *tmp_line, uint8_t type)
{
    uint8_t start = 3;
    uint32_t address;

    if (type == 2)
    {
        /* 4, 5, 6, 7 (16 bits) */
        address = HexToDec(tmp_line[start+1],tmp_line[start+2]);
        address = address << 8;
        address = address + HexToDec(tmp_line[start+3],tmp_line[start+4]);
    }

    if (type == 3)
    {
        /* 4, 5, 6, 7, 8, 9 (24 bits) */
        address = HexToDec(tmp_line[start+1],tmp_line[start+2]);
        address = address << 8;
        address = address + HexToDec(tmp_line[start+3],tmp_line[start+4]);
        address = address << 8;
        address = address + HexToDec(tmp_line[start+5],tmp_line[start+6]);
    }

    if (type == 4)
    {
        /* 4, 5, 6, 7, 8, 9, 10, 11 (32 bits) */
        address = HexToDec(tmp_line[start+1],tmp_line[start+2]);
        address = address << 8;
        address = address + HexToDec(tmp_line[start+3],tmp_line[start+4]);
        address = address << 8;
        address = address + HexToDec(tmp_line[start+5],tmp_line[start+6]);
        address = address << 8;
        address = address + HexToDec(tmp_line[start+7],tmp_line[start+8]);
    }

    return address;
}

/**
 * @brief: Get Data in Hex
 * @input *tmp_line: a string
 * @input type: number of bytes for address, represents different types
 * @output: data array.
 */
uint8_t *SREC_GetData(char *tmp_line, uint8_t type)
{
    static uint8_t data[30];
    uint8_t data_index = 0;
    uint8_t i;

    if (type == 2)
    {
        for (i = DATA_OFFSET_2BYTES; i < (SREC_GetLength(tmp_line)-2); i=i+2)
        {
            data[i - DATA_OFFSET_2BYTES - data_index] = HexToDec(tmp_line[i], tmp_line[i+1]);
            data_index++;
        }
    }

    if (type == 3)
    {
        for (i = DATA_OFFSET_3BYTES; i < (SREC_GetLength(tmp_line)-2); i=i+2)
        {
            data[i - DATA_OFFSET_3BYTES - data_index] = HexToDec(tmp_line[i], tmp_line[i+1]);
            data_index++;
        }
    }

    if (type == 4)
    {
        for (i = DATA_OFFSET_4BYTES; i < (SREC_GetLength(tmp_line)-2); i=i+2)
        {
            data[i - DATA_OFFSET_4BYTES - data_index] = HexToDec(tmp_line[i], tmp_line[i+1]);
            data_index++;
        }
    }

    return data;
}

/**
 * @brief: Get Checksum in Hex
 * @input *tmp_line: a string
 * @output: actual checksum (the last byte).
 */
uint8_t SREC_GetCheckSum(char *tmp_line)
{
    return HexToDec(tmp_line[SREC_GetLength(tmp_line)-2], tmp_line[SREC_GetLength(tmp_line)-1]);
}

/**
 * @brief: Calculate checksum (add + mask + complement)
 * @input *tmp_line: a string
 * @output: calculated checksum in Hex.
 */
uint8_t SREC_CalCheckSum(char *tmp_line)
{
    uint32_t cal_checksum = 0;
    uint8_t i;

    /* Add: add each byte, start with byte_count */
    cal_checksum = SREC_GetByteCount(tmp_line);

    for ( i = 4 ; i < (SREC_GetLength(tmp_line)-2) ; i++ )
    {
        cal_checksum = cal_checksum + HexToDec(tmp_line[i], tmp_line[i+1]);
        i++;
    }

    /* Mask: keep the least significant byte of the total */
    cal_checksum = cal_checksum & 0x00FF;

    /* Complement: compute ones' complement of the least significant byte */
    cal_checksum = 0xFF - cal_checksum;

    return cal_checksum;
}
/*******************************************************************************
 * Support functions
 ******************************************************************************/
/**
 * @brief: Character to Number Conversion
 * @input c: a character within range: 0 --> 9 ; A --> F
 * @output: a number uint8_t
 */
uint8_t CharToNum(char c)
{
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

/**
 * @brief: Hexa to Decimal conversion
 *         Left shift 4 is analogue to multiplied by 16
 * @input a, b: 2 characters
 * @output: a decimal number is converted from a hex string combination.
 * @example: a string 'AF' --> AF or 10x16+15 = 160+15 = 175
 * @note: addition is higher priority than bitwise operator */
uint32_t HexToDec(char a, char b)
{
    return((CharToNum(a) << 4) + CharToNum(b));
}
