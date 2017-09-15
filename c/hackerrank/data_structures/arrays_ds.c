/**
 * File   : arrays_ds.c
 * Author : To Hoang Linh
 * Date   : 2017-08-02
 * ForWhat: Data Structures. An array is a type of data structure that stores
 * elements of the same type in a contiguous block of memory. In an array, A,
 * of size N, each memory location has some unique index, i (where 0 <= i < N),
 * that can be referenced as A[i], or A_i.
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
    /* input N: number of integers in A */
    int N;
    scanf("%d", &N);
    int index;
    int A[N];
    for (index = 0; index < N; index++)
    {
        scanf("%d ", &A[index]);
    }

    /* output */
    for (index = (N-1); index >= 0; index--)
    {
        printf("%d ", A[index]);
    }

    return 0;
}
