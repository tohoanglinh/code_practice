/**
 * File   : printing_pattern_2.c
 * Author : To Hoang Linh
 * Date   : 2017-08-28
 * ForWhat: print the pattern of the following form (squares)
 * containing the numbers from 1 to n.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_CNT 200

/*******************************************************************************
 * Code
 ******************************************************************************/
void draw_pattern(int **array, int dim)
{
    int r, c;

    for (r = 0; r < dim; r++)
    {
        for (c = 0; c < dim; c++)
        {
            printf("%d ", array[r][c]);
        }
        printf("\n");
    }
}

int main(void)
{
    /* input */
    int n;
    int m;
    int i;
    int j;
    int length;

    scanf("%d", &n);

    length = (2*n - 1);

    /* memory allocation for two-dimension array */
    int **arr = (int **)malloc(length * sizeof(int *));
    for (i = 0; i < length; i++)
    {
        arr[i] = (int *)malloc(length * sizeof(int));
    }

    /* set data at each cell location */
    m = 0;
    while (m <= (length / 2))
    {
        for (i = m; i < length-m; i++)
        {
            for (j = m; j < length-m; j++)
            {
                if ((m == i) || (m == j) || ((length-m-1) == i) || ((length-m-1) == j))
                {
                    arr[i][j] = n;
                }
            }
        }
        m++;
        n--;
    }

    /* draw pattern */
    draw_pattern(arr, length);

    /* free allocated memory */
    for (i = 0; i < length; i++)
    {
        free(arr[i]);
    }

    free(arr);

    /* output */
    return 0;
}
