#ifndef _HAL_H_
#define _HAL_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint16_t     sectorLength;
FILE         *fp;

int kmc_read_sector(unsigned long index, uint8_t *buff);

int kmc_read_multi_sector(unsigned long index, unsigned int num, uint8_t *buff);

#endif /* _HAL_H_ */
