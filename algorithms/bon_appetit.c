/*
 * File   : bon_appetit.c
 * Author : To Hoang Linh
 * Date   : 2017-07-10
 * ForWhat: Bon Appetit. Anna and Brian order n items at a restaurant, but Anna declines
 * to eat any of the k_th item (where 0<=k<n) due to an allergy. When the check comes,
 * they decide to split the cost of all the items they shared; however, Brian may have
 * forgotten that they didn't split the k_th item and accidentally charged Anna for it.
 *
 * You are given n, k, the cost of each of the n items, and the total amount of money
 * that Brian charged Anna for her portion of the bill. If the bill is fairly split,
 * print Bon Appetit; otherwise, print the amount of money that Brian must refund to Anna.
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

int main(void)
{
    /* n: number of items ordered, k: index of the item that Anna did not eat */
    long n, k;
    scanf("%ld %ld", &n, &k);

    /* cost of each item */
    long i;
    int *cost;
    cost = malloc(n*sizeof(int));
    if (NULL == cost)
    {
        return (-1);
    }
    for (i = 0; i < n; i++)
    {
        scanf(" %d", cost+i);
    }

    /* amount of money that Brian charged Anna for her share of the bill */
    float b_charged;
    scanf("%f", &b_charged);

    /* output */
    float b_actual;
    b_actual = 0;
    int sum;
    sum = 0;
    for (i = 0; i < n; i++)
    {
        if (i != k)
        {
            sum = sum + cost[i];
        }
    }
    //printf("sum = %d\n", sum);
    b_actual = (float)(sum)/2;
    //printf("b_actual = %f\n", b_actual);

    if (b_charged > b_actual)
    {
        printf("%d\n", (int)(b_charged-b_actual));
    }
    else
    {
        printf("Bon Appetit\n");
    }

    free(cost);
    return 0;
}
