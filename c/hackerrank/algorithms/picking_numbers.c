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
bool isSubsetSatisfied(int tmp_arr[], int size_tmp_arr)
{
	int i, j;
	for (i = 0; i < size_tmp_arr; i++)
	{
		for (j = 0; j < size_tmp_arr; j++)
		{
			if (abs(tmp_arr[j]-tmp_arr[i]) > 1)
			{
				return false;
			}				
		}
	}
	return true;
}

int fact(int n)
{
	if (n == 0) return 1;
	if (n > 0) return n * fact(n-1);
}

int combinations(int n, int r)
{
	if (n == r) return 1;
	if (r == 0 && n != 0) return 1;
	else
	{
		return (fact(n) / (fact(n-r) * fact(r)));
	}
}
 
int main(void)
{
    printf("Picking Numbers\n");
       
    /* input n: size of the array */
//    int n;
//    n = 0;
//    while (n < 2 || n > 100)
//    {
//        scanf("%d", &n);
//    }
//    
//    int *arr;
//    arr = malloc(sizeof(int)*n);
//    if (NULL == arr)
//    {
//        return (-1);
//    }
//    
//	int i;
//    for (i = 0; i < n; i++)
//    {
//        scanf(" %d", arr+i);
//    }

    /* output */
	/*
	 * 1. pick a subset ???? HOW TO
	 * 2. is the subset satisfied? OK
	 * 3. return number of elements of that subset OK
	 * 4. continue from 1
	 */
	
	
	
//	int max_length = 2;
//	for (;;)
//	{
//		int sub_arr[] = {1, 2, 1, 2};
//		int sub_arr_size = sizeof(sub_arr)/sizeof(int);
//		if (true == isSubsetSatisfied(sub_arr, sub_arr_size))
//		{
//			printf("OK");
//			if (max_length < sub_arr_size)
//			{
//				max_length = sub_arr_size;
//			}
//		}
//		else
//		{
//			printf("NOPE");
//		}		
//	}
//
//	printf("%d", max_length);

//    free(arr);
    return 0;
}
