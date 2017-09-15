#include <string.h>
#include "read_file.h"
/*
 *find out next cluster of data in FAT table
*/
static uint32_t findNextCluster(uint32_t fat_offset, uint32_t cluster)
{
    /*declare variables*/
    uint32_t index=0, EntryOffset=0, NextCluster=0;

    /*index is position of data in FAT table*/
    index = (cluster * 3 / 2) / SectorRange;

    /*EntryOffset is the first position of data's cluster*/
    EntryOffset = (cluster * 3 / 2) % SectorRange;

    /*allocate memory for buffer*/
    unsigned char *buff = (unsigned char *) malloc (SectorRange);

    /*if can not allocate memory*/
    if(buff==NULL)
    {
        printf("\ncan not malloc buffer");
        return -1;
    }
    /*allocate memory successfully*/
    else
    {
        /*1 in (index + 1) is the only sector of boot sector*/
        fat_offset = index + 1;

        /*read cluster for finding next cluster, each cluster stores address of next cluster*/
        kmc_read_sector(fat_offset, buff);

        /*if cluster is even number*/
        if(cluster % 2 == 0)
        {
            /*access under the rule of FAT12, each cluster takes up 1.5 bytes*/
            NextCluster = buff[EntryOffset] | ((buff[EntryOffset + 1] & 0x0F) << 8);
        }

        /*if cluster is odd number*/
        else
        {
            /*access under the rule of FAT12, each cluster takes up 1.5 bytes*/
            NextCluster = (buff[EntryOffset] >> 4) | (buff[EntryOffset + 1] << 4);
        }

        /*free memory*/
        free(buff);
    }

    return NextCluster;
}

/*
 *read boot sector, show boot sector's arguments and calcualte needed arguments
*/
FAT12BootSector *readBootSector(uint8_t choice)
{
    /*allocate memory for buffer*/
    char *buff = (char *)malloc(SectorRange);

    /*declare variable type FAT12BootSector*/
    FAT12BootSector *bootsector;

    /*if allocate fail*/
    if(buff == NULL)
    {
        printf("can not malloc buffer");
        return (FAT12BootSector *)-1;
    }

    /*if allocate successfuly*/
    else
    {
        /*read boot sector and push data to buffer*/
        kmc_read_sector(0, buff);

        /*cast data type*/
        bootsector = (FAT12BootSector *) buff;

        /*if user choices is to show information*/
        if(choice == showInfor)
        {
            printf("  Number byte Fat12BootSector       : %d\n", sizeof(FAT12BootSector));
            printf("  Jump code                         : %02X:%02X:%02X\n", bootsector->Jmp[0], bootsector->Jmp[1], bootsector->Jmp[2]);
            printf("  OEM code                          : %.8s\n", bootsector->Oem);
            printf("  Bytes per sector                  : %d\n", bootsector->BytePerSector);
            printf("  Sectors per cluster               : %d\n", bootsector->SectorPerClustor);
            printf("  Number of reserved sector         : %d\n", bootsector->ReservedSector);
            printf("  Number of fats                    : %d\n", bootsector->NumFat);
            printf("  Max number of root dir entries    : %d\n", bootsector->MaxDirEntry);
            printf("  Total sectors count               : %d\n", bootsector->TotalSectorCount);
            printf("  Sector per FAT                    : %d\n", bootsector->SectorPerFAT);
            printf("  Sectors per track                 : %d\n", bootsector->SectorPerTrack);
            printf("  Number of heads                   : %d\n", bootsector->NumHead);
            printf("  Boot signature                    : 0x%02X\n", bootsector->BootSignature);
            printf("  Volume id                         : 0x%08X\n", bootsector->VolumeId);
            printf("  Volume label                      : %.11s\n", bootsector->VolumeLabel);
            printf("  Filesystem type                   : %.5s\n", bootsector->FileSystemType);
        }

    }

    return bootsector;

    /*free buffer*/
    free(buff);
}

