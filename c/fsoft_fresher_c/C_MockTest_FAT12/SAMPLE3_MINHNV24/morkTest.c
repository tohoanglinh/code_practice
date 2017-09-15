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
int main()
{
FILE *p_file = fopen("floppy.img", "rb");
int16_t inputMenu;

uint16_t fatIndex;
uint16_t rootDirIndex;
uint16_t dataRegionIndex;
uint16_t rootDirSize;
uint16_t fatTableSize;
uint8_t fileType;
uint16_t secPerClus;

uint8_t *buffBootSector;    /*SECTOR_SIZE*/
uint8_t *buffFat;           /*fatTableSize*SECTOR_SIZE*/
uint16_t *newFat;           /*MAX_BUFF_SIZE*/
uint16_t *fatChain;         /*MAX_BUFF_SIZE*/

/*Read boot sector*/
buffBootSector=(uint8_t *) malloc(SECTOR_SIZE*sizeof(uint8_t));
FAT_readMultiSector(p_file,INDEX_BOOT_SECTOR,BOOT_SECTOR_SIZE, buffBootSector);
FAT_readBootSector(buffBootSector);

/*Find Index*/
FAT_findIndex (&fatIndex,&rootDirIndex,&dataRegionIndex,&secPerClus,buffBootSector);
rootDirSize=dataRegionIndex-rootDirIndex;
fatTableSize=rootDirIndex-fatIndex;
free(buffBootSector);

/*New FAT*/
buffFat=(uint8_t *) malloc(fatTableSize*SECTOR_SIZE*sizeof(uint8_t));
FAT_readMultiSector(p_file,fatIndex,fatTableSize,buffFat);
newFat=FAT_newFat(fatTableSize,buffFat);
free(buffFat);

/*App print Root*/
printf("\n-----------------------------------------------------------\n");
printf("<ROOT FOLDER> ");
printf("\n-----------------------------------------------------------\n");

fileType=FOLDER_;
fatChain=FAT_readFatChain(INDEX_BOOT_SECTOR,newFat);
FAT_readData (p_file,fatChain,fileType,rootDirIndex,rootDirSize,secPerClus);
free (fatChain);

/*App print Directory*/
while (1)
{
    if(fileType==FOLDER_)
    {
        printf("Input entry you want to read <example: 1> : ");
    }
    else printf("Type 0 please:  ");
    scanf("%d",&inputMenu);
    if (inputMenu<EXIT_CONDITION)
    {
        printf("Exiting...............");
        break;
    }
    printf("\n-----------------------------------------------------------\n");
    printf(".    is current folder\n..   is back to previous folder\nInput -1 to exit program");
    printf("\n-----------------------------------------------------------\n");

    fileType=g_menu.type[inputMenu];
    fatChain=FAT_readFatChain(g_menu.index[inputMenu],newFat);
    FAT_readData (p_file,fatChain,fileType,rootDirIndex,rootDirSize,secPerClus);
    free (fatChain);
}

free (newFat);
fclose (p_file);
return 0;
}
