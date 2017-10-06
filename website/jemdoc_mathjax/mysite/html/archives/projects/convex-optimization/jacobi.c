/**
 * File   : jacobi.c
 * Author : To Hoang Linh
 * Date   : 2017-10-05
 * ForWhat: iterative jacobi algorithms.
 * - Parallel and Distributed Computing: Numerical Methods, D.P. Bertsekas and J.N. Tsitsiklis
 * - Section 2.4, 2.6
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
#define DEBUG 1

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
    /* We need to solve Ax = b */
    /* A = [a11 a12; a21 a22]; */
    /* b = [b1;b2]; */

    /* Matrix A(2x2) and b(2x1) */
    int a11 = 2; int a12 = -1;
    int a21 = -1; int a22 = 2;
    int b1 = 0; int b2 = 0;

    float *x;
    float *y;
    x = malloc(sizeof(float)*100);
    y = malloc(sizeof(float)*100);

    /* Initialize */
    int t = 1;
    x[t] = 10;
    y[t] = 10;

    /* Stop criterion */
    float tolerance = 10e-3;
    int max_iteration = 50;

    /* Jacobi loop */
    while(max_iteration > 0)
    {
        x[t+1] = (-1/(float)a11) * ((float)a12 * y[t] - (float)b1);
        y[t+1] = (-1/(float)a22) * ((float)a21 * x[t] - (float)b2);
        max_iteration = max_iteration - 1;
        #if (DEBUG)
        printf("x[%d] = %f, x[%d] = %f\n", t, x[t], t+1, x[t+1]);
        printf("y[%d] = %f, y[%d] = %f\n", t, y[t], t+1, y[t+1]);
        printf("eps = %f\n", fabs(x[t+1] - x[t]));
        printf("iteration = %d\n", 50-max_iteration);
        #endif
        if (fabs(x[t+1] - x[t]) < tolerance)
        {
            t = t + 1;
            break;
        }
        t = t + 1;
    }

    /* Display results */
    printf("System of Linear Equations: Jacobi Iterative Method\n");
    printf("Number of Iterations: %d \n", 50-max_iteration);
    printf("Solution (x, y) = (%4.4f,%4.4f) \n", x[t], y[t]);

    free(x);
    free(y);
    return 0;
}
