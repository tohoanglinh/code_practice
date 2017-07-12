/*
 * File   : breaking_best_and_worst_records.c
 * Author : To Hoang Linh
 * Date   : 2017-07-10
 * ForWhat: Maria plays n games of college basketball in a season. Because she wants to go pro, she tracks her points
 * scored per game sequentially in an array defined as score=[s_0, s_1, ..., s_n-1]. After each game i, she checks to
 * see if score s_i breaks her record for most or least points scored so far during that season. Given Maria's array
 * of scores for a season of n games, find and print the number of times she breaks her record for most and least
 * points scored during the season.
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
    /* n: number of games */
    int n;
    n = 0;
    while (n < 1 || n > 1000)
    {
        scanf("%d", &n);
    }
    
    int i;
    int *s;
    s = malloc(n*sizeof(int));
    if (NULL == s)
    {
        printf("malloc is failed\n");
        return (-1);
    }
    
    for (i = 0; i < n; i++)
    {
        scanf(" %d", s+i);
    }
    
    i = 0;
    int cnt_highest, cnt_lowest;
    cnt_highest = 0;
    cnt_lowest = 0;
    int highest, lowest;
    highest = s[0];
    lowest = s[0];
    while (i < (n-1))
    {
        if (s[i+1] > highest)
        {
            /* found */
            cnt_highest++;
            highest = s[i+1];
        }
        if (s[i+1] < lowest)
        {
            /* found */
            cnt_lowest++;
            lowest = s[i+1];
        }
        i++;
    }

    printf("%d %d", cnt_highest, cnt_lowest);
    
    free(s);
    return 0;
}
