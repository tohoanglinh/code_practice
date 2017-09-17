/*******************************************************************************
 * @dev: LinhTH8 [FR_EMB_HN17_01]
 * @men: MinhNQ2
 * @tit: MockTest1 FAT12
 * @dat: 25/1 - 9/2
 * @file: FAT.h
 * FAT Header Library
 ******************************************************************************/

#ifndef _FAT_H_
#define _FAT_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CLUSTER_ROOT 0
#define MAX_ENTRIES 224

/*define for boot sector struct*/
#define BOOTSECTOR_INDEX 0
#define SIZE_JMP 3
#define SIZE_OEM 8
#define SIZE_VOL_LABEL 11
#define SIZE_FILE_SYS 8
#define SIZE_BOOT_REST 0x1C0

/*define for directory entry struct*/
#define SIZE_FILE_NAME 8
#define SIZE_EXTENSION 3
#define DIR_ENTRY_FREE1 0x00
#define DIR_ENTRY_FREE2 0xE5

#define ATTR_READ_ONLY 0x01
#define ATTR_HIDDEN 0x02
#define ATTR_SYSTEM 0x04
#define ATTR_VOLUME_LABEL 0x08
#define ATTR_SUB_DIRECTORY 0x10
#define ATTR_ARCHIVE 0x20
#define ATTR_FILE 0x00
#define ATTR_LFN 0x0F

/*size of directory entry in bytes*/
#define SIZE_ENTRY 32

#define OFFSET_CLUSTER 0x002
#define END_CLUSTER 0xFFF

#define BEEP_SOUND 7
#define TRAILING_SPACE 0

#define SEPARATE_LINE() printf("----------------------------------------------------------------------------\n")

/*******************************************************************************
 * These structs are derived from FAT12Description.pdf
 ******************************************************************************/
#pragma pack(push, 1)

typedef struct
{
    uint8_t jmpBoot[SIZE_JMP];
    uint8_t OEMName[SIZE_OEM];
    uint16_t BytesPerSector;
    uint8_t SectorsPerCluster;
    uint16_t NoOfReservedSectors;
    uint8_t NoOfFATs;
    uint16_t RootDirEntries;
    uint16_t TotalSectorCount12;
    uint8_t Ignore1;
    uint16_t SectorsPerFAT;
    uint16_t SectorsPerTrack;
    uint16_t NoOfHeads;
    uint32_t Ignore2;
    uint32_t TotalSectorCount32;
    uint16_t Ignore3;
    uint8_t ExtendedBootSignature;
    uint32_t VolumeID;
    uint8_t VolumeLabel[SIZE_VOL_LABEL];
    uint8_t FileSystemType[SIZE_FILE_SYS];
    uint8_t Ignore4[SIZE_BOOT_REST];
    uint16_t BootSectorSignature;
} FAT12BootSector_t;

typedef struct
{
    uint8_t FileName[SIZE_FILE_NAME];
    uint8_t Extension[SIZE_EXTENSION];
    uint8_t Attributes;
    uint8_t Reserved;
    uint8_t CreationTimeMilSec;
    uint16_t CreationTime;
    uint16_t CreationDate;
    uint16_t LastAccessDate;
    uint16_t IgnoreInFAT12;
    uint16_t LastWriteTime;
    uint16_t LastWriteDate;
    uint16_t FirstLogicalCluster;
    uint32_t FileSizeBytes;
} FAT12DirEntry_t;

#pragma pack(pop)
/*******************************************************************************
 * APIs
 ******************************************************************************/
/*!
 * @brief Read bootsector data
 *
 * @param null
 *
 * @return a bootsector struct.
 */
FAT12BootSector_t *FAT_readBootSector(void);

/*!
 * @brief Print bootsector data
 *
 * @param bootsector struct
 *
 * @return display bootsector on screen.
 */
void FAT_printBootSector (FAT12BootSector_t *bootSector);

/*!
 * @brief Read FAT table for next cluster
 *
 * @param *bootSector
 * @param cluster:   previous cluster
 * @param *buff_cluster: store FAT table to look up next cluster value
 *
 * @return next cluster (address).
 */
uint16_t FAT_readFatNextCluster(FAT12BootSector_t *bootSector, uint16_t cluster,uint8_t *buff_cluster);

/*!
 * @brief Read Root Directory
 *
 * @param *bootSector.
 *
 * @return a dirEntry struct.
 */
FAT12DirEntry_t *FAT_readRootDir(FAT12BootSector_t *bootSector);

/*!
 * @brief Print Root Directory
 *
 * @param *dirEntry
 * @param *bootSector
 * @param firstClusterID[] array for storing ID, user can choose to enter
 * @param attributes[] array for storing attributes, to identify folder or file later
 *
 * @return Display root file/folder.
 */
uint16_t FAT_printRootDir(FAT12DirEntry_t *dirEntry, FAT12BootSector_t *bootSector, uint32_t firstClusterID[], uint32_t attributes[]);

/*!
 * @brief Read File Content at cluster
 *
 * @param *bootSector.
 * @param cluster.
 *
 * @return Display File Content.
 */
void FAT_readFile(FAT12BootSector_t *bootSector, uint16_t cluster);

/*!
 * @brief Read Folder (except root) at cluster
 *
 * @param *bootSector.
 * @param cluster.
 *
 * @return Display Folder Content (List of files and subfolders).
 */
uint16_t FAT_readFolder(FAT12BootSector_t *bootSector, uint16_t cluster, uint32_t firstClusterID[], uint32_t attributes[]);

/*!
 * @brief Extract time information from dirEntry
 *
 * @param time
 *
 * @return Time format (00:00:10).
 */
static void FAT_timeExtract(uint16_t time);

/*!
 * @brief Extract date information from dirEntry
 *
 * @param date.
 *
 * @return Date format (1/1/2008).
 */
static void FAT_dateExtract(uint16_t date);

#endif /* _FAT_H_ */
