#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "HAL.h"
#include "Function.h"
#include "EntryList.h"

void readBootSector(boot_t *bootsect){
    fseek(fp, ROOT_DIR_OFFSET, SEEK_SET);
    fread(bootsect -> jump,sizeof(uint8_t),SIZE_JUMP,fp);
    fread(bootsect -> name,sizeof(uint8_t),SIZE_OEM_NAME,fp);
    fread(&(bootsect -> bytePerSector),sizeof(uint8_t),SIZE_BYTE_PER_SEC,fp);    
    fread(&(bootsect -> sectorsPerCluster),sizeof(uint8_t),SIZE_SECT_PER_CLUST,fp);
    fread(&(bootsect -> reservedSectors),sizeof(uint8_t),SIZE_RESERVE_SECT,fp);    
    fread(&(bootsect -> fats),sizeof(uint8_t),SIZE_FATS,fp);    
    fread(&(bootsect -> rootDirectoryEntries),sizeof(uint8_t),SIZE_ROOT_DIR_ENTR,fp);
    fread(&(bootsect -> logicalSectors),sizeof(uint8_t),SIZE_LOGICAL_SECT,fp);    
    fread(&(bootsect -> mediumDescriptorByte),sizeof(uint8_t),SIZE_MED_DESCRIPT_BYTE,fp);    
    fread(&(bootsect -> sectorsPerFat),sizeof(uint8_t),SIZE_SECT_PER_FAT,fp);    
    fread(&(bootsect -> sectorsPerTrack),sizeof(uint8_t),SIZE_SECT_PER_TRACK,fp);    
    fread(&(bootsect -> heads),sizeof(uint8_t),SIZE_HEAD,fp);
    fread(bootsect -> hiddenSectors,sizeof(uint8_t),SIZE_HIDDEN_SECT,fp);
    fread(bootsect -> code,sizeof(uint8_t),SIZE_CODE,fp);
    fread(&(bootsect -> marker),sizeof(uint8_t),SIZE_MARKER,fp);
}

void printBootSector(boot_t *bootsect){
    printf("\nOEM name: %s",bootsect -> name);    
    printf("\nByte per sector: %d",bootsect -> bytePerSector);
    printf("\nSectors per cluster: %d",bootsect -> sectorsPerCluster);
    printf("\nReserved sectors: %d",bootsect -> reservedSectors);
    printf("\nfirstClusterumber of fats: %d",bootsect -> fats);
    printf("\nRoot directory entries: %d",bootsect -> rootDirectoryEntries);
    printf("\nSectors per fats: %d",bootsect -> sectorsPerFat);
    printf("\nSectors per track: %d",bootsect -> sectorsPerTrack);
    printf("\nheads: %d",bootsect -> heads);
    printf("\nmarker: %x",bootsect -> marker);
}

uint16_t fatMapping(uint16_t firstCluster){
    
    uint8_t *secBuff = (uint8_t*)malloc(sectorLength * sizeof(uint8_t));
    if(NULL == secBuff){
        return EXIT_FAILURE;
    }
    
    uint16_t thisFATEntOffset;
    uint16_t thisEntryVal;
    uint16_t thisFATSecfirstClusterum;
    
    thisFATSecfirstClusterum = RESERVE_SECT_CNT + ((firstCluster + (firstCluster / 2)) / sectorLength);
    thisFATEntOffset = (firstCluster + (firstCluster / 2)) % sectorLength;
    
    kmc_read_sector(thisFATSecfirstClusterum, secBuff);

    if (firstCluster & 1) {
        thisEntryVal = (secBuff[thisFATEntOffset] >> 4) | ((uint16_t)secBuff[thisFATEntOffset + 1] << 4);
    } 
    else {
        thisEntryVal = secBuff[thisFATEntOffset] | ((uint16_t)(secBuff[thisFATEntOffset + 1] & 0x0F) << 8);
    }
    free(secBuff);
    return thisEntryVal;
}

int readFile(uint16_t firstCluster){
    
        uint8_t *buff = (uint8_t*)malloc(sectorLength * sizeof(uint8_t));
        char *str = (char*)malloc(sectorLength * sizeof(char));
        if ((NULL == buff) || (NULL == str))
        {
            return EXIT_FAILURE;
        }
        
        uint16_t entry_val = fatMapping(firstCluster);
        int i;
        int j = 1;
        
        printf("\n");
        printf("\n*********************************FILE CONTENT*********************************\n\n");
        fseek(fp, sectorLength * BYTE_OF_DIR + sectorLength * (firstCluster - 1), SEEK_SET);
        fgets (str, sectorLength, fp);
        printf("%s",str);
    
        while((entry_val != END_OF_FILE)){        
            j++;
            fseek(fp, sectorLength * BYTE_OF_DIR + sectorLength * (entry_val - 1), SEEK_SET);        
            fgets (str, sectorLength, fp);
            printf("%s",str);
            entry_val = fatMapping(entry_val);
        }
        printf("\n\n******************************************************************************\n");
        free(buff);
        free(str);
    
    return EXIT_SUCCESS;
}
