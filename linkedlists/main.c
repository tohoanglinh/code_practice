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

    /* list0 */
    head0 = malloc(sizeof(node_t));
    head0->data = 1;
    head0->next = malloc(sizeof(node_t));
    head0->next->data = 2;
    head0->next->next = malloc(sizeof(node_t));
    head0->next->next->data = 3;
    head0->next->next->next = NULL;

    if (true == LL_isListEmpty(head0))
    {
        printf("List is empty\n");
    }
    else
    {
        printf("List is not empty\n");
        LL_printList(head0);
    }

    return 0;
}
