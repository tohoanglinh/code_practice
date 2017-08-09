/*
 * File   : cats_and_a_mouse.c
 * Author : To Hoang Linh
 * Date   : 2017-07-20
 * ForWhat: Two cats named A and B are standing at integral points on the x-axis.
 * Cat A is standing at point x and cat B is standing at point y. Both cats run
 * at the same speed, and they want to catch a mouse named C that's hiding at
 * integral point z on the x-axis. Can you determine who will catch the mouse?
 * You are given q queries in the form of x, y, and z. For each query, print the
 * appropriate answer on a new line:
 * If cat A catches the mouse first, print Cat A.
 * If cat B catches the mouse first, print Cat B.
 * If bot cats reach the mouse at the same time, print Mouse C as the two cats
 * fight and mouse escapes.
 */

/**
 * INCLUDES
 */
/* printf, scanf */
#include <stdio.h>
/* malloc, free, abs */
#include <stdlib.h>

/**
 * DEFINES & MACROS
 */
#define TRUE  1
#define FALSE 0

int main(void)
{
    /* q: number of queries */
    int q;
    scanf("%d", &q);
    int i;
    int x[q];   /* cat A   location */
    int y[q];   /* cat B   location */
    int z[q];   /* mouse C location */
    for (i = 0; i < q; i++)
    {
        scanf("%d %d %d", &x[i], &y[i], &z[i]);
    }
    
    /* output: which catches which first */
    int distAC;
    int distBC;
    
    for (i = 0; i < q; i++)
    {
        distAC = abs(x[i] - z[i]);
        distBC = abs(y[i] - z[i]);
        if (distAC == distBC)
        {
            printf("Mouse C\n");
        }
        else if (distAC > distBC)
        {
            printf("Cat B\n");
        }
        else
        {
            printf("Cat A\n");
        }
    }

    return 0;
}
