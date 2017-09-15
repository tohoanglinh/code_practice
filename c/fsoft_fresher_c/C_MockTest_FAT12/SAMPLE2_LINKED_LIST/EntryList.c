#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "HAL.h"
#include "EntryList.h"

int insertFirst(node_t **head, directory_t input_data, int idx)
{
    if (NULL == head)
    {
        return EXIT_FAILURE;
    }
    node_t *node = (node_t*) malloc(sizeof(node_t));
    node->data = input_data;
    node->index = idx;

    /* point it to old first node */
    node->next = *head;

    /* point first to new first node */
    *head = node;
    
    return EXIT_SUCCESS;
}

int length(const node_t *head)
{
    if (NULL == head)
    {
        return EXIT_FAILURE;
    }
    int length = 0;
    node_t *current;

    for(current = head; current != NULL; current = current->next)
    {
        length++;
    }
    
    return length;
}

uint16_t searchClust(node_t *head, int index)
{
    if (NULL == head)
    {
        return EXIT_FAILURE;
    }
    
    node_t *current;
    uint16_t result = 0;

    for(current = head; current != NULL; current = current->next)
    {
        if(current->index == index){
            result = current->data.firstCluster;
        }
    }
    
    return result;
}

bool isFolder(node_t *head, node_t *node){
    if (NULL == head || NULL == node)
    {
        return EXIT_FAILURE;
    }    
    
    if ((node->data.attribute & ATTR_DIRECTORY) == ATTR_DIRECTORY){
        return true;
    }
    
    return false;
}

node_t *searchIdx(node_t *head, int index){
        
    if (NULL == head)
    {
        return NULL;
    }
    
    node_t *current;
    node_t *result = NULL;
    
    for(current = head; current != NULL; current = current->next)
    {
        if(current->index == index){
            result = current;
        }
    }    
    
    return result;
}

int freeList(node_t **head)
{    
    node_t *current;

    /* check if input parameter is invalid or not */
    if (NULL == *head)
    {
        return EXIT_FAILURE;
    }

    /* iterate over the list, node by node */
    while(*head != NULL)
    {
        /* make pCurrent point to head of list */
        current = *head;
        /* set node behind head of list as new head of list */
        *head = (*head)->next;

        /* free node pointed by pCurrent */
        free(current);
    }
    // *head = NULL;

    return EXIT_SUCCESS;
}

int printNode(const node_t *node)
{
    /* check if input parameter is invalid or not */
    if ((NULL == node))
    {
        return EXIT_FAILURE;
    }

    /* print fresher's info out */
    printf("\nFile Name: %s", node->data.fileName);
    printf("\nfirst cluster: %d", node->data.firstCluster);
    printf("\nindex: %d", node->index);
    printf("\n");

    return EXIT_SUCCESS;
}

int printList(const node_t *head)
{
    node_t *current;
        
    /* check if input parameter is invalid or not */
    if (NULL == head)
    {
        printf("\n\nList is empty!");
        return EXIT_SUCCESS;
    }
    else{
        printf("\nLength of list: %d", length(head));
    }

    /* if list is not empty, iterate over the list by using pCurrent pointer,
    start from head of list */
    current = head;
    while(NULL != current)
    {
        /* print fresher's info out */
        printNode(current);
        /* make pCurrent point to the next node */
        current = current->next;
    }

    return EXIT_SUCCESS;
}

int readDir(directory_t *rdir, node_t **head, uint16_t startCluster, bool isSubDir){
    
    int i;
    int j = 0;
    int numFile = 0;
        
    if(NULL == rdir || NULL == head){
        return EXIT_FAILURE;
    }
    
    while(1){    
        
        if(!isSubDir){
            fseek(fp,NUM_SECT_TO_ROOT * sectorLength + BYTE_OF_DIR * j,SEEK_SET);           
        }
        else{
            fseek(fp,sectorLength * BYTE_OF_DIR + sectorLength * (startCluster - 1) + BYTE_OF_DIR + BYTE_OF_DIR * (j + 1),SEEK_SET);
        }
        
        fread(rdir -> fileName,sizeof(uint8_t),SIZE_FILE_NAME,fp);
        if((rdir -> fileName)[0] == 0x00){
            break;
        }

        fread(rdir -> extend,sizeof(uint8_t),SIZE_EXTEND,fp);
        fread(&(rdir -> attribute),sizeof(uint8_t),SIZE_ATTRIBUTE,fp);
        fread(rdir -> properties,sizeof(uint8_t),SIZE_PROPERTIES,fp);
        fread(&(rdir -> firstCluster),sizeof(uint8_t),SIZE_FIRST_CLUST,fp);                
        fread(&(rdir -> fileSize),sizeof(uint8_t),SIZE_FILE_SIZE,fp);
        
        if(((rdir -> attribute) & ATTR_HIDDEN) != ATTR_HIDDEN){    
            
            numFile++;
            insertFirst(head, *rdir, numFile);
            if(((rdir -> attribute) & ATTR_DIRECTORY) != ATTR_DIRECTORY){                                
                printf("\n%d. %s\t\t%d\t\t%d byte\t\tFile", numFile, rdir -> fileName,rdir -> firstCluster,rdir -> fileSize);                                
            }
            else{
                printf("\n%d. %s\t\t%d\t\t%d byte\t\tFolder", numFile, rdir -> fileName,rdir -> firstCluster,rdir -> fileSize);                    
            }
        }                
        j++;            
    }    
    return EXIT_SUCCESS;
}

int requestHandle(directory_t *rdir, node_t **head, uint16_t startCluster, bool isSubDir){
    
    if(NULL == rdir || NULL == head){
        return EXIT_FAILURE;
    }
    
    int choice;
    int i = 0;
    int level = 0;
    int lengthList;

    readDir(rdir, head, startCluster, isSubDir);
    lengthList = length(*head);
    printf("\n---------------------------------------------------------------------------");
    printf("\n\nWhich index of file that you want to display?");
    printf("\n(0 -> %d; 0 to back root directory)?: ", lengthList);
    scanf("%d",&choice);    
    
    if((choice > 0 || choice == 0) && (choice < lengthList + 1)){
        uint16_t fc = searchClust(*head, choice);
        
        if (choice == 0){
            freeList(head);        
            requestHandle(rdir, head, fc, false);
        }
        
        if(isFolder(*head, searchIdx(*head, choice))){        
            freeList(head);
            requestHandle(rdir, head, fc, true);
        }
        else{
            readFile(searchClust(*head, choice));
        }
    }
    return EXIT_SUCCESS;
}
