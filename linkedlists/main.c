/*
	Name: main.c
	Copyright:
	Author: ToHoangLinh
	Date: 25/08/17 09:24
	Description: main program to test linked lists
*/
#include "linkedlists.h"

int main(void)
{
    node_t *head0   = NULL;

    /* init list0 */
    head0 = malloc(sizeof(node_t));
    head0->data = 1;
    head0->next = malloc(sizeof(node_t));
    head0->next->data = 2;
    head0->next->next = malloc(sizeof(node_t));
    head0->next->next->data = 3;
    head0->next->next->next = NULL;

    /* test empty and print */
    if (true == LL_isListEmpty(head0))
    {
        printf("Init List is empty\n");
    }
    else
    {
        printf("Init List is not empty\n");
        LL_printList(head0);
    }

    /* test push */
    LL_pushItemBegin(&head0, 0);
    LL_pushItemEnd(head0, 4);
    printf("New List is\n");
    LL_printList(head0);
    
    /* test remove */
    
    return 0;
}
