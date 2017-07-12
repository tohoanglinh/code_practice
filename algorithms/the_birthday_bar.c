/*
 * File   : the_birthday_bar.c
 * Author : To Hoang Linh
 * Date   : 2017-07-12
 * ForWhat: Birthday Chocolate. ly has a chocolate bar consisting of a row of n squares where
 * each square has an integer written on it. She wants to share it with Ron for his birthday,
 * which falls on month m and day d. Lily wants to give Ron a piece of chocolate only if it
 * contains m consecutive squares whose integers sum to d.
 * Given m, d, and the sequence of integers written on each square of Lily's chocolate bar,
 * how many different ways can Lily break off a piece of chocolate to give to Ron?
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

int sum_m_consecutive(int arr[], int size_arr, int m, int start)
{
    int i;
    int sum;
    sum = arr[start];
    i = start+1;
    while (i < (start+m))
    {
        sum = sum + arr[i];
        i++;
    }
    return sum;
}

int main(void)
{
    /* input */
    /* n: number of squares in the chocolate bar */
    int n;
    scanf("%d", &n);
    
    /* s: pointer to n integers, s0, s1, ..., sn-1 */
    int i;
    int *s;
    s = malloc(n*sizeof(int));
    if (NULL == s)
    {
        printf("malloc failed\n");
        return (-1);
    }
    for (i = 0; i < n; i++)
    {
        scanf(" %d", s+i);
    }

    /* d: Ron's birth day and m: Ron's birth month */
    int d;
    int m;
    scanf("%d %d", &d, &m);
    int cnt = 0;
    /* check consecutive sum */
    for (i = 0; i < n; i++)
    {
        /* if m consecutive numbers have sum to be d --> found++ */
        if (i + m > n)
        {
            /* do not calculate sum */
        }
        else
        {
            /*printf("sum of m = %d consecutive from %d is %d\n", m, i, sum_m_consecutive(s,n, m,i));*/
            if (sum_m_consecutive(s,n, m,i) == d)
            {
                cnt++;
            }
        }
    }
    printf("%d", cnt);
    
    free(s);
    return 0;
}
