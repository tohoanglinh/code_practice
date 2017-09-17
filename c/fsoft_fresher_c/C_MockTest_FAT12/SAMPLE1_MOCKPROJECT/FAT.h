#ifndef _FAT_H_
#define _FAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SIZE_SECTOR 512

#pragma pack(push, 1)
unsigned char *buff_Data;
unsigned char *buff;
typedef struct
{
    unsigned char filename[8];
    unsigned char ext[3];
    unsigned char attributes;
    unsigned char reserved;
    unsigned char CreateTime_fine;
    unsigned short CreateTime_hms;
    unsigned short CreateTime_ymd;
    unsigned short AccessTime_ymd;
    unsigned short EAIndex;
    unsigned short modify_time;
    unsigned short modify_date;
    unsigned short starting_cluster;
    unsigned long file_size;
} Fat12Entry;

typedef struct
{
    uint8_t jmp[3];
    char    oem[8];
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
    char volume_label[11];
    char fs_type[8];
    uint8_t boot_code[448];
    uint16_t boot_sector_signature;
} Fat12BootSector;
FILE *file;
/* 
 *doc foder o vi tri firstCluster 
 */
void read_foder(uint32_t firstCluster);
/* 
 *doc file trong thu muc con o vi tri firstCluster 
 */
void read_file(int firstCluster);
/* 
 *doc boot sector
 */
int read_boot_sector(unsigned int *fat_offset, unsigned int *rootdir_offset, unsigned int *data_offset, unsigned int *size_sectors);
/* 
 *tim vi tri claster tiep theo trong file
 */
unsigned short readNextCluster(int fat_offset, int cluster, int size_sector);
/* 
 *in ra chuoi buf voi kich thuoc la size
 */
void print_str (char *buf, int size);
/* 
 *hien thi file doc duoc
  cluster : vi tri firstCluster cua file can doc
 */
void Display(int cluster);
/* 
 *viet command line
 */
void command (void);
#pragma pack(pop)
#endif

