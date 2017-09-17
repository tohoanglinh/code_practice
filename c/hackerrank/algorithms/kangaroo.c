/*
 * File   : kangaroo.c
 * Author : To Hoang Linh
 * Date   : 2017-07-10
 * ForWhat: There are two kangaroos on a number line ready to jump in the positive direction
 * (i.e, toward positive infinity). The first kangaroo starts at location x1 and moves at a
 * rate of v1 meters per jump. The second kangaroo starts at location x2 and moves at rate
 * of v2 meters per jump. Given the starting locations and movement rates for each kangaroo,
 * can you determine if they'll ever land at the same location at the same time?
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
    int x1, x2, v1, v2;
    x1 = 0;
    x2 = 0;
    v1 = 0;
    v2 = 0;
    
    while ((x1 < 0) || (x1 > 10000) ||
           (x2 < 0) || (x2 > 10000) ||
           (v1 < 1) || (v1 > 10000) ||
           (v2 < 1) || (v2 > 10000))
    scanf("%d %d %d %d", &x1, &v1, &x2, &v2);

    if (((x1 > x2) && (v2 < v1)) ||
        ((x1 < x2) && (v2 > v1)) ||
        ((x1 != x2) && (v2 == v1)) ||
        ((x1 == x2) && (v2 != v1)))
    {
        printf("NO\n");
    }
    else
    {
        if ((x1 > x2) && ((x1 - x2) % (v2 - v1) == 0))
        {
            printf("YES\n");
        }
        else if ((x1 > x2) && ((x1 - x2) % (v2 - v1) != 0))
        {
            printf("NO\n");
        }
        if ((x1 < x2) && ((x2 - x1) % (v1 - v2) == 0))
        {
            printf("YES\n");
        }
        else if ((x1 < x2) && ((x2 - x1) % (v1 - v2) != 0))
        {
            printf("NO\n");
        }
    }
    
    return 0;
}
