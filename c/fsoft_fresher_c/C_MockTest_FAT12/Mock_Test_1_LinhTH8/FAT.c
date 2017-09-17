/*******************************************************************************
 * @dev: LinhTH8 [FR_EMB_HN17_01]
 * @men: MinhNQ2
 * @tit: MockTest1 FAT12
 * @dat: 25/1 - 9/2
 * @file: FAT.c
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "FAT.h"
#include "HAL.h"

/*******************************************************************************
 * Prototypes (description in header file FAT.h)
 ******************************************************************************/
 FAT12BootSector_t *FAT_readBootSector(void);
 uint16_t FAT_readNextCluster(FAT12BootSector_t *bootSector, uint16_t cluster,uint8_t *buff_cluster);
 FAT12DirEntry_t *FAT_readRootDir(FAT12BootSector_t *bootSector);
 void FAT_readFile(FAT12BootSector_t *bootSector, uint16_t cluster);
 uint16_t FAT_readFolder(FAT12BootSector_t *bootSector, uint16_t cluster, uint32_t firstClusterID[], uint32_t attributes[]);
 void FAT_printBootSector (FAT12BootSector_t *bootSector);
 uint16_t FAT_printRootDir(FAT12DirEntry_t *dirEntry, FAT12BootSector_t *bootSector, uint32_t firstClusterID[], uint32_t attributes[]);

/*******************************************************************************
 * Code: FAT LIB MAIN FUNCTIONS
 *  readBootSector
 *  readFatNextCluster
 *  readRootDir
 *  readFile
 *  readFolder
 *  printBootSector
 *  printRootDir
 ******************************************************************************/
FAT12BootSector_t *FAT_readBootSector(void)
{
    uint8_t *buff_bootsector;

    buff_bootsector = (uint8_t *) malloc(SIZE_SECTOR);

    if (buff_bootsector == NULL)
    {
        printf("Not enough memory for reading Boot Sector.\n");
        return NULL;
    }
    else
    {
        /* read sector index 0 into buff */
        kmc_read_sector(BOOTSECTOR_INDEX,buff_bootsector);

        /* casting buff into data type of FAT12BootSector struct */
        return ((FAT12BootSector_t *) buff_bootsector);
    }
    free(buff_bootsector);
}

void FAT_printBootSector (FAT12BootSector_t *bootSector)
{
    /* display bootsector data information */
    printf("Boot Sector Data           :\n");
    printf(" Jump-to-Boot Code         : %X.%X.%X\n", bootSector->jmpBoot[0], bootSector->jmpBoot[1], bootSector->jmpBoot[2]);
    printf(" OEM                       : %s\n", bootSector->OEMName);
    printf(" Bytes per sector          : %d (bytes)\n", bootSector->BytesPerSector); /*FAT uses little endian 0x0200 = 512*/
    printf(" Sectors per cluster       : %d (sector)\n", bootSector->SectorsPerCluster);
    printf(" No of reserved sectors    : %d (sector)\n", bootSector->NoOfReservedSectors);
    printf(" No of FATs                : %d\n", bootSector->NoOfFATs);
    printf(" Root directory entries    : %d\n", bootSector->RootDirEntries);
    printf(" Total sector count (16b)  : %d\n", bootSector->TotalSectorCount12);
    printf(" Sectors per FAT           : %d (sectors)\n", bootSector->SectorsPerFAT);
    printf(" Sectors per track         : %d (sectors)\n", bootSector->SectorsPerTrack);
    printf(" Number of heads           : %d\n", bootSector->NoOfHeads);
    printf(" Total sector count (32b)  : %d\n", bootSector->TotalSectorCount32);
    printf(" Extended boot signature   : 0x%02X\n", bootSector->ExtendedBootSignature);
    printf(" Volume ID                 : 0x%02X\n", bootSector->VolumeID);
    printf(" Volume label              : %.11s\n", bootSector->VolumeLabel);
    printf(" File system type          : %.5s\n", bootSector->FileSystemType);
    printf(" Boot sector signature     : 0x%X 0x%X\n", bootSector->BootSectorSignature & 0xFF, (bootSector->BootSectorSignature & 0xFF00)>>8);
    SEPARATE_LINE();
}

