#ifndef __HAL_H__
#define __HAL_H__

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* 2^9 = 512*/
#define ShiftByte      9
#define SectorRange    512

/*******************************************************************************
 * API
*******************************************************************************/

/*
* @kmc_read_sector: read a sector
* @file: input file
* @index: index of sector
* @buff: store sector's information
* @return: the number of read byte
*/
uint32_t kmc_read_sector(unsigned long index, unsigned char *buff);

/*
* @kmc_read_multi_sector: read multiple sectors
* @file: input file
* @index: index of sector
* @num: the number of read sector
* @buff: store sector's information
* @return: the number of read byte
*/
uint32_t kmc_read_multi_sector(unsigned long index, uint32_t num, unsigned char *buff);

#endif
