/**
 * File   : template.c
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

void draw_square(int num)
{
    /* draw a square with input number */
    int i;

    for (i = 0; i < num; i++)
    {
         printf("%d", num);
    }
}

int main(void)
{
    /* input */
    int n;

    scanf("%d", &n);

    printf("Gia tri n = %d\n", n);

    /* output */
    return 0;
}
