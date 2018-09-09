#ifndef _MORK_TEST_H_
#define _MORK_TEST_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*MENU STRUCT*/
#define MAX_ENTRY 512               /*Byte*/

/*MAIN*/
#define FILE_ 1
#define FOLDER_ 0
#define EXIT_CONDITION 0
#define INDEX_BOOT_SECTOR 0
#define SECTOR_SIZE 512             /*Byte*/
#define BOOT_SECTOR_SIZE 1          /*Sector*/

/*FAT_newFat*/
#define MOVE_ONE_BYTE 8             /*Bit*/
#define MOVE_HALF_BYTE 4            /*Bit*/
#define MASK_FAT_1 0x0F
#define MASK_FAT_2 0xF0
#define GROUP_3_BYTE 3              /*Byte*/

/*FAT_readFatChain*/
#define MAX_FATCHAIN_SIZE 512*3     /*Byte*/
#define RESERVED_FAT 2              /*Byte*/
#define FAT_ROOT_BEGIN 0x000
#define FAT_ROOT_END 0xFFF
#define END_FAT 0xFFF

/*FAT_readData*/
#define MAX_CLUSTER_READ_SIZE 512*14

/*FAT_readFolder*/
#define LONG_FILE_NAME_ATTRIBUTE 0x0F
#define LFN_ATTRIBUTE_POSITION 11
#define EMPTY_ENTRY 0x20

/*FAT_findIndex*/
#define DIR_ENTRY_SIZE 32           /*Sector*/

#pragma push
#pragma pack(1)
typedef struct {
    uint8_t jmp[3];
    uint8_t oem[8];
    uint16_t sector_size;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t number_of_fats;
    uint16_t root_dir_entries;
    uint16_t total_sectors_short; // if zero, later field is used
    uint8_t media_descriptor;
    uint16_t fat_size_sectors;
    uint16_t sectors_per_track;
    uint16_t number_of_heads;
    uint32_t hidden_sectors;
    uint32_t total_sectors_long;
    uint8_t drive_number;
    uint8_t current_head;
    uint8_t boot_signature;
    uint32_t volume_id;
    uint8_t volume_label[11];
    uint8_t fs_type[8];
    uint8_t boot_code[448];
    uint16_t boot_sector_signature;
} bootSector_t;
#pragma pop

#pragma push
#pragma pack(1)
typedef struct {
    uint8_t name[8];
    uint8_t extension[3];
    uint8_t attribute;
    uint8_t time[14];
    uint16_t first_cluster_index;
    uint32_t file_size_byte;
} directoryEntry_t;
#pragma pop

#pragma push
#pragma pack(1)
typedef struct {
    uint16_t Element1;
    uint16_t Element2;
} tempFat_t;
#pragma pop
typedef struct {
    uint8_t type[MAX_ENTRY];
    uint32_t index[MAX_ENTRY];
} menu_t;

/*Store index and file type of each folder showed*/
menu_t g_menu;

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief <parse Data to SREC data>
 *
 * @param lineData <array of all data for 1 line SREC data>.
 *
 * @return < SREC_data_t >.
 */
uint16_t *FAT_newFat(uint16_t size,uint8_t *buff);
uint16_t *FAT_readFatChain(uint16_t in,uint16_t *newFat);

uint16_t FAT_readSector(FILE* p_file, uint32_t index, uint8_t *buff);
uint16_t FAT_readMultiSector(FILE* p_file, uint32_t index,uint32_t num, uint8_t *buff);

uint16_t FAT_readBootSector(uint8_t *buff);
uint16_t FAT_findIndex(uint16_t *fatIndex,uint16_t *rootDirIndex,uint16_t *dataRegionIndex,uint16_t *secPerClus,uint8_t *buff);
uint16_t FAT_readData (FILE* p_file,uint16_t *fatChain,uint8_t fileType,uint16_t rootIndex,uint16_t rootSize,uint16_t secPerClus);
uint16_t FAT_readFolder(uint8_t *buff);

#endif /* _Mork_test_H_ */
