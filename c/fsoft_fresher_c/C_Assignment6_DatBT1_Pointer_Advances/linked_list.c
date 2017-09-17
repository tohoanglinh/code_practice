/************************************************
 * @mentor: datbt1
 * @date: 18-Jan-2017
 * @dev: linhth8
 * @FR_EMB_HN17_01
 * File: linked_list.c
 * Description: containt linked list functions
	- FresherAdd(name, account, gpa);
	- FresherPrintList();
	- FresherArrangeList();
	- FresherDeleteAcc(account);
	- FresherFindAcc(account);
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>
#include "header_a6.h"
#include "memory checking\mem_management.h"

extern struct student *head;		/* extern pointer head from main.c */
extern struct student *current;		/* extern pointer current from main.c */
extern uint8_t noOfFresher;

/*!
 * @brief Add a fresher student with three input arguments
 *
 * @param1 char name
 * @param2 char account
 * @param3 float gpa
 *
 * @return void.
 */
void FresherAdd(char name[], char account[], float gpa) {
    /*create a link*/
    struct student *link = (struct student*) mm_alloc(sizeof(struct student), "", 0, 0, 0);

    noOfFresher++;

    /*insert data into that link*/
    strcpy(link->name,name);
    strcpy(link->account,account);
    link->gpa = gpa;

    /*point that link to first previous node cu*/
    link->next = head;

    /*point first to first next (new) node*/
    head = link;
}

/*!
 * @brief Free Memory Allocated for Linked List
 *
 * @param void.
 *
 * @return void.
 */
void FresherFreeMemoryList() {
    struct student* tmp;

    /* start free memory allocated to pointer head*/
    while (head != NULL) {
        /* save pointer head to tmp */
        tmp = head;
        /* move to next node */
        head = head->next;
        /* free memory pointed by tmp (previous head) */
        mm_free(tmp);
    }

}

/*!
 * @brief Return length of record list
 *
 * @param void.
 *
 * @return void.
 */
int FresherLengthList() {
    int length = 0;
    struct student *current;

    for(current = head; current != NULL; current = current->next) {
        length++;
    }

    return length;
}

/*!
 * @brief Arrange list according to GPA (descending, max --> min)
 *		  Compare two consecutive gpa --> swap positions.
 * @param void.
 *
 * @return void.
 */
void FresherArrangeList() {
    int i;
    int j;
    int k;
    char tempName[50];
    char tempAcc[10];
    float tempGpa;
    struct student *current;
    struct student *next;
    int size = FresherLengthList();
    k = size ;

    for ( i = 0 ; i < size - 1 ; i++, k-- ) {
        current = head ;
        next = head->next ;

        for ( j = 1 ; j < k ; j++ ) {
            /* sort in descending order : max --> min */
            if ( current->gpa < next->gpa) {
                /* swap gpa*/
                tempGpa = current->gpa ;
                current->gpa = next->gpa;
                next->gpa = tempGpa ;

                /* swap account*/
                strcpy(tempAcc, current->account);
                strcpy(current->account, next->account);
                strcpy(next->account, tempAcc);

                /* swap name*/
                strcpy(tempName, current->name);
                strcpy(current->name, next->name);
                strcpy(next->name, tempName);
            }
            current = current->next;
            next = next->next;
        }
    }
}
/*!
 * @brief Print student list
 *
 * @param void.
 *
 * @return void.
 */
void FresherPrintList() {
    struct student *temp = head;

    /*start from beginning of list*/
    while(temp != NULL) {
        printf("%s          ", temp->name);
        printf("%s          ", temp->account);
        printf("%.1f\n", temp->gpa);
        temp = temp->next;
    }
//    mm_free(head);
}

/*!
 * @brief Find a student with known account
 *
 * @param account[] account string from input keyboard.
 *
 * @return NULL if no student has that account,
 * @return !NULL if exists student with that account.
 */
struct student* FresherFindAcc(char account[]) {
    /* Start searching from first student */
    struct student* current = head;

    /* if list is empty */
    if(head == NULL) {
        return NULL;
    }

    /* student list browsing */
    /* compare current(account) with account entered from keyboard
     * if different --> check if here is the last node (student) -->(Y) --> NULL
     * if different --> .........................................-->(N) --> move to the next node (student)
     * until string compare is satisfied (found student with that account)
    */
    while(strcmp(current->account, account)!=0) {

        /* if this is the last student */
        if(current->next == NULL) {
            return NULL;
        } else {
            /* move to next student */
            current = current->next;
        }
    }

    /* if found, then return the current student */
    return current;
}

/*!
 * @brief Delete a student with known account
 *
 * @param account[] account string from input keyboard.
 *
 * @return NULL if no student has that account,
 * @return !NULL if exists student with that account.
 */
struct student* FresherDeleteAcc(char account[]) {
    /* start from first student */
    struct student* current = head;
    struct student* previous = NULL;

    /* if list is empty */
    if(head == NULL) {
        return NULL;
    }

    /* student list browsing */
    /* compare current(account) with account entered from keyboard
     * if different --> check if here is the last node (student) -->(Y) --> NULL
     * if different --> .........................................-->(N) --> move to the next node (student)
     * until string compare is satisfied (found student with that account)
    */
    while(strcmp(current->account, account)!=0) {

        /* if here is the last student */
        if(current->next == NULL) {
            return NULL;
        } else {
            /* save the current student to temporarily previous student*/
            previous = current;
            /* move to next student*/
            current = current->next;
        }
    }

    /* update student */
    if(current == head) {
        /* change head (first) to point to next student*/
        head = head->next;
    } else {
        /* skip the current student */
        previous->next = current->next;
    }

    return current;
}
