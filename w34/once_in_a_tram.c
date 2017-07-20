/*
 * File   : once_in_a_tram.c
 * Author : To Hoang Linh
 * Date   : 2017-07-20
 * ForWhat: One day, Jack was going home by tram. When he got his ticket,
 * he noticed that number on the ticket was not lucky. A lucky ticket is
 * a six-digit number on the ticket in which sum of the first three digits
 * is equal to the sum of the last three digits.
 * For example, number 165912 is lucky because sum of 1+6+5=12, and
 * 9+1+2=12.
 * Since the number on the ticket wasn't lucky, Jack needs your help to find
 * the next lucky ticket number.
 * For example, if Jack's ticket number is 165901, then the next lucky ticket
 * number is 165903.
 * Given Jack's current ticket number, find and print the next lucky ticket
 * number.
 */

/**
 * INCLUDES
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * DEFINES & MACROS
 */
#define MAX_CNT 200

uint8_t isLucky(char *tmp_str)
{
    uint8_t i, first_three_sum, second_three_sum;
    first_three_sum = 0;
    second_three_sum = 0;

    for (i = 0; i < 3; i++)
    {
        first_three_sum = first_three_sum + tmp_str[i];
    }
    for (i = 3; i < 6; i++)
    {
        second_three_sum = second_three_sum + tmp_str[i];
    }
    if (first_three_sum == second_three_sum)
    {
        /* lucky */
        return true;
    }
    else
    {
        /* unlucky */
        return false;
    }
    return 0;
}

uint8_t *decode(long num)
{

}

uint8_t main(void)
{
    /* input x: integer, 6-digit number on the ticket */
    long x;
    x = 0;
    while (x < 0 || x > 999999)
    {
        scanf("%ld", &x);
    }

    /* output */
    uint8_t *x_num;
    x_num = malloc(6);

    isLucky(x_num);

    free(x_num);
    return 0;
}
