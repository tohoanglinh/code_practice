/*
 * File   : sock_merchant.c
 * Author : To Hoang Linh
 * Date   : 2017-07-10
 * ForWhat: Sock Merchant. John's clothing store has a pile of n loose socks, where each sock
 * i is labeled with an integer, c_i, denoting its color. He wants to sell as many socks as
 * possible, but his customers will only buy them in matching pairs. Two socks, i and j, are
 * single matching pair if c_i = c_j.
 * Given n and the color of each sock, how many pairs of socks can John sell?
 */

/**
 * INCLUDES
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * DEFINES & MACROS
 */
#define TRUE  1
#define FALSE 0

int find_duplicate(int element, int *arr, int size_arr)
{
    int i;
    int cnt;
    cnt = 0;
    for (i = 0; i < size_arr; i++)
    {
        if (arr[i] == arr[element])
        {
            cnt++;
        }
    }
    return cnt;
}

int main(void)
{
    /* input n: number of socks */
    int n;
    n = 0;

    while ((n < 1) || (n > 100))
    {
        scanf(" %d", &n);
    }

    int i;
    int *color;
    color = malloc(n*sizeof(int));
    if (NULL == color)
    {
        printf("malloc is failed\n");
        return (-1);
    }
    for (i = 0; i < n; i++)
    {
        scanf(" %d", color+i);
    }
    
    /* output */
    i = 0;
    int j;
    char test;
    while (i < n)
    {
        test = 0;
        /* if i != all the last --> count_number */
        for (j = 0; j < i; j++)
        {
            if (color[i] == color[j])
            {
                test = 1;
            }
        }
        if (1 == test)
        {
            printf("Color type %d is %d\n", color[i], find_duplicate(i, color, n));
        }
        i++;
    }
    
    free(color);
    return 0;
}
