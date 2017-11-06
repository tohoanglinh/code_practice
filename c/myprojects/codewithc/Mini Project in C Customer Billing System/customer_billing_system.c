/**
 * File   : customer_billing_system.c
 * Author : To Hoang Linh
 * Date   : 2017-08-28
 * ForWhat: to create a generic template for C/C++ source coding.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define WINDOWS

/*******************************************************************************
 * Code
 ******************************************************************************/
void wait(void)
{
    char c;
    c = getchar();
    while (getchar() != '\n');
}

void clrscr()
{
    #ifdef WINDOWS
    system("cls");
    #endif // WINDOWS

    #ifdef LINUX
    system("clear");
    #endif // LINUX
}

void welcome()
{
    printf("   CUSTOMER BILLING SYSTEM\n");
    printf("============================\n");
    printf("1: to add account on list\n");
    printf("2: to search account\n");
    printf("3: to exit\n");
    printf("============================\n");
}

int main(void)
{
    /* variables declaration */
    char choice;

    /* variables initialization */

    /* program flows */
    clrscr();

    welcome();

    /* 1. wait for key from user */
    do
    {
        printf("Enter your choice number:");
        choice = getchar();
    } while (choice <= '0' || choice > '3');

    /* 2. switch based on entered key */
    switch(choice)
    {
    case '1':
        clrscr();
        printf("How many customer accounts?\n");
        main();
        break;
    case '2':
        clrscr();
        main();
        break;
    case '3':
        printf("----------------------------\n");
        printf("Author: To Hoang Linh\n");
        printf("Date  : 2017-10-16\n");
        printf("----------------------------\n");
        break;
    default:
        printf("N/A\n");
    }

    return 0;
}
