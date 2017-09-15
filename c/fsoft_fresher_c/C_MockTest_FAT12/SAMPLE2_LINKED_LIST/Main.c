#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "HAL.h"
#include "Function.h"
#include "EntryList.h"

int main() {
    boot_t *bootSect;
    directory_t *rdir;
    node_t *head = NULL;
    
    if(fp = fopen("floppy.img","rb")){
        bootSect = (boot_t*)malloc(sizeof(boot_t));
        rdir = (directory_t*)malloc(sizeof(directory_t));
        // kmc_read_sector(0, bootSect);
        readBootSector(bootSect);
        sectorLength = bootSect -> bytePerSector;
        printf("\n**************************BOOT SECTOR INFORMATION***************************\n");
        printBootSector(bootSect);
        printf("\n\n*****************************FILE INFORMATION******************************\n");
        printf("\nFile Name\t\tFirst Cluster\tFile Size\tType");
        printf("\n---------------------------------------------------------------------------\n");
        printf("Gia tri Head: %d\n", head);
        printf("Dia chi Head: %X\n", &head); getchar();
        requestHandle(rdir, &head, ROOT_DIR_OFFSET, false); 

        freeList(&head);        
        free(rdir);
        free(bootSect);        
    }
    if (NULL != fp){
    	fclose(fp);
	}
    return(0);
}
