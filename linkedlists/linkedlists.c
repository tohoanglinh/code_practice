/*
    Name: linkedlists.c
    Copyright:
    Author: ToHoangLinh
    Date: 25/08/17 09:26
    Description: Linked lists is an array, but can grow and shrink as needed
    from any point in the array [Array is fixed size, can't add or remove].

Advantages over arrays:
   1. Can add or remove items from the middle of the list
   2. No need to define an initial size
Disadvantages:
   1. no "random" access. To access nth item, we have to iterate from the
   beginning to nth item.
   2. require pointers, dynamic memory allocation --> complicates the code
   and increases the risk of memory leaks and segmentation faults.
   3. linked lists have a much larger overhead over arrays (because: *items
   are dynamically allocated, and *each item must store an additional pointer)
   --> less efficient in memory usage.
*/
#include "linkedlists.h"

void LL_printList(node_t * head)
{
    node_t * current = head;
    
    while (current != NULL)
    {
        printf("%d\n", current->data);
        current = current->next;
    }
}

bool LL_isListEmpty(node_t * head)
{
    return (head == NULL);
}