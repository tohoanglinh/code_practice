/**
 * File   : equality_in_a_array.c
 * Author : To Hoang Linh
 * Date   : 2017-08-11
 * ForWhat: Karl has an array of n integers defined as A = a0, a1, ..., an-1.
 * In one operation, he can delete any element from the array.
 * Karl wants all the elements of the array to be equal to one another. To do
 * this, he must delete zero or more elements from the array. Find and print
 * the minimum number of deletion operations Karl must perform so that all the
 * array's elements are equal.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "../temp/lwipcfg.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_CNT 200

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    /* input */
    int n;      /* n: number of elements in array A */
    int i;
    int *A = malloc(sizeof(int)*n);
    
    printf("%d", LWIP_DHCP);
    getch();
    
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf(" %d", A+i);
    }

    /* output */
    free(A);
    return 0;
}
