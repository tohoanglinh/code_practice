/**
 * File   : angry_professor.c
 * Author : To Hoang Linh
 * Date   : 2018-12-31
 * ForWhat: a discrete math professor has a class of students. Frustrated with
 * their lack of discipline, he decides to cancel class if fewer than some number
 * of students are present when class starts. Arrival times go from on time to
 * arrived late (arrivalTime > 0).
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
void wait(void)
{
    char c;
    c = getchar();
    while (getchar() != '\n');
}

int main(void)
{
    /* input */
    /* t: number of test cases*/
    int t;
    scanf("%d", &t);



    /* arrival time of each student */
    int arrival_time;



    /* output */
    return 0;
}
