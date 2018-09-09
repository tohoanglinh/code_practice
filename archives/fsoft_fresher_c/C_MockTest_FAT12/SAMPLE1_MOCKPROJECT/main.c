/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FAT.h"
#include "HAL_Read_Write_Sector.h"
/*******************************************************************************
 * Variables
 ******************************************************************************/
FILE *file;

/*******************************************************************************
 * Codes
 ******************************************************************************/
int main(int argc, char *argv[])
{
    int i;
    char *a;
    Fat12Entry *entry;
    int data_value[3];

    /* cap phat dong buff 512 byte */
    buff = (char *)malloc(512);
    if (buff == NULL)
    {
        printf ("Cannot malloc() buffer\n\n");
        return 1;
    }
    int k = kmc_read_sector(0, buff);
    /*in ra buff*/
    Fat12BootSector *bs = (Fat12BootSector *)buff;
    printf("\n  So byte Fat12BootSector: %d\n", sizeof(Fat12BootSector));
    printf("  Jump code           : %02X:%02X:%02X\n", bs->jmp[0], bs->jmp[1], bs->jmp[2]);
    printf("  OEM code            : [%.8s]\n", bs->oem);
    printf("  sector size         : %d\n", bs->sector_size);
    printf("  sectors per cluster : %d\n", bs->sectors_per_cluster);
    printf("  reserved sectors    : %d\n", bs->reserved_sectors);
    printf("  number of fats      : %d\n", bs->number_of_fats);
    printf("  root dir entries    : %d\n", bs->root_dir_entries);
    printf("  total sectors short : %d\n", bs->total_sectors_short);
    printf("  media descriptor    : 0x%02X\n", bs->media_descriptor);
    printf("  fat size sectors    : %d\n", bs->fat_size_sectors);
    printf("  sectors per track   : %d\n", bs->sectors_per_track);
    printf("  number of heads     : %d\n", bs->number_of_heads);
    printf("  hidden sectors      : %d\n", bs->hidden_sectors);
    printf("  total sectors long  : %d\n", bs->total_sectors_long);
    printf("  drive_number        : 0x%02X\n", bs->drive_number);
    printf("  current_head        : 0x%02X\n", bs->current_head);
    printf("  boot_signature      : 0x%02X\n", bs->boot_signature);
    printf("  volume_id           : 0x%08X\n", bs->volume_id);
    printf("  Volume label        : [%.11s]\n", bs->volume_label);
    printf("  Filesystem type     : [%.8s]\n", bs->fs_type);
    printf("  Boot sector signature: 0x%04X\n", bs->boot_sector_signature);
    printf("\n\nRoot Dir:\n");
    /* Tinh entry de vao rood dir */
    uint32_t entry_offset = (bs->reserved_sectors + (bs->number_of_fats * bs->fat_size_sectors)) * bs->sector_size;
    /*root dir entries * 32 = 7168 */
    buff = (char *)malloc(7168);
    if (buff == NULL)
    {
        printf ("Cannot malloc() buffer\n\n");
        return 1;
    }
    /* Get all value of root dir */
    printf("sector: %d\n", entry_offset/512);
    /*
    moi root dir co 224 entries moi entries co 32 byte
    14 = 224 * 32 / 512 sector
    Doc 14 sector lien tiep, bat dau tu sector thu entry_offset/512, vao mang tro buff, tra ve so byte duoc doc */
    int root_value_size = kmc_read_multi_sector(entry_offset/512, 14, buff);
    printf("Dir Offset: %d\n", entry_offset);           /* in byte o vi tri dau tien cua root dri */
    printf("size of root dir: %d\n", root_value_size);  /* in ra so byte doc dc*/
    
    entry = (Fat12Entry *) buff;
    printf("\n**************************************************** \n");
    printf("*********** DOC THU MUC GOC ************************** \n");
    printf("\n");
    
    for(i = 0; i < bs->root_dir_entries; i++)
    {
        if (entry->filename[0] == 0x00)  
            break;
        if (entry->attributes != 0xF)     /* 0xf: long file name*/
        {
            for(i = 0; i < strlen(entry->filename); i++)
            {
                printf("%c", entry->filename[i]); 
            }
            printf("    A: %02X First Cluster: %d  Size: %04X\n", entry->attributes, entry->starting_cluster, entry->file_size);
            printf("\n");
        }
        entry++;
    }
    printf("\n");
    printf("********************************************************* \n");
    printf("*********** DOC FILE THU MUC GOC ************************* \n");
    printf("\n");
    /*bat dau vung data thi sector = 33 */
    read_file(33);
    read_file(34);
    read_file(35);
    read_file(36);
    printf("\n");
    printf("******************************************************* \n");
    printf("\n");
    printf("*********** DOC FILE THEM VAO *************************** \n");
    printf("\n");
    /*bat dau vung data thi sector = 33 */
    Display(39);
    getch();
    Display(1267);
    printf("\n");
    printf("******************************************************* \n");
    /* doc foder o vi tri firstCluster = 7 <-> foder DOC*/
    printf("*********** DOC THU MUC CON *************************** \n");
    printf("\n");
    read_foder(7);
    printf("\n");
    printf("******************************************************* \n");
    command();
    fclose(file);
    return 0;
}