/*
 *read directory
*/
uint8_t readDirectory(uint8_t mode, uint32_t *FirstCluster, uint32_t *Attributes, uint8_t *fileNum)
{
    /*declare variables*/
    uint16_t i,j;

    *fileNum = 0;

    /*buffer stores data*/
    unsigned char *buff;

    /*declare for function "readBootSector()"*/
    uint32_t bootSector, rootDirOffset, dataOffset, NumFat, SectorPerFat, BytePerSector, MaxDirEntry;

    /*choose to calculate needed data*/

    FAT12BootSector *bootsector = readBootSector(calculate);
    bootSector = bootsector->ReservedSector;
    NumFat = bootsector->NumFat;
    SectorPerFat = bootsector->SectorPerFAT;
    BytePerSector = bootsector->BytePerSector;
    MaxDirEntry = bootsector->MaxDirEntry;

    /*find the directory's first position, 1 corresponds to boot sector's range, bytes of FAT = number of FAT * sector per FAT*/
    uint32_t DirectoryFirstPosition = ((bootSector + (NumFat * SectorPerFat)) * BytePerSector)/512;

    /*allocate memory for buffer, each directory consist of 224 entry, each entry had 32 bytes*/
    buff = (char*) malloc(32 * MaxDirEntry);

    /*if can not malloc buffer*/
    if(buff == NULL)
    {
        printf("Can not malloc buff\n");
        return 0;
    }

    /*read 14 consecutive bytes from DirectoryFirstPosition*/
    /*14 = (224 entry * 32 bytes / 512 (size of sector))*/
    kmc_read_multi_sector(DirectoryFirstPosition, 14, buff);

    /*casting data type*/
    FAT12DirectoryEntry *directory = (FAT12DirectoryEntry*) buff;

    for(i=0; i < MaxDirEntry; i++)
    {
        /*if file is empty or to be deleted*/
        if(directory->FileName[0]==0x00||directory->FileName[0]==0xE5)
        {
             break;
        }

        /*if file is not long file name*/
        if(directory->Attributes!=0x0F)
        {
            Attributes[directory->FirstCluster] = directory->Attributes;
            /*increase the file's order*/
            (*fileNum)++;

            /*store first cluster into FirstCluster*/
            FirstCluster[*fileNum] = directory->FirstCluster;

            /*if user chooses to show directory information*/
            if(mode == showInfor)
            {
                printf("ID %d    ",*fileNum);

                /*show file name*/
                for(j=0; j<strlen(directory->FileName); j++)
                {
                    printf("%c", directory->FileName[j]);
                }
                /*print files information*/
                printf("   Atribute %02X    First Cluster: %d    Size: %04X\n", directory->Attributes, directory->FirstCluster, directory->FileSize);
                printf("\n");
            }
        }
        /*move to next directory*/
        directory++;
    }

    /*free memory*/
    free(buff);

    /*return file's total number*/
    return 0;
}

/*
 *display data
*/
static void print_str (char *buf, int size)
{
    int i;
    for (i=0; i < size; i++)
    {
        /*if buf[i] differs from "bip" character*/
        if(buf[i]!=7)
        printf ("%c", buf[i]);
    }

}

/*
 *read data
*/
void readData(uint32_t cluster)
{
    /*the first position of data*/
    uint32_t offsetData;

    /*declare for function "readBootSector()"*/
    uint32_t bootSector, rootDirOffset, dataOffset, NumFat, SectorPerFat, BytePerSector, MaxDirEntry;

    /*choose to calculate needed data*/

    readBootSector(calculate);

    FAT12BootSector *bootsector = readBootSector(calculate);
    
    bootSector = bootsector->ReservedSector;
    rootDirOffset = bootSector + (bootsector->NumFat * bootsector->SectorPerFAT);
    dataOffset = rootDirOffset + (bootsector->MaxDirEntry * 32) / bootsector->BytePerSector;

    /*allocate memory for buffer*/
    char *buff = (char *) malloc(SectorRange);

    /*show data*/
    do
    {
        /*move to first address of needed data*/
        offsetData = dataOffset + (cluster - 2);

        /*take turn to read all sectors from the first one*/
        kmc_read_sector(offsetData, buff);

        /*print each sector*/
        print_str (buff, SectorRange);

        /*move to next cluster of data*/
        cluster = findNextCluster(bootSector,cluster);
    }
    /*loop until encountering the end of data chain*/
    while(cluster <= 0xFF7);

    /*free buffer*/
    free(buff);
}

/*
 *read Sub Directory
*/
uint8_t readSubDirectory(uint32_t FirstCluster, uint32_t *Cluster, uint32_t *Attributes, uint8_t *fileNum)
{
    /*declare variables*/
    uint32_t i,j;

    /*the first cluster's position in data fild*/
    uint32_t offsetCluster;

    /*ID of file*/
    *fileNum = 0;

    /*allocate memory for buffer*/
    char *buff = (char *) malloc(SectorRange);

    /*33 is the first position of data fild, 2 is the first 2 cluster of data fild*/
    offsetCluster = FirstCluster + 33 - 2;

    /*read data and push to buffer*/
    kmc_read_sector(offsetCluster, buff);

    /*casting data type*/
    FAT12DirectoryEntry *directory = (FAT12DirectoryEntry*) buff;

    printf("\nSub Directory Entry:\n");

    for(i=0;i < SectorRange;i+=32)
    {
        /*if file is empty or to be deleted*/
        if(directory->FileName[0]==0x00||directory->FileName[0]==0xE5)
            break;
        if(directory->Attributes!=0x0F)
        {
            /*increase file's ID*/
            (*fileNum)++;

            /*take file's attribute*/
            Attributes[directory->FirstCluster] = directory->Attributes;

            /*store first cluster into FirstCluster*/
            Cluster[*fileNum] = directory->FirstCluster;

            /*show ID of files*/
            printf("ID %d    ",*fileNum);

            /*printf file's name*/
            for(j=0; j<strlen(directory->FileName); j++)
            {
                printf("%c", directory->FileName[j]);
            }

            /*print files information*/
            printf("   Atribute %02X    First Cluster: %d    Size: %04X\n",  directory->Attributes, directory->FirstCluster, directory->FileSize);
            printf("\n");
        }
        /*move to next directory*/
        directory++;
    }
    /*free memory*/
    free(buff);
    return 0;
}
