/*******************************************************************************
 * @dev: LinhTH8 [FR_EMB_HN17_01]
 * @men: MinhNQ2
 * @tit: MockTest1 FAT12
 * @dat: 25/1 - 9/2
 * @file: HAL.c
 * HAL - Hardware Abstraction Layer: a layer of programming that
 * allows a computer os to interact with a hardware device.
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>

#include "HAL.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
FILE *file;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* read one sector index into buff */
uint32_t kmc_read_sector (uint32_t indexSector, uint8_t *buff)
{
	uint32_t byte_read;
	
    /* open file image in binary read mode */
    file = fopen(FILE_PATH, "rb");

    /* start, seek to position of sector index */
    fseek(file, SIZE_SECTOR * indexSector, SEEK_SET);

    /* read a sector (512 bytes) into buff*/
    byte_read = fread(buff, sizeof(uint8_t), SIZE_SECTOR, file);
    
    return byte_read;
    
    /* close file */
    fclose(file);
}


/* read num sector contiguously, start from sector index, into array pointer buff */
uint32_t kmc_read_multi_sector (uint32_t indexSector, uint16_t num, uint8_t *buff)
{
	uint32_t byte_read;
	
    /* open file image in binary read mode */
    file = fopen(FILE_PATH, "rb");

    /* start from position of sector index */
    fseek(file, SIZE_SECTOR * indexSector, SEEK_SET);

    /* read multi sector (512*num) into buff */
    byte_read = fread(buff, sizeof(uint8_t), SIZE_SECTOR * num, file);

    /* return num of read byte */
    return byte_read;

    /* close file */
    fclose(file);
}
