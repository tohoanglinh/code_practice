/**
 * File   : counting_valleys.c
 * Author : To Hoang Linh
 * Date   : 2017-08-28
 * ForWhat: Gary is an avid hiker. He tracks his hikes meticulously, paying close
 * attention to small details like topography. During his last hike, he took
 * exactly n steps. For every step he took, he noted if it was an uphill or a
 * downhill step. Gary's hikes start and end at sea level. We define the following
 * terms:
 * - A mountain is a non-empty sequence of consecutive steps above sea level,
 * starting with a step up from sea level and ending with a step down to a sea level.
 * - A valley is a non-empty sequence of consecutive steps below sea level,
 * starting with a step down from sea level and ending with a step up to sea level.
 * Given Gary's sequence of up and down steps during his last hike, find and print
 * the number of valleys he walked through.
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
int main(void)
{
    /* input n: number of steps in Gary's hike */
    int n;
    scanf("%d ", &n);
    
    /* input: sequence of Up-Down steps */
    char *sequenceUD;
    sequenceUD = malloc(sizeof(char)*n);
    
    int i;
    i = 0;
    for (i = 0; i < n; i++)
    {
        scanf("%c", sequenceUD+i);
    }
    
    SUDDDUDUUS
    
    /* output: number of valleys Gary walked through? */
    int init_height = 0;
    int *height;
    height = malloc(sizeof(int)*n);
    *height = init_height;

    for (i = 0; i < n; i++)
    {
        if (*(sequenceUD+i) == 'U')
        {
            *(height+i) = *(height+i-1)+1;
        }
        else if (*(sequenceUD+i) == 'D')
        {
            *(height+i) = *(height+i-1)-1;
        }
    }
    
    for (i = 0; i < n; i++)
    {
        printf("%d", *(height+i));
    }
    
    free(sequenceUD);
    free(height);
    
    return 0;
}
