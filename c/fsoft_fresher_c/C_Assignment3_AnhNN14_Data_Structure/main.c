/*******************************************************************************
 * Dev: @linhth8
 * Mentor: @anhnn14
 * Topic: Linked List - Data Structure
 * Main: Student List Management in a Class.
 * FUNCTIONS:
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

/* Declare and initialize pointer head and current position for link list */
struct student *head = NULL;
struct student *current = NULL;

/* Main code */
uint8_t main(void)
{
	/* local variables declaration in main */
	char option;
	char yesno;
	char tmpName[MAX_NAME_LENGTH];
	struct student *foundStudent;
	
	/* request an user to choose an option */
    printf("Student Management in Class\n");
	printf("Enter option: 1(Add), 2(Remove), 3(Print), q(Quit).\n");
    
    do
    {
    /* waiting for option entered from keyboard by user */
    scanf(" %c", &option);
	    if (option == '1')
	    {
	    	/* add student */
	    	studentAddData("To Hoang Linh");
	    	studentAddData("Nguyen Van A");
	    	studentAddData("Nguyen Van B");
	    	studentAddData("Trinh Van C");
	    	printf("Enter option: 1(Add), 2(Remove), 3(Print), q(Quit).\n");
		}
		if (option == '2')
	    {
	    	/* enter name to remove */
	    	printf("Enter name to remove: ");
	    	scanf(" %[^\n]%*c", tmpName);
	    	/* check if that name exists or not in the list */
	    	foundStudent = studentFindName(tmpName);
			    if (foundStudent != NULL)
				{
					printf("Student %s exists. Remove (y/n)?", tmpName);
					/* are you really sure to remove */
					scanf(" %c", &yesno);
					if (yesno == 'y')
					{
						/* removing ... */
						studentRemoveName(tmpName);
					}
				}
				else
				{
					/* that student is non-exist in the current list */
					printf("Student %s non-exists.\n", tmpName);
				}	    	
	    	printf("Enter option: 1(Add), 2(Remove), 3(Print), q(Quit).\n");
		}
		if (option == '3')
	    {
	    	system("cls");
	    	/* print student list */
	    	studentPrintList();
	    	printf("Enter option: 1(Add), 2(Remove), 3(Print), q(Quit).\n");
		}	
	} while (option != 'q');

	/* free memory that is occupied and pointed by pointer current and head */
	free(current);
	free(head);

    return(0);
}
