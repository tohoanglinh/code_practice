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
/*Find index of Fat, root and Data cluster region*/
uint16_t FAT_findIndex(uint16_t *fatIndex,uint16_t *rootDirIndex,uint16_t *dataRegionIndex,uint16_t *secPerClus,uint8_t *buff)
{
    bootSector_t* p_bootSector;
    p_bootSector=(bootSector_t*) buff;
    /*Index mean the number of sector from sector 0- boot sector*/
    *fatIndex=INDEX_BOOT_SECTOR + p_bootSector->reserved_sectors;
    *rootDirIndex=*fatIndex + p_bootSector->number_of_fats*p_bootSector->fat_size_sectors;
    *dataRegionIndex=*rootDirIndex + p_bootSector->root_dir_entries*DIR_ENTRY_SIZE/p_bootSector->sector_size;
    *secPerClus=p_bootSector->sectors_per_cluster;
}

/*Read BootSector to find Index*/
uint16_t FAT_readBootSector(uint8_t *buff)
{
    bootSector_t* p_bootSector;
    p_bootSector=(bootSector_t*) buff;
}

/*Read directory*/
uint16_t FAT_readFolder(uint8_t *buff)
{
    uint16_t i=0;
    directoryEntry_t *p_directoryEntry;
    while (1)
    {
        p_directoryEntry=(directoryEntry_t*) buff;
        if (p_directoryEntry->name[0]==0) break;
        if(buff[LFN_ATTRIBUTE_POSITION]!=LONG_FILE_NAME_ATTRIBUTE)
        {
            i++;
            printf(" %d. ", i);
            printf(" %.8s ", p_directoryEntry->name);
            printf("% 5.3s  ", p_directoryEntry->extension);
            printf("   %d bytes \n", p_directoryEntry->file_size_byte);
            g_menu.index[i]=p_directoryEntry->first_cluster_index;
            if(p_directoryEntry->extension[0]==EMPTY_ENTRY)
            {
                g_menu.type[i]=FOLDER_;
            }
            else
            {
                g_menu.type[i]=FILE_;
            }
        }
        buff=buff+DIR_ENTRY_SIZE;
    }
    /*Put other index not show stored in g_menu to 0*/
    /*if input a number not is entry showed, we will move to root folder*/
    i++;
    while (g_menu.index[i]!=0)
    {
        g_menu.type[i]=0;
        g_menu.index[i]=0;
        i++;
    }
}

/*Read data*/
uint16_t FAT_readData (FILE* p_file,uint16_t *fatChain,uint8_t fileType,uint16_t rootIndex,uint16_t rootSize,uint16_t secPerClus)
{
    uint8_t* buff;
    uint16_t dataIndex=0;
    buff=(uint8_t*)malloc (MAX_CLUSTER_READ_SIZE*sizeof(uint8_t));
    uint16_t i=0,j=0;
    dataIndex=rootIndex+rootSize;
    /*Root*/
    if (fatChain[0]<RESERVED_FAT)
    {
        /*fatChain[0]<2 means index of virtual chain point to Root*/
        /*Find number of meaning sector root directory*/
        FAT_readMultiSector(p_file,rootIndex,rootSize, buff);
        FAT_readFolder(buff);
        free(buff);
    }
    /*Except Root*/
    else
    {
        while (fatChain[i]!=END_FAT)
        {
            FAT_readMultiSector(p_file,(fatChain[i]-RESERVED_FAT)*secPerClus+dataIndex,secPerClus,buff);
            if (fileType==FILE_)
            {
                /*Print each cluster*/
                for(j=0;j<SECTOR_SIZE*secPerClus;j++)
                {
                    /*Do not show character '7' which make beep sound*/
                    if (buff[j]!=7)printf("%c",buff[j]);
                }
            }
            else
            {
                FAT_readFolder(buff);
            }
            printf("\n");
            i++;
        }
        free(buff);

        /*Exit to previous folder after reading file*/
        if (fileType==FILE_)
        {
            /*Change type store in g_menu from 1 (file) to 0 (folder)*/
            g_menu.type[0]=0;
            printf("\n-----------------------------------------------------------\n");
            printf("Please type 0 to escape file and move back___\n\n");
        }
        else
        {
            /*Fat Chain No 0 store the current folder Index before move to file*/
            g_menu.index[0]=fatChain[0];
        }
    }
}
