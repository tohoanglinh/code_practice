/**
 * @file      srec.h
 * @developer LinhTH8
 * @mentor    HaiND1
 * @topic     MockTest2-File Handling and Debug
 * @requires  S-Record Parse to information: Address & Data
 */

#ifndef _SREC_H_
#define _SREC_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef struct SREC
{
    uint8_t type;
    uint8_t length;
    uint8_t bytecount;
    uint32_t address;
    uint8_t *data;
    uint8_t get_checksum;
    uint8_t cal_checksum;
    uint8_t data_bytecount;
    uint8_t checksum_bytecount;
} SREC_struct_t;

#define DATA_OFFSET_2BYTES  8
#define DATA_OFFSET_3BYTES  10
#define DATA_OFFSET_4BYTES  12

#define DEBUG 0
/*******************************************************************************
 * API
 ******************************************************************************/
void SREC_ParseLine(char tmp_line[]);
void SREC_DisplayLine(char tmp_line[]);
void SREC_FlashLine(char tmp_line[]);
uint8_t SREC_Format(char *tmp_line);
uint8_t SREC_GetLength(char *tmp_line);
uint8_t SREC_GetType(char *tmp_line);
uint8_t SREC_GetByteCount(char *tmp_line);
uint32_t SREC_GetAddress(char *tmp_line, uint8_t type);
uint8_t *SREC_GetData(char *tmp_line, uint8_t type);
uint8_t SREC_GetCheckSum(char *tmp_line);
uint8_t SREC_CalCheckSum(char *tmp_line);
uint8_t CharToNum(char c);
uint32_t HexToDec(char a, char b);

#endif /* _SREC_H_ */
