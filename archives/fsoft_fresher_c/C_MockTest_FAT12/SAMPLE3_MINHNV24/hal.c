#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "morkTest.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
 
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*Index means the name of sector*/
uint16_t FAT_readSector(FILE* p_file, uint32_t index, uint8_t *buff)                    
{
    fseek(p_file, INDEX_BOOT_SECTOR, SEEK_SET);
    fseek(p_file, index*SECTOR_SIZE, SEEK_SET);
    fread(buff, SECTOR_SIZE, 1, p_file);
    return SECTOR_SIZE;
}

uint16_t FAT_readMultiSector(FILE* p_file, uint32_t index,uint32_t num, uint8_t *buff)                  
{
    uint16_t byteRead;
    uint32_t i;
    fseek(p_file, INDEX_BOOT_SECTOR, SEEK_SET);
    for(i=0;i<num;i++)
    {
        FAT_readSector(p_file,index+i,&buff[i*SECTOR_SIZE]);
    }
    byteRead=SECTOR_SIZE*(i+1);
    return byteRead;
}