/* Read address of cluster in FAT by bitwise operators &, |, << (left), >> (right) */
uint16_t FAT_readNextCluster(FAT12BootSector_t *bootSector, uint16_t cluster,uint8_t *buff_cluster)
{
    uint16_t cluster_index;
    uint16_t cluster_offset;

    uint16_t sizeSector = bootSector->BytesPerSector;
    uint16_t fatOffset = bootSector->NoOfReservedSectors;

    cluster_index = (cluster + cluster/2) / sizeSector;
    cluster_offset = cluster + cluster/2;

    if (buff_cluster == NULL)
    {
        printf("Unable to allocate memory for next cluster reading.\n");
        return 1;
    }
    else
    {
        fatOffset = fatOffset + cluster_index;

        /* Get each byte from Fat Array */
        uint16_t nHi = buff_cluster[cluster_offset+1];
        uint16_t nLo = buff_cluster[cluster_offset];

        /* Parse nHi nLo into Address of cluster */
        if (cluster % 2 == 0)
        {   /* cluster element #even */
            /* Example: k = 2 --> i = 2 * (3/2) = 3
             * nLo = Fat[3] = 0x03; nHi = Fat[4] = 0x7B; --> 0x0B03
             * Step 1:
             *  Mask 4 hi bits of nHi, Keep 4 lo bits of nHi
             *  nHi & 0x0F = 0x7B & 0x0F = 0x0B
             * Step 2:
             *  Left shift 8 bits
             *  (nHi & 0x0F) << 8 = 0x0B00
             * Step 3:
             *  OR (|) bitwise ~ add bits
             *  Add nLo with the above left shifted number
             *  (nLo | 0x0B00) = 0x0B03 = 0xB03
             * ==> return this number as address of next cluster
             */
            return (nLo | ((nHi & 0xF) << 8));
        }
        else
        {   /* cluster element #odd */
            /* Example: k = 3 --> i = 3 * (3/2) = 4
             * nLo = Fat[4] = 0x7B; nHi = Fat[5] = 0x8C; --> 0x08C7
             * Step 1:
             *  Left shift nHi 4 bits
             *  nHi << 4 = 0x08C0
             * Step 2:
             *  Right shift nLo 4 bits
             *  nLo >> 4 = 0x0007
             * Step 3:
             *  OR (|) bitwise ~ add bits
             *  0x08C0 | 0x0007 = 0x08C7
             * ==> return this number as address of next cluster
             */
            return ((nHi << 4) | (nLo >> 4));
        }
    }
}

FAT12DirEntry_t *FAT_readRootDir(FAT12BootSector_t *bootSector)
{
    uint8_t *buff_rootdir;
    uint32_t buff_root_memory;
    uint16_t sizeRootDir;
    uint8_t i;

    uint16_t sizeSector = bootSector->BytesPerSector;
    uint16_t fatOffset = bootSector->NoOfReservedSectors;
    uint16_t rootOffset = fatOffset + bootSector->NoOfFATs * bootSector->SectorsPerFAT;
    uint16_t dataOffset = rootOffset + bootSector->RootDirEntries * SIZE_ENTRY / sizeSector;

    /*
     * allocate memory (bytes) for rootdir reading, 1 root dir entry size = 32 bytes
     * total bytes needed for root dir entries = buff_root_memory =
     *      = no_of_root_entries * 32
     *      = (dataOffset - rootOffset) * sizeSector
     */
    buff_root_memory = (dataOffset - rootOffset) * sizeSector;

    buff_rootdir = (uint8_t *) malloc(buff_root_memory);

    if (buff_rootdir == NULL)
    {
        printf("Not enough memory for reading Root Dir.\n");
        return NULL;
    }
    else
    {
        /* read multi sectors of root dir entries into buff */
        sizeRootDir = kmc_read_multi_sector(rootOffset, buff_root_memory/sizeSector, buff_rootdir);

        /* casting buff_rootdir to struct FAT12DirEntry */
        return ((FAT12DirEntry_t *) buff_rootdir);
    }
    free(buff_rootdir);
}

