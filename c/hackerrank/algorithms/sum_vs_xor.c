/**
 * File   : sum_vs_xor.c
 * Author : To Hoang Linh
 * Date   : 2017-09-21
 * ForWhat: Given an integer n, find each x such that
 * 0 <= x <= n
 * n + x = n xor x.
 * output: total number of x that satisfies the criteria
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/*******************************************************************************
 * Code
 ******************************************************************************/
unsigned long long numOfZeros(unsigned long long num)
{
    unsigned long long remainder;
    unsigned long long zeros;
    zeros = 0;
    while (num > 0)
    {
        remainder = num % 2;
        num = num/2;
        if (remainder == 0)
        {
            zeros++;
        }
    }
    return zeros;
}

int main(void)
{
    /* input n: a single integer */
    unsigned long long n;
    scanf("%llu", &n);

    /* output */
    /**
    * n+x = n|x + n&x
    * n^x = n|x - n&x
    * n&x = 0, find x
    */
    printf("%llu", (unsigned long long)(pow(2,numOfZeros(n))));

    return 0;
}
