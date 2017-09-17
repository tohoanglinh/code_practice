/**
 * File   : lonely_integer.c
 * Author : To Hoang Linh
 * Date   : 2017-09-12
 * ForWhat: Consider an array of n integers, A = [a0, a1, ..., an-1], where all
 * but none of the integers occur in pairs. In other words, every element in A
 * occurs exactly twice except for one unique element.
 * Given A, find and print the unique element.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Constraints */
#define MAX_NUM_INTEGERS 100

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    /* input n: number of integers in the array */
    int n;
    n = 0;
    while ((n < 1) || (n >= MAX_NUM_INTEGERS) || (n % 2 == 0))
    {
        scanf("%d", &n);
    }

    /* input n space-separated integers */
    int *A;
    A = malloc(sizeof(int)*n);
    int i;
    for (i = 0; i < n; i++)
    {
        scanf(" %d", A+i);
    }

    /* output: print the unique number that occurs only once in A on a new line */
    int unique;
    unique = 0;
    int j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (n == 1)
            {
                unique = 1;
            }
            else
            {
                if (j == i)
                {
                    continue;
                }
                else
                {
                    if (*(A+j) != *(A+i))
                    {
                        unique = 1;
                    }
                    else
                    {
                        unique = 0;
                        break;
                    }
                }
            }
        }
        if (unique == 1)
        {
            printf("%d", *(A+i));
        }
    }

    free(A);
    return 0;
}
