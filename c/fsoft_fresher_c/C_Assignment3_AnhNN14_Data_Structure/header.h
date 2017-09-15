#ifndef _HEADER_H_
#define _HEADER_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_NAME_LENGTH 50

struct student{
	char name[MAX_NAME_LENGTH];
	struct student *next;
};

/*******************************************************************************
 * API for Linked List Functions
 ******************************************************************************/
void studentAddData(char name[]);
/*!
 * @brief Add data(name) of student
 *
 * @param name[] a string as name from user keyboard.
 *
 * @return void.
 */
void studentPrintList(void);
/*!
 * @brief Print student list
 *
 * @param void.
 *
 * @return void.
 */
struct student* studentFindName(char name[]);
/*!
 * @brief Find a student with known name
 *
 * @param name[] name string from input keyboard.
 *
 * @return NULL if no student has that name,
 * @return !NULL if exists student with that name.
 */
struct student* studentRemoveName(char name[]);
/*!
 * @brief Remove a student with known name
 *
 * @param name[] name string from input keyboard.
 *
 * @return NULL if no student has that name,
 * @return !NULL if exists student with that name.
 */
#endif /* _HEADER_H_ */
