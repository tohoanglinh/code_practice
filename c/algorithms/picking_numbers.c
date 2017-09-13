/**
 * File   : picking_numbers.c
 * Author : To Hoang Linh
 * Date   : 2017-09-05
 * ForWhat: Given an array of integers, find and print the maximum number of
 * integers you can select from the array such that the absolute difference
 * between any two of the chosen integers is less or equal than 1.
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
#define MAX_CNT 200

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    printf("Picking Numbers\n");
    /* input n: size of the array */
    int n;
    n = 0;
    while (n < 2 || n > 100)
    {
        scanf("%d", &n);
    }
    int *arr;
    arr = malloc(sizeof(int)*n);
    if (NULL == arr)
    {
        return (-1);
    }
    int i;
    for (i = 0; i < n; i++)
    {
        scanf(" %d", arr+i);
    }

    /* output */

    free(arr);
    return 0;
}
