#ifndef __read_file__
#define __read_file__

#include "HAL.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*define user's choice for function "readBootSector();"*/
/*showInfor: show information of boot sector*/
/*calculate: just calculating and return the needed values for other functions*/
#define showInfor 0
#define calculate 1

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*
 *find out next cluster of data in FAT table
*/
static uint32_t findNextCluster(uint32_t fat_offset, uint32_t cluster);

/*
 *read data
 *@cluster: the first position of data's address
*/
void readData(uint32_t cluster);

/*
 *read data
 *@mode: user's choice to show or just calculating data
 *@FirstCluster: the first data address
 *@storeFirstCluster: store first cluster's value for choosing to open file
*/
uint8_t readDirectory(uint8_t mode, uint32_t *FirstCluster, uint32_t *Attributes, uint8_t *fileNum);

/*
 *display data
*/
static void print_str (char *buf, int size);

/*
 *read Sub Directory
*/
uint8_t readSubDirectory(uint32_t FirstCluster, uint32_t *Cluster,uint32_t *Attributes, uint8_t *fileNum);

#pragma pack(push, 1)
typedef struct
{
    unsigned char Jmp[3];
    unsigned char Oem[8];
    uint16_t BytePerSector;
    uint8_t  SectorPerClustor;
    unsigned short ReservedSector;
    uint8_t NumFat;
    uint16_t MaxDirEntry;
    uint16_t TotalSectorCount;
    uint8_t Ignore;
    unsigned short SectorPerFAT;
    unsigned short SectorPerTrack;
    unsigned short NumHead;
    unsigned char Ignore2[4];
    uint32_t TotalSectorCountFAT32;
    unsigned short Ignore3;
    unsigned char BootSignature;
    uint32_t VolumeId;
    unsigned char VolumeLabel[11];
    unsigned char FileSystemType[8];
}
FAT12BootSector;

typedef struct
{
    unsigned char FileName[8];
    unsigned char Extension[3];
    uint8_t  Attributes;
    unsigned short Reserved;
    unsigned short CreateTime;
    unsigned short CreateDate;
    unsigned short LastAccessDate;
    unsigned short Ignore;
    unsigned short LastWriteTime;
    unsigned short LastWriteDate;
    unsigned short FirstCluster;
    unsigned long FileSize;
}
FAT12DirectoryEntry;

/*
 *read boot sector for reading data
 *@choice: user's choice to show or just calculating data
*/
FAT12BootSector *readBootSector(uint8_t choice);

#pragma pack(pop)
#endif
