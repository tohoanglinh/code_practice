/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_file.h"
#include "HAL.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*FAT12 can organize max 2847 data's clusters*/
#define MaxClusterNum 2847

#define Invalid 0
#define Folder 0x10
/*******************************************************************************
 * Variables
 ******************************************************************************/
FILE *file;

/*******************************************************************************
 * Codes
 ******************************************************************************/
int main()
{
    /*declare variables*/
    uint16_t i;

    /*user chooses ID to open file*/
    uint8_t chooseFile = 1;
    
    /*file ID*/
    uint8_t *fileNum;

    /*cluster of data*/
    uint32_t Cluster[MaxClusterNum];

    /*atribute of file*/
    uint32_t Attributes[MaxClusterNum];

    /*buffer stores data*/
    unsigned char *buff;

    /*alocating memory for buffer*/
    buff = (char*) malloc(SectorRange);

    /*if alocating process fail*/
    if(buff == NULL)
    {
        printf("Can not malloc buff\n");
        return 0;
    }

    /*read boot sector and push data to buff*/
    kmc_read_sector(0,buff);

    /*casting data type*/
    FAT12BootSector *bootsector = (FAT12BootSector *) buff;

    /*display boot sector's information*/
    readBootSector(showInfor);

    /*display rood directory information*/
    printf("\n\nRoot Directory Entry:\n\n");

    /*show information of root directory*/
    readDirectory(showInfor, &Cluster, &Attributes, &fileNum);

    printf("\n");

    /*user's choice to read file, insert '0' to quit program*/
    while(chooseFile != Invalid)
    {
        printf("\nInsert the order of file to open or '0' to quit:  ");
        scanf("%d", &chooseFile);

        printf("\n");

        /*if chooseFile belongs to array of file order and differs from '0'*/
        if(chooseFile != Invalid && chooseFile <= fileNum)
        {
            /*if folder does not consit of sub folders*/
            if(Attributes[Cluster[chooseFile]] != Folder)
            {
                /*read respectively data*/
                readData(Cluster[chooseFile]);
            }

            /*if file choose to open consists of back to open directory character*/
            else if(Cluster[chooseFile] == 0)
            {
                /*display rood directory information*/
                printf("\n\nRoot Directory Entry:\n\n");

                /*display boot sector's information*/
                readDirectory(showInfor, &Cluster, &Attributes, &fileNum);
            }

            else
            {
                /*read sub directory*/
                readSubDirectory(Cluster[chooseFile], &Cluster, &Attributes, &fileNum);
            }

        }

        /*if user want to close program*/
        else if(chooseFile == 0)
        {
            printf("\nQuit program, thank for using.\n");
        }

        /*if chooseFile is out of the file's list*/
        else
        {
            printf("\nInvalid ID\n");
        }
    }

    /*free memory*/
    free(buff);

    /*close file*/
    fclose(file);

    return 0;
}
