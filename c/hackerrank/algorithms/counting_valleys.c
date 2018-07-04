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
    /* input n: number of steps in Gary's hike 8 */
    int n = 0;
    #if (DEBUG)
    printf("number of steps in Gary's hike: ");
    #endif
    while (n < 2 || n > 1e6)
    {
    	scanf("%d ", &n);
	}
    
    /* input: sequence of Up-Down steps UDDDUDUU */
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

	int height = 0;		/* start from sea level */
	int cnt_valley = 0;
	int check = 1;
	
	for (i = 0; i < n; i++)
	{
		if (sequenceUD[i] == 'U')
		{
			height++;	
		}
		else if (sequenceUD[i] == 'D')
		{
			height--;
		}

        #if (DEBUG)
		printf("i = %d, height = %d\n", i, height);
        #endif

		if (check == 1 && height == (-1))
		{
			cnt_valley++;
			check = 0;
		}

		if (height == 0)
		{
			/* is it valley or mountain? */
			check = 1;
		}
	}
	
	printf("%d", cnt_valley);
	
    free(sequenceUD);

    return 0;
}
