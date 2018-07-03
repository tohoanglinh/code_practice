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
#define DEBUG 0

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
    /* input n: number of steps in Gary's hike */
    int n = 0;
    #if (DEBUG)
    printf("number of steps in Gary's hike: ");
    #endif
    while (n < 2 || n > 1e6)
    {
    	scanf("%d ", &n);
	}
    
    /* input: sequence of Up-Down steps */
    char *sequenceUD;
    sequenceUD = malloc(sizeof(char)*n);

    int i;
    i = 0;
    for (i = 0; i < n; i++)
    {
    	scanf("%c", sequenceUD+i);
        while(*(sequenceUD+i) != 'U' && *(sequenceUD+i) != 'D')
        {
        	#if (DEBUG)
        	printf("Reenter order %d pls", i);
        	#endif
        	scanf("%c", sequenceUD+i);
		}
    }

    /* output: number of valleys Gary walked through? */
    int init_height = 0;
    int *height;
    height = malloc(sizeof(int)*n);
    height[0] = init_height;

    for (i = 0; i < n; i++)
    {
        if (*(sequenceUD+i) == 'U')
        {
            height[i+1] = height[i] + 1;
        }
        else if (*(sequenceUD+i) == 'D')
        {
            height[i+1] = height[i] - 1;
        }
        #if (DEBUG)
        printf("i = %d --> %c\n", i, *(sequenceUD+i));
        printf("new height after %d: %d\n", i, height[i+1]);
        #endif /* IF_DEBUG */
    }

    int cnt_valley;
    cnt_valley = 0;
    for (i = 0; i < n; i++)
    {
        #if (DEBUG)
		printf("%d\n", *(height+i));
		#endif
		if (height[i] == 0 && (i == (n-1)))
		{
			break;
		}
        if (height[i] == 0 && height[i+1] < 0)
        {
            cnt_valley++;
        }
    }
    printf("%d", cnt_valley);

    free(height);
    free(sequenceUD);

    return 0;
}
