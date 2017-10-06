/**
 * File   : flow_control.c
 * Author : To Hoang Linh
 * Date   : 2017-10-06
 * ForWhat: Prof. Jeonghoon Mo lecture, ICE0662: Network Optimization (Fall 2005)
 *          Lecture 7-8: Flow Control I+II
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <gsl/gsl_sf_bessel.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

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
    int num_flows = 3;
    int num_links = 2;

    int end_sim = 500;
    float stepsize = 0.1;

    int i;
//    for (i = 1; i < end_sim; i++)
//    {
//        p = p + stepsize;
//    }

    double x = 5.0;
    double y = gsl_sf_bessel_J0(x);
    printf ("J0(%g) = %.18e\n", x, y);

    return 0;
}
