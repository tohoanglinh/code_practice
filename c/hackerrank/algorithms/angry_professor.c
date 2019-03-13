/**
 * File   : angry_professor.c
 * Author : To Hoang Linh
 * Date   : 2019-01-11
 * ForWhat: A discrete mathematics professor has a class of students. Frustrated
 * with their lack of discipline, he decides to cancel class if fewer than some
 * number of students are present when class starts. Arrival times go from on time
 * (arrivalTime < 0) to arrived late (arrivalTime > 0). Given the arrival time of
 * each student and a threshold number of attendees, determine if the class is canceled.
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
    int test_cases;
    int i_index;
    int j_index;
    int number_students_n;
    int threshold_k;
    int *arrival_time;
    int on_time_counter = 0;

    scanf("%d", &test_cases);

    for (i_index = 0; i_index < test_cases; i_index++)
    {
        scanf("%d %d", &number_students_n, &threshold_k);

        arrival_time = (int *)malloc(number_students_n);

        for (j_index = 0; j_index < number_students_n; j_index++)
        {
            scanf("%d ", arrival_time+j_index);
            if (*(arrival_time+j_index) <= 0)
            {
                on_time_counter++;
            }
        }

        for (j_index = 0; j_index < number_students_n; j_index++)
        {
            printf("%d ", *(arrival_time+j_index));
        }

        if (on_time_counter >= threshold_k)
        {
            /* Class continues */
            printf("NO\n");
        }
        else
        {
            /* Class is canceled */
            printf("YES\n");
        }

        on_time_counter = 0;
        free(arrival_time);
    }

    return 0;
}
