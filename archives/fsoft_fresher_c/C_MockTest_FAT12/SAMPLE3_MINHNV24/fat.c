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
/*Make a new FAT table from FAT12 table*/
uint16_t* FAT_newFat(uint16_t size,uint8_t *buff)
{
    uint32_t i;
    uint16_t* newFat;
    tempFat_t tempFat;
    newFat=(uint16_t*)malloc (size*SECTOR_SIZE*sizeof(uint16_t));
    /*Group 3 byte in FAT to 2 units(2 bytes) in new FAT*/
    for (i=0;i<size*SECTOR_SIZE/GROUP_3_BYTE;i++)
    {
        tempFat.Element1=((buff[3*i+1]&MASK_FAT_1)<<MOVE_ONE_BYTE)|buff[3*i];
        tempFat.Element2=((buff[3*i+2]<<MOVE_ONE_BYTE)|(buff[3*i+1]&MASK_FAT_2))>>MOVE_HALF_BYTE;
        newFat[2*i]=tempFat.Element1;
        newFat[2*i+1]=tempFat.Element2;
    }
    return newFat;
}

/*Make a FAT chain of index parameter*/
uint16_t *FAT_readFatChain(uint16_t in,uint16_t *newFat)
{
    uint16_t* fatChain;
    uint16_t i=0;
    fatChain=(uint16_t*)malloc (MAX_FATCHAIN_SIZE*sizeof(uint16_t));
    if(in<RESERVED_FAT)
    {
        /*Virtual FAT chain for root directory*/
        fatChain[0]=FAT_ROOT_BEGIN;
        fatChain[1]=FAT_ROOT_END;
    }
    else
    {
        fatChain[0]=in;
        fatChain[1]=newFat[in];
        do
        {
        i++;
        fatChain[i+1]=newFat[fatChain[i]];
        }
        while (fatChain[i+1]!=END_FAT);
    }
    return fatChain;
}