uint16_t FAT_printRootDir(FAT12DirEntry_t *dirEntry, FAT12BootSector_t *bootSector, uint32_t firstClusterID[], uint32_t attributes[])
{
    uint8_t i;
    uint16_t fRootCount = 0;

    printf("Root Directory Data        :\n");
    printf("ID\tName\tExt\tCluster\tType\tSize\tModTime\t\tModDate\t\n");

    for (i = 0; i < bootSector->RootDirEntries ; i++)
    {
        /* check file name is valid or not */
        if ((dirEntry->FileName[0] == DIR_ENTRY_FREE1) || (dirEntry->FileName[0] == DIR_ENTRY_FREE2))
        {
            break;
        }
        /* check whether long file name (LFN) or not? If not, then print out file/folders in root */
        if (dirEntry->Attributes != ATTR_LFN)
        {
            fRootCount++;
            printf("%d\t", fRootCount);
            printf("%.8s", dirEntry->FileName);
            printf("%.3s\t", dirEntry->Extension);
            printf("%d\t", dirEntry->FirstLogicalCluster);
            firstClusterID[fRootCount]= dirEntry->FirstLogicalCluster;
            attributes[fRootCount] = dirEntry->Attributes;
            switch (dirEntry->Attributes)
            {
                case ATTR_READ_ONLY :
                    printf("ReadOnly\t");
                    break;
                case ATTR_HIDDEN :
                    printf("Hidden\t");
                    break;
                case ATTR_SUB_DIRECTORY :
                    printf("Folder\t");
                    break;
                case ATTR_ARCHIVE :
                    printf("Archive\t");
                    break;
                case ATTR_FILE :
                    printf("File\t");
                    break;
                default:
                    printf("Invalid\t");
            }
            printf("%d\t", dirEntry->FileSizeBytes);
            FAT_timeExtract(dirEntry->LastWriteTime);
            FAT_dateExtract(dirEntry->LastWriteDate);
        }
        /* increase pointer to point to the next dir Entry */
        dirEntry++;
    }
    SEPARATE_LINE();
    return fRootCount;
}

void FAT_readFile(FAT12BootSector_t *bootSector, uint16_t cluster)
{
    uint16_t fileSize;
    uint16_t sectorOffset;
    uint16_t i;

    /* extract some offset information for later usage */
    uint16_t sizeSector = bootSector->BytesPerSector;
    uint16_t fatOffset = bootSector->NoOfReservedSectors;
    uint16_t rootOffset = fatOffset + bootSector->NoOfFATs * bootSector->SectorsPerFAT;
    uint16_t dataOffset = rootOffset + bootSector->RootDirEntries * SIZE_ENTRY / sizeSector;

    uint8_t *buff_cluster = (uint8_t *) malloc(bootSector->SectorsPerFAT*sizeSector* sizeof(uint8_t));

    kmc_read_multi_sector(fatOffset, bootSector->SectorsPerFAT, buff_cluster);

    uint8_t *buff_file = (uint8_t *) malloc(sizeSector);

    if (buff_file == NULL)
    {
        printf("Not enough memory for reading file.\n");
    }
    else
    {
        while (cluster > OFFSET_CLUSTER && cluster < END_CLUSTER)
        {
            /* calculate sector offset in Data Region based on cluster in FAT Region */
            sectorOffset = dataOffset + (cluster - OFFSET_CLUSTER);

            /* read a block of data (512) into buff_file, start from sector offset */
            fileSize = fileSize + kmc_read_sector(sectorOffset, buff_file);

            for (i = 0 ; i < sizeSector ; i++)
            {
                /* remove beep sound and trailing space */
                if (*(buff_file+i) != BEEP_SOUND && *(buff_file+i) != TRAILING_SPACE)
                {
                    printf("%c", *(buff_file+i));
                }
            }

            /* read next cluster from FAT table */
            cluster = FAT_readNextCluster(bootSector, cluster, buff_cluster);

            /* reallocate buff_file */
            realloc(buff_file, sizeSector);
        } 

        printf("\nFile Size = %d (bytes)", fileSize);

        printf("\n");
        SEPARATE_LINE();
    }
}

