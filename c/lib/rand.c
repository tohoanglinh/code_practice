/**
 * File   : random.c
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
#include <time.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_CNT 200

/*******************************************************************************
 * Code
 ******************************************************************************/
void wait(void)
{
    char c;
    c = getchar();
    while (getchar() != '\n');
}

int main(void)
{
    /* input */
    int iSecret, iGuess;

    /* initialize random seed */
    srand(time(NULL));

    int r = rand();

    /* output */
    printf("iSecret = %d", r);
    return 0;
}
