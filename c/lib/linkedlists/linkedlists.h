#ifndef LINKEDLISTS_H
#define LINKEDLISTS_H

/*******************************************
 * INCLUDES
 *******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************************************
 * STRUCTS
 *******************************************/
typedef struct node
{
    int data;
    struct node * next;
} node_t;

/*******************************************
 * DEFINES
 *******************************************/

/*******************************************
 * GLOBAL VARIABLES
 *******************************************/

/*******************************************
 * APIS
 *******************************************/
/* add item to end of list */
void LL_pushItemEnd(node_t * head, int item_data);

/* add item to begin of list */
void LL_pushItemBegin(node_t ** head, int item_data);

/* remove item */

/* print list */
void LL_printList(node_t * head);

/* check emptiness of list */
bool LL_isListEmpty(node_t * head);

#endif /* LINKEDLISTS_H */

