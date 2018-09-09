#ifndef _HAL_Read_Write_Sector_H_
#define _HAL_Read_Write_Sector_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
#define SIZE_SECTOR 512
/*
 Read sector thu index vao buff, tra ve so byte duoc doc
 */
int kmc_read_sector(unsigned long index, unsigned char *buff);
/*
 Doc num sector lien tiep, bat dau tu sector thu index, vao mang tro buff, tra ve so byte duoc doc
 */
int kmc_read_multi_sector(unsigned long index, unsigned int num, unsigned char *buff);

#pragma pack(pop)

#endif


