#include <stdio.h>
#include <string.h>
#include "HAL_Read_Write_Sector.h"
#include "FAT.h"
/*
 *doc foder o vi tri firstCluster
 */
void read_foder(uint32_t firstCluster)
{
    uint32_t offset;
    int i;
    buff_Data = (char *)malloc(512);
    int cluster = firstCluster;
    offset = 33 + (cluster - 2);  /* offset cua cluster can lan du lieu trong vung Data */
    int data_size = kmc_read_sector(offset, buff_Data);
    Fat12Entry *entry = (Fat12Entry *) buff_Data;
    printf("Folder o firstCluster %d: \n", cluster);

    for(i = 0; i < 512; i += 32)
    {
        if (entry->filename[0] == 0x00)
            break;
        if (entry->attributes != 0xF)
        {
            for(i = 0; i < strlen(entry->filename); i++)
            {
                printf("%c", entry->filename[i]);
            }
            printf("   A: %02X First Cluster: %d  Size: %04X\n", entry->attributes, entry->starting_cluster, entry->file_size);
            printf("\n");
        }
        entry++;
    }
    free(buff_Data);
}
/*
 *doc file trong thu muc con o vi tri firstCluster
 */
void read_file(int firstCluster)
{
    char *a;
    int data_value;
    data_value = kmc_read_sector(firstCluster, buff);
    a = (char*) buff;

    printf("du lieu file :  %s", a);
    printf("\nsize of file : %d\n", data_value);

}
/* 
 *doc boot sector
 */
int read_boot_sector(unsigned int *fat_offset, unsigned int *rootdir_offset, unsigned int *data_offset, unsigned int *size_sectors)
{
    char *buff = (char *) malloc(SIZE_SECTOR);
    if(buff == NULL)
    {
        return -1;
    }
    else
    {
        kmc_read_sector(0, buff);
        Fat12BootSector *boot = (Fat12BootSector *)buff;
        *fat_offset = boot -> reserved_sectors;
        *rootdir_offset = *fat_offset + (boot -> number_of_fats * boot -> fat_size_sectors);
        *data_offset = *rootdir_offset + (boot -> root_dir_entries * 32) / boot -> sector_size;
        *size_sectors = boot -> sector_size;
    }
    free(buff);
    return 0;
}
/* 
 *tim vi tri claster tiep theo trong file
 */
unsigned short readNextCluster(int fat_offset, int cluster, int size_sector)
{
    unsigned int index = 0, entry_offset = 0;
    index = (cluster + (cluster /2)) / size_sector;   
    entry_offset =  (cluster + (cluster /2)) % size_sector;  
    unsigned short next_cluster;      
    unsigned char *buff = (unsigned char *)malloc(size_sector); 
    if(buff == NULL)
    {
        return -1;
    }
    else
    {
        fat_offset += index;
        kmc_read_sector(fat_offset, buff);
        if(cluster % 2 == 0)
        {
            next_cluster = *(buff + entry_offset) | ((*(buff + entry_offset + 1) & 0x0F) << 8);
        }
        else
        {
            next_cluster = (buff[entry_offset] >> 4) | (buff[entry_offset + 1] << 4);
        }
        free(buff);
    }
    return next_cluster;
}
void print_str (char *buf, int size)
{
    int i;
    for (i=0; i!=size; i++) printf ("%c", *buf++);
}
/* 
 *hien thi file doc duoc
 *cluster : vi tri firstCluster cua file can doc
 */
void Display(int cluster)
{
    unsigned int fat_offset, rootdir_offset, data_offset, size_sectors;
    read_boot_sector( &fat_offset, &rootdir_offset, &data_offset, &size_sectors);
    char *buff = (char *) malloc(size_sectors);
    int offset;
    do
    {
        offset = data_offset + (cluster - 2);
        kmc_read_sector(offset, buff);
        print_str (buff, size_sectors);
        cluster = readNextCluster(fat_offset, cluster, size_sectors);
    }
    while(cluster > 0x002 && cluster <= 0xFF7);
    free(buff);
}
void command (void)
{

}


