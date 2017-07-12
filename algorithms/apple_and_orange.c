/*
 * File   : apple_and_orange.c
 * Author : To Hoang Linh
 * Date   : 2017-07-10
 * ForWhat: Sam's house has an apple tree and an orange tree that yield an abundance of fruit.
 * In the diagram below, the red region denotes his house, where s is the start point and t is
 * the end point. The apple tree is to the left of his house, and the orange tree is to its right.
 * You can assume the trees are located on a single point, where the apple tree is at point a
 * and the orange tree is at point b.
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

/**
 * FUNCTIONS
 */
int find_new_pos(int origin, int offset)
{
    return (origin + offset);
}

int main(void)
{
    int s, t;
    s = 0;
    t = 0;
    
    int a, b;
    a = 0;
    b = 0;
    while (a >= b || s >= t || a > s || t > b)
    {
        scanf("%d %d", &s, &t);
        scanf("%d %d", &a, &b);
    }

    int m, n;
    scanf("%d %d", &m, &n);
    
    int i;
    int apple_cnt;
    int orange_cnt;
    apple_cnt = 0;
    orange_cnt = 0;
    int *apple;
    int *apple_pos;
    int *orange;
    int *orange_pos;
    apple = malloc(m*sizeof(int));
    apple_pos = malloc(m*sizeof(int));
    orange = malloc (n*sizeof(int));
    orange_pos = malloc (n*sizeof(int));
    if ((NULL == apple) || (NULL == orange) || (NULL == apple_pos) || (NULL == orange_pos))
    {
        printf("malloc is failed\n");
        return (-1);
    }

    for (i = 0; i < m; i++)
    {
        scanf("%d", apple+i);
        *(apple_pos+i) = find_new_pos(a, *(apple+i));
        if (*(apple_pos+i) >= s && *(apple_pos+i) <= t)
        {
            apple_cnt++;
        }
    }

    for (i = 0; i < n; i++)
    {
        scanf("%d", orange+i);
        *(orange_pos+i) = find_new_pos(b, *(orange+i));
        if (*(orange_pos+i) >= s && *(orange_pos+i) <= t)
        {
            orange_cnt++;
        }
    }
    
    /* check for inclusive range */
    printf("%d\n", apple_cnt);
    printf("%d\n", orange_cnt);
    
    free(orange);
    free(apple);
    
    return 0;
}
