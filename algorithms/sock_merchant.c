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

int find_duplicate(int *arr, int size_arr)
{
    
    return 0;
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
    // find the duplicate color element
    find_duplicate(color, n);
    
    free(color);
    return 0;
}
