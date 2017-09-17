/**
 * File   : maximizing_xor.c
 * Author : To Hoang Linh
 * Date   : 2017-09-15
 * ForWhat: given two integers, L and R, find the maximal value of A xor B,
 * where A and B satisfy the following condition: L <= A <= B <= R.
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
 * Prototypes
 ******************************************************************************/
int func_Max(int arr[], int arr_size);
int func_TotalCases(int n);

/*******************************************************************************
 * Code
 ******************************************************************************/
int func_Max(int arr[], int arr_size)
{
    int i;
    int max;
    i = 0;
    max = 0;
    for (i = 0; i < arr_size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int func_TotalCases(int n)
{
    if (n > 1)
    {
        return n+func_TotalCases(n-1);
    }
    else
    {
        return 1;
    }
}

int main(void)
{
    /* input L and R */
    int L;
    int R;
    L = 0;
    R = 0;
    while (L < 1 || L > 1000)
    {
        scanf("%d", &L);
    }
    while (R < 1 || R > 1000)
    {
        scanf("%d", &R);
    }

    /* output L <= A <= B <= R */
    int A;
    int B;
    int *xor_arr;
    int total_num;
    int xor_arr_index;

    total_num = func_TotalCases(R - L + 1);
    xor_arr = malloc(sizeof(int)*total_num);

    xor_arr_index = 0;
    for (A = L; A < R; A++)
    {
        for (B = A; B < R; B++)
        {
            xor_arr[xor_arr_index] = A ^ B;
            //printf("%d", xor_arr[xor_arr_index]);
            printf("%d", 15 ^ 21);
            getchar();
            xor_arr_index++;
        }
        xor_arr_index++;
    }

    //printf("%d", func_Max(xor_arr, total_num));

    free(xor_arr);
    return 0;
}
