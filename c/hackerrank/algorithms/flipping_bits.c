/**
 * File   : flipping_bits.c
 * Author : To Hoang Linh
 * Date   : 2017-09-20
 * ForWhat: Given a list of 32 bits unsigned integers. You are required to output
 * the list of the unsigned integers you get by flipping bits in its binary representation
 * (i.e., unset bits must be set, and set bits must be unset).
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
#define MAX_T 100

/*******************************************************************************
 * Code
 ******************************************************************************/
void wait(void)
{
    char c;
    c = getchar();
    while (getchar() != '\n');
}

unsigned long convert2binary(unsigned long decimal)
{
    unsigned long base;
    unsigned long remainder;
    unsigned long binary;

    base = 1;
    binary = 0;

    while (decimal > 0)
    {
        remainder = decimal % 2;
        binary = binary + remainder * base;
        decimal = decimal / 2;
        base = base * 10;
    }

    return binary;
}

int main(void)
{
    /* input T: list size */
    int T;
    T = 0;
    while (T < 1 || T > MAX_T)
    {
        scanf("%d", &T);
    }

    unsigned long *num;
    num = malloc(sizeof(unsigned long)*T);

    int i;
    for (i = 0; i < T; i++)
    {
        scanf("%lu", num+i);
    }

    /* output */
    printf("%lu", convert2binary(134));
    //flipbits();

    free(num);
    return 0;
}
