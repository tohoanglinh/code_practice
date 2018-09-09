/*******************************************************************************
 * @dev: LinhTH8 [FR_EMB_HN17_01]
 * @men: MinhNQ2
 * @tit: MockTest1 FAT12
 * @dat: 25/1 - 9/2
 * @file: main.c
     * Main Requirements:
     * [1]. Display all files/folders in root
     * [2]. Enter folder (ID) --> display subdirs and files inside
     * [3]. Enter file (ID) --> display content of that file
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include "FAT.h"
#include "HAL.h"
#include "config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ID_QUIT 0

#define CMD() printf("Enter ID (0 quit) (. current) (.. previous) (%d root): ", entryCount+1)

/*******************************************************************************
 * Main
 ******************************************************************************/
int main(void)
{
    /*================================================================================*/
    g_filepath = malloc(sizeof(char)*100);

    /* Temp array to store: ID, Attributes */
    uint32_t firstClusterID[MAX_ENTRIES];
    uint32_t attributes[MAX_ENTRIES];

    /* Count/Temp var */
    uint16_t id;
    uint16_t entryCount;

    /* Struct var */
    FAT12BootSector_t *bootSector;
    FAT12DirEntry_t *dirEntry;
    /*================================================================================*/
    printf("****************************************************************************\n");
    printf("MOCK TEST 1 - FAT12.\n");
    printf("Please enter full path to img file:");
    scanf("%s", g_filepath);
    printf("Parsing file path: %s\n", g_filepath);
    SEPARATE_LINE();
    /*================================================================================*/
    /* read boot sector information */
    bootSector = FAT_readBootSector();

    FAT_printBootSector(bootSector);

    /*================================================================================*/
    /* read root dir information */
    /* task 1: display all files/folders in root */
    dirEntry = FAT_readRootDir(bootSector);

    entryCount = FAT_printRootDir(dirEntry, bootSector, firstClusterID, attributes);

    /*================================================================================*/
    /* file/folder/sub-directories */
    /* task 2: enter file ID --> display content of that file */
    /* task 3: enter folder ID --> display subdir and files in that folder */

    CMD();

    scanf("%" SCNd16, &id);

    /* check id is quit or not */
    while ( id != ID_QUIT )
    {
        /* check id (valid) is less than current number of entries */
        if ( id > ID_QUIT && id <= entryCount )
        {
            /* if id corresponds to root --> list root directory data */
            if (firstClusterID[id] == CLUSTER_ROOT)
            {
                /* read root directory data, save into struct dirEntry */
                dirEntry = FAT_readRootDir(bootSector);

                /* display root directory data, return the current number of entries */
                entryCount = FAT_printRootDir(dirEntry, bootSector, firstClusterID, attributes);

                CMD();
            }
            /* if id does not correspond to root --> list subdirs or files inside */
            else
            {
                /* if id ~ subdir --> readFolder; otherwise --> readFile */
                if (attributes[id] == ATTR_SUB_DIRECTORY)
                {
                    /*read sub-dir based on id*/
                    entryCount = FAT_readFolder(bootSector, firstClusterID[id], firstClusterID, attributes);

                    CMD();
                }
                else
                {
                    /*read file based on id*/
                    FAT_readFile(bootSector, firstClusterID[id]);

                    CMD();
                }
            }
        }
        else if (id == entryCount + 1)
        {
            /* read root directory data, save into struct dirEntry */
            dirEntry = FAT_readRootDir(bootSector);

            /* display root directory data, return the current number of entries */
            entryCount = FAT_printRootDir(dirEntry, bootSector, firstClusterID, attributes);

            CMD();
        }
        else
        {
            SEPARATE_LINE();
            printf("Invalid ID. Again.\n");
        }
        scanf("%" SCNd16, &id);
    }
    printf("****************************************************************************\n");
    /*================================================================================*/
    free(g_filepath);
    return 0;
}