uint16_t FAT_readFolder(FAT12BootSector_t *bootSector, uint16_t cluster, uint32_t firstClusterID[], uint32_t attributes[])
{

    uint32_t offset;
    uint16_t i;
    uint16_t j;
    uint16_t fFolderCount=0;

    /* extract some offset information for later usage */
    uint16_t sizeSector = bootSector->BytesPerSector;
    uint16_t fatOffset = bootSector->NoOfReservedSectors;
    uint16_t rootOffset = fatOffset + bootSector->NoOfFATs * bootSector->SectorsPerFAT;
    uint16_t dataOffset = rootOffset + bootSector->RootDirEntries * SIZE_ENTRY / sizeSector;

    uint8_t * buff_folder = (uint8_t *)malloc(sizeSector);

    if (buff_folder == NULL)
    {
        printf("Not enough memory for reading folder.\n");
    }
    else
    {
        /* offset of cluster which we need to access in data region.
         * It is minus 2 because the first two sectors in data region are unused.
         */
        offset = dataOffset + (cluster - OFFSET_CLUSTER);

        kmc_read_sector(offset, buff_folder);

        FAT12DirEntry_t *dirEntry = (FAT12DirEntry_t *) buff_folder;

        printf("Directory Data        :\n");
        printf("ID\tName\tExt\tCluster\tType\tSize\tModTime\t\tModDate\n");

        for(i = 0; i < sizeSector; i += SIZE_ENTRY)
        {
            /* check file name is valid or not */
            if ((dirEntry->FileName[0] == DIR_ENTRY_FREE1) || (dirEntry->FileName[0] == DIR_ENTRY_FREE2))
            {
                break;
            }
            /* check whether long file name (LFN) or not? If not, then print out file/folders in root */
            if (dirEntry->Attributes != ATTR_LFN)
            {
                fFolderCount++;
                printf("%d\t", fFolderCount);
                printf("%.8s", dirEntry->FileName);
                printf("%.3s\t", dirEntry->Extension);
                printf("%d\t", dirEntry->FirstLogicalCluster);
                firstClusterID[fFolderCount]= dirEntry->FirstLogicalCluster;
                attributes[fFolderCount] = dirEntry->Attributes;
                switch (dirEntry->Attributes)
                {
                    case ATTR_READ_ONLY :
                        printf("ReadOnly\t");
                        break;
                    case ATTR_HIDDEN :
                        printf("Hidden\t");
                        break;
                    case ATTR_SUB_DIRECTORY :
                        printf("Folder\t");
                        break;
                    case ATTR_ARCHIVE :
                        printf("Archive\t");
                        break;
                    default :
                        printf("File\t");
                }
                printf("%d\t", dirEntry->FileSizeBytes);
                FAT_timeExtract(dirEntry->LastWriteTime);
                FAT_dateExtract(dirEntry->LastWriteDate);
            }
            /* increase pointer to point to the next dir Entry */
            dirEntry++;
        }
        SEPARATE_LINE();
        return fFolderCount;
    }
    free(buff_folder);
}

/*******************************************************************************
 * Code: FAT LIB SUPPORT FUNCTIONS (STATIC)
 *  timeExtract
 *  dateExtract
 ******************************************************************************/
static void FAT_timeExtract(uint16_t time)
{
    /* sec: 5 bits lsb, shift left << 1 because 2-second resolution (fatgen103.doc, page 25) */
    uint8_t seconds = (0b0000000000011111 & time) << 1;

    /* min: 6 bits next, shift 5 bits to right (hour takes 5 bit-space) */
    uint8_t minutes = (0b0000011111100000 & time) >> 5;

    /* hr: 5 bits msb, shift 11 bits to right (hour and min takes 11 bit-space) */
    uint8_t hours = (0b1111100000000000 & time) >> 11;

    /* display AM or PM according to hour */
    if (hours > 12)
    {
        hours = hours - 12;
        printf("%02d:%02d:%02d PM\t", hours, minutes, seconds);
    }
    else
    {
        printf("%02d:%02d:%02d AM\t", hours, minutes, seconds);
    }
}

static void FAT_dateExtract(uint16_t date)
{
    /* days: 5 bits lsb */
    uint8_t days = (0b0000000000011111 & date);

    /* months: 4 bits next */
    uint8_t months = (0b0000000111100000 & date) >> 5;

    /* years: 7 bits msb */
    uint16_t years = ((0b1111111000000000 & date) >> 9) + 1980;

    printf("%02d/%02d/%04d\n", days, months, years);
}
