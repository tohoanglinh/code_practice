#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#define CONVERT_32(x)             ((x >> 24)|(x << 24)|((x >> 8) & 0xff00)|((x << 8) & 0xff0000))
#define CONVERT_16(x)             ((x >> 8)|(x << 8))

#define SIZE_JUMP                 (3)
#define SIZE_OEM_NAME             (8)
#define SIZE_BYTE_PER_SEC         (2)
#define SIZE_SECT_PER_CLUST       (1)
#define SIZE_RESERVE_SECT         (2)
#define SIZE_FATS                 (1)
#define SIZE_ROOT_DIR_ENTR        (2)
#define SIZE_LOGICAL_SECT         (2)
#define SIZE_MED_DESCRIPT_BYTE    (1)
#define SIZE_SECT_PER_FAT         (2)
#define SIZE_SECT_PER_TRACK       (2)
#define SIZE_HEAD                 (2)
#define SIZE_HIDDEN_SECT          (4)
#define SIZE_CODE                 (478)
#define SIZE_MARKER               (2)

typedef struct BootSector {
    uint8_t        jump [SIZE_JUMP];
    uint8_t        name [SIZE_OEM_NAME];
    uint16_t       bytePerSector;
    uint8_t        sectorsPerCluster;
    uint16_t       reservedSectors;
    uint8_t        fats;
    uint16_t       rootDirectoryEntries;
    uint16_t       logicalSectors;
    uint8_t        mediumDescriptorByte;
    uint16_t       sectorsPerFat;
    uint16_t       sectorsPerTrack;
    uint16_t       heads;
    uint8_t        hiddenSectors [SIZE_HIDDEN_SECT];    
    uint8_t        code [SIZE_CODE];
    uint16_t       marker;
}boot_t;

uint16_t fatMapping(uint16_t firstCluster);
void printBootSector(boot_t *bootsect);
void readBootSector(boot_t *bootsect);
int readFile(uint16_t firstCluster);

#endif /* _FUNCTION_H_ */
