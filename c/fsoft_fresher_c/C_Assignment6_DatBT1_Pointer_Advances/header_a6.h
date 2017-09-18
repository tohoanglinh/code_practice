#ifndef _HEADER_A6_H_
#define _HEADER_A6_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define printScreen printf("Enter option: \n 1(add), \n 2(print), \n 3(remove), \n 4(sortGpa), \n f(memfree), \n m(memdisplay), \n q(exit).\n")

struct student
{
   char name[50];
   char account[10];
   float gpa;
   struct student *next;
};

/*******************************************************************************
 * API
 ******************************************************************************/
void FresherInputData();
/*!
 * @brief Procedure input data for fresher from keyboard
 *
 * @param void.
 *
 * @return void.
 */

void FresherFreeMemoryList();
/*!
 * @brief Free Memory Allocated for Linked List
 *
 * @param void.
 *
 * @return void.
 */

void FresherAdd(char name[], char account[], float gpa);
/*!
 * @brief Add a fresher student with three inputted arguments
 *
 * @param1 char name
 * @param2 char account
 * @param3 float gpa
 *
 * @return void.
 */

void FresherPrintList();
/*!
 * @brief Print student list
 *
 * @param void.
 *
 * @return void.
 */

void FresherArrangeList();
/*!
 * @brief Arrange list according to GPA (descending, max --> min)
 *        Compare two consecutive gpa --> swap positions.
 * @param void.
 *
 * @return void.
 */

int FresherLengthList();
/*!
 * @brief Return length of record list
 *
 * @param void.
 *
 * @return void.
 */

struct student* FresherDeleteAcc(char account[]);
/*!
 * @brief Delete a student with known account
 *
 * @param account[] account string from input keyboard.
 *
 * @return NULL if no student has that account,
 * @return !NULL if exists student with that account.
 */

struct student* FresherFindAcc(char account[]);
/*!
 * @brief Find a student with known account
 *
 * @param account[] account string from input keyboard.
 *
 * @return NULL if no student has that account,
 * @return !NULL if exists student with that account.
 */

#endif /* _HEADER_A6_H_ */
