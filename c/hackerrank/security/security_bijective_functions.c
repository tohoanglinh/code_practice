/**
 * File   : security_bijective_functions.c
 * Author : To Hoang Linh
 * Date   : 2017-09-26
 * ForWhat: onto functions; bijective functions.
 * A function f X -> Y is onto if and only if each element in Y is the image 
 * of at least one element in X. (Im(f) = Y)
 * Bijective functions = one-to-one and onto functions
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
#define MAX_CNT 200

/*******************************************************************************
 * Code
 ******************************************************************************/
void wait(void)
{
    char c;
    c = getchar();
    while (getchar() != '\n');
}

int main(void)
{
    /* input n: size of domain X */
    int n;
    scanf("%d", &n);
    int *f;
    f = malloc(sizeof(int)*n);
    int i;
    for (i = 0; i < n; i++)
    {
        scanf(" %d", f+i);
    }

    /* output */
    if (f == bijective)
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }
    free(X);
    return 0;
}
