/**
 * File   : strange_advertising.c
 * Author : To Hoang Linh
 * Date   : 2017-08-17
 * ForWhat: HackerLand Enterprise is adopting a new viral advertising strategy.
 * When they launch a new product, they advertise it to exactly 5 people on
 * social media.
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
 * Definitions
 ******************************************************************************/
#define MAX_CNT 200

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    /* input: a single integer, n, denoting a number of days */
    int n;
    n = 0;
    while (n < 1 || n > 50)
    {
        scanf("%d", &n);
    }
    
    /* output: no of people who liked the ad during the first n days */
    printf("%f", floor(5/2));
    
    /*
    Day1: 5 receiver, floor(5/2) likes
    Day2: floor(5/2)*3 receiver, floor(6/2) likes
    Day3:
    */
    
    return 0;
}
