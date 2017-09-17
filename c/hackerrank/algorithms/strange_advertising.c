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
    /*
    Day1: 5 receiver, floor(5/2) likes = floor(receiver/2)
    Day2: floor(5/2)*3 receiver, floor(6/2) likes = floor(receiver/2)
    receiver = last_receiver*3;
    likes = floor(receiver/2);
    last_receiver = receiver;
    Day3:
    */
    /* Start with 5 people, after n days, how many people likes that ad? */
    double receiver, last_receiver;
    int day;
    int totallikes;
    day = 1;
    double *numlikes;
    numlikes = malloc(sizeof(double)*n);
    last_receiver = 5;
    totallikes = 0;
    while (day <= n)
    {
        /* main code */
        receiver = last_receiver*3;
        if (day == 1)
        {
            receiver = last_receiver;
        }
        numlikes[day] = floor(receiver/2);
        last_receiver = numlikes[day];
        totallikes = totallikes + (int)(numlikes[day]);
        day++;
    }

    printf("%d", totallikes);

    free(numlikes);
    return 0;
}