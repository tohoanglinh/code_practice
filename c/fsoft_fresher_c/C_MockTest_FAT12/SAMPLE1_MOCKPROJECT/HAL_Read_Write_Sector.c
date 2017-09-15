#include <stdio.h>
#include "HAL_Read_Write_Sector.h"
#include "FAT.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*
 Read sector thu index vao buff, tra ve so byte duoc doc 
 */
int kmc_read_sector(unsigned long index, unsigned char *buff)
{
    
    file = fopen("floppy.img", "rb");
    fseek(file, SIZE_SECTOR * index, SEEK_SET);
    fread(buff, 1, SIZE_SECTOR, file);
    return SIZE_SECTOR;
}
/*
 Doc num sector lien tiep, bat dau tu sector thu index, vao mang tro buff, tra ve so byte duoc doc 
 */
int kmc_read_multi_sector(unsigned long index, unsigned int num, unsigned char *buff)
{
    file = fopen("floppy.img", "rb");
    fseek(file, SIZE_SECTOR * index, SEEK_SET);
    fread(buff, 1, SIZE_SECTOR * num, file);
    return (num*SIZE_SECTOR);
}




