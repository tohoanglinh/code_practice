/************************************************
 * @mentor: datbt1
 * @date: 18-Jan-2017
 * @dev: linhth8
 * @FR_EMB_HN17_01
Assignment 6:
Write a program to manage information of fresher
Example information:
- Name: To Hoang Linh
- Account: LINHTH8
- GPA: 9.5
Requirement:
    + use linked list to manage list
    + function to add student
    + function to remove student
    + function to arrange student (GPA)
Requirement:
    + use mm_alloc (instead of malloc)
    +     mm_free (instead of free)
    +     mm_display
for dynamic memory allocation
display memory statistics
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include "header_a6.h"
#include "memory checking\mem_management.h"

struct student *head = NULL;
struct student *current = NULL;
uint8_t noOfFresher = 0;

/* procedure to input name, acc, gpa from user keyboard*/
void FresherInputData() {
    char t_name[50];
    char t_acc[10];
    float t_gpa;

    printf("Name: ");
    scanf (" %[^\n]%*c", t_name);/* space before % is to avoid skipping this string scanf
                                  * http://stackoverflow.com/questions/18721375/my-program-skip-getting-input-data*/
    printf("Acc: ");
    scanf(" %[^\n]%*c", t_acc);

    printf("Gpa: ");
    scanf("%f", &t_gpa);

    FresherAdd(t_name, t_acc, t_gpa);
}

/* main program */
int main() {
    char inputc='0';
    char answer;
    char deletedAcc[10];
    struct student *foundStudent;

    printf("Fresher Embedded Information Management Program.\n");
    printf("------------------------------------------------\n");

    /* YEU CAU:
     * 1. Nhap thong tin sinh vien (i++)
     * 2. Hien thi tat ca thong tin sinh vien da nhap
     * 3. Xoa sinh vien (i)
     * 4. Sap xep list theo GPA
     */

    printScreen;
    do {
        scanf("%c",&inputc);
        if (inputc == '1')
        {
            /* add student */
            FresherInputData();
            printScreen;
        }

        if (inputc == '2')
        {
            /* print student list */
            printf("There is/are %d student(s).\n", noOfFresher);
            FresherPrintList();
            printScreen;
        }

        if (inputc == '3')
        {
            /* remove student */
            printf("Enter account to be deleted: ");
            scanf(" %[^\n]%*c", deletedAcc);
            /* check if acc is available in list or not*/
            foundStudent = FresherFindAcc(deletedAcc);
            if(foundStudent != NULL) {
                printf("Found that student: ");
                printf("(%s,%s,%.1f) ",foundStudent->name,foundStudent->account,foundStudent->gpa);
                printf("\nAre you sure to delete that student? (y/n)");
                scanf(" %c",&answer);
                if (answer == 'y') {
                    FresherDeleteAcc(deletedAcc);
                    /* free memory allocated to the deleted student */
                    mm_free(head);
                }
                /* if answer is different from 'y', just do-nothing, non-deleted */
            } else {
                printf("Cannot found that student in the existing list.\n");
            }
            printScreen;
        }

        if (inputc == '4')
        {
            /* arrange student list (GPA descending order (great --> small)*/
            FresherArrangeList();
            printf("Sorted list:\n");
            FresherPrintList();
            printScreen;
        }

        if (inputc == 'f')
        {
            /* free all memory allocated */
            FresherFreeMemoryList();
            printf("Allocated memory has been free.\n");
            printScreen;
        }

        if (inputc == 'm')
        {
            /* heap memory statistic display */
            mm_display();
            printScreen;
        }
    } while (inputc != 'q');

    /* free all allocated memory */
    FresherFreeMemoryList();

    /* display memory statistics */
    mm_display();

    return(0);
}
