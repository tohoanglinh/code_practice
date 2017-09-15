/*******************************************************************************
 * Dev: @linhth8
 * Mentor: @anhnn14
 * Topic: Linked List - Data Structure
 * LINKED LIST FUNCTIONS:
 * 		studentAddData(name)
 *		studentRemoveName(name)
 *		studentPrintList()
 *		studentFindName(name)
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "header.h"

extern struct student *head;		/* external pointer head from other source *.c (main.c) */
extern struct student *current;		/* external pointer current from other source *.c (main.c) */

/*-------------------------------------------------------------------------------*/
/*!
 * @brief Add data(name) of student
 *
 * @param name[] a string as name from user keyboard.
 *
 * @return void.
 */
void studentAddData(char name[])
{
   /*create a link*/
   struct student *link = (struct student*) malloc(sizeof(struct student));

   /*insert data into that link*/
   strcpy(link->name,name);

   /*point that link to first previous node cu*/
   link->next = head;

   /*point first to first next (new) node*/
   head = link;
}
/*-------------------------------------------------------------------------------*/
/*!
 * @brief Print student list
 *
 * @param void.
 *
 * @return void.
 */
void studentPrintList(void)
{
   struct student *ptr = head;

   printf("Current student list is:\n");
   /*start from beginning of list*/
   while(ptr != NULL)
   {
      printf("%s          \n", ptr->name);
      ptr = ptr->next;
   }
}
/*-------------------------------------------------------------------------------*/
/*!
 * @brief Find a student with known name
 *
 * @param name[] name string from input keyboard.
 *
 * @return NULL if no student has that name,
 * @return !NULL if exists student with that name.
 */
struct student* studentFindName(char name[])
{
   /* Start searching from first student */
   struct student* current = head;

   /* if list is empty */
   if(head == NULL)
   {
      return NULL;
   }

   /* student list browsing */
   /* compare current(name) with name entered from keyboard
    * if different --> check if here is the last node (student) -->(Y) --> NULL
    * if different --> .........................................-->(N) --> move to the next node (student)
    * until string compare is satisfied (found student with that name)
	*/   
   while(strcmp(current->name, name)!=0)
   {
      /* if this is the last student */
      if(current->next == NULL)
	  {
         return NULL;
      }
	  else 
	  {
         /* move to next student */
         current = current->next;
      }
   }

   /* if found, then return the current student */
   return current;
}
/*-------------------------------------------------------------------------------*/
/*!
 * @brief Remove a student with known name
 *
 * @param name[] name string from input keyboard.
 *
 * @return NULL if no student has that name,
 * @return !NULL if exists student with that name.
 */
struct student* studentRemoveName(char name[])
{
   /* start from first student */
   struct student *current = head;
   struct student *previous = NULL;

   /* check if list is empty */
   if(head == NULL)
   {
      return NULL;
   }

   /* student list browsing */
   /* compare current(name) with name entered from keyboard
    * if different --> check if here is the last node (student) -->(Y) --> NULL
    * if different --> .........................................-->(N) --> move to the next node (student)
    * until string compare is satisfied (found student with that name)
	*/
   while(strcmp(current->name, name)!=0)
   {
      /* if here is the last student */
      if(current->next == NULL)
	  {
         return NULL;
      }
	  else 
	  {
         /* save the current student to temporarily previous student*/
         previous = current;
         /* move to next student*/
         current = current->next;
      }
   }

   /* update pointer of student */
   if(current == head) 
   {
      /* change head (first) point to next student*/
      head = head->next;
   }
   else 
   {
      /* skip the current student (current is the removed), move to next */
      previous->next = current->next;
   }

   return current;
}
