#include "HAL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int kmc_read_sector(unsigned long index, uint8_t *buff)    {
    if(NULL == buff){
        return EXIT_FAILURE;
    }
    
    fseek(fp, index * sectorLength, SEEK_SET);
    if(feof(fp)){
        return EXIT_FAILURE;
    }    
    fread(buff,sizeof(uint8_t), sectorLength, fp);
    return sectorLength;
}

int kmc_read_multi_sector(unsigned long index, unsigned int num, uint8_t *buff){
    if(NULL == buff){
        return EXIT_FAILURE;
    }
    
    fseek(fp, index * sectorLength, SEEK_SET);
    if(feof(fp)){
        return EXIT_FAILURE;
    }
    fread(buff,sizeof(uint8_t), num * sectorLength, fp);
    return num * sectorLength;
}

