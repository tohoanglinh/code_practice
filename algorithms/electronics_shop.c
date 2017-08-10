/**
 * File   : electronics_shop.c
 * Author : To Hoang Linh
 * Date   : 2017-08-10
 * ForWhat: Monica wants to buy exactly one keyboard and one USB drive from her
 * favorite electronics store. The store sells n different brands of keyboards
 * and m different brands of USB drives. Monica has exactly s dollars to spend,
 * and she wants to spend as much of it as possible (i.e., the total cost of
 * her purchase must be maximal).
 * Given the price lists for the store's keyboards and USB drives, find and print
 * the amount money Monica will spend. If she doesn't have enough money to buy
 * one keyboard and one USB drive, print -1 instead.
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
int max(int arr[], int size_arr)
{
    int i;
    int max_val;
    max_val = arr[0];
    for (i = 0; i < size_arr; i++)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }
    return 0;
}

int main(void)
{
    /* input */
    int s;      /* s: amount of money Monica has */
    int n;      /* n: number of keyboard brands */
    int m;      /* m: number of USBdrive brands */
    
    scanf("%d %d %d", &s, &n, &m);
    
    int i;
    int *keyboard_price = malloc(n*sizeof(int));
    int *usbdrive_price = malloc(m*sizeof(int));
    for (i = 0; i < n; i++)
    {
        scanf(" %d", keyboard_price+i);
    }

    for (i = 0; i < m; i++)
    {
        scanf(" %d", usbdrive_price+i);
    }
    
    /* output */
    int j;
    int *sum_price;
    sum_price = malloc(n*m*sizeof(int));

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            sum_price[j+m*i] = keyboard_price[i] + usbdrive_price[j];
        }
    }

    int k;
    for (k = 0; k < m*n; k++)
    {
        printf("sum_price[%d] = %d\n", k, sum_price[k]);
    }
   
    free(sum_price); 
    free(keyboard_price);
    free(usbdrive_price);
    return 0;
}
