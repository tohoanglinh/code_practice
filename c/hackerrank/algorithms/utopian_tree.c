/**
 * File   : uptopian_tree.c
 * Author : To Hoang Linh
 * Date   : 2017-09-11
 * ForWhat: spring: height = height*2
            summer: height = height+1
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
#define INIT_HEIGHT         1  /* 1 meter */
#define MAX_TESTCASE        10
#define MAX_CYCLES          60

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    /* input: T number of test cases */
    int T;
    T = 0;
    while (T < 1 || T > MAX_TESTCASE)
    {
        scanf("%d", &T);
    }

    /* input: N[i] number of cycles for test case i */
    int i;
    int *N;
    N = malloc(sizeof(int)*T);
    for (i = 0; i < T; i++)
    {
        do
        {
            scanf("%d", N+i);
        } while(*(N+i)>MAX_CYCLES || *(N+i)<0);
    }

    /* output */
    int j;              /* j: cycle index */
    int *height;
    height = malloc(sizeof(int)*T);
    for (i = 0; i < T; i++)
    {
        height[i] = INIT_HEIGHT;
        for (j = 0; j < N[i]; j++)
        {
            if (j % 2 == 0)
            {
                height[i] = height[i] * 2;
            }
            else
            {
                height[i] = height[i] + 1;
            }
        }
        printf("%d\n", height[i]);
    }

    free(height);
    free(N);
    return 0;
}
