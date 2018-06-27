/**
 * File   : designer_pdf_viewer.c
 * Author : To Hoang Linh
 * Date   : 2018-06-27
 * ForWhat: When you select a contiguous block of text in a PDF viewer, the selection
 * is highlighted with a blue rectangle. In this PDF viewer, each word is highlighted independently.
 * In this challenge, you will be given a list of letter heights in the alphabet and a string.
 * Using the letter heights given, determine the area of the rectangle highlight
 * in mm2 assuming all letters are 1mm wide
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define WIDTH_CHAR  1		/* width of a character is 1mm */

#define MAX_WORD_LENGTH 10

#define SIZE_ABC 26

int g_height[SIZE_ABC];

/*******************************************************************************
 * Code
 ******************************************************************************/
void wait(void)
{
    char c;
    c = getchar();
    while (getchar() != '\n');
}

int charToIndex(char ch)
{
    return (ch-97);
}

int maxHeight(char tmp_str[], int length_str)
{
    int i;
    int max = g_height[charToIndex(tmp_str[0])];

    for (i = 0; i < length_str; i++)
    {
        if (max <= g_height[charToIndex(tmp_str[i])])
        {
            max = g_height[charToIndex(tmp_str[i])];
        }
    }
    return max;
}

int main(void)
{
	/* local var */
	char str[MAX_WORD_LENGTH];
	int i;	
	
	/* input height of characters */
	for (i = 0; i < SIZE_ABC; i++)
	{
		scanf(" %d",&g_height[i]);
	}

	/* input words */
	scanf("%s", str);
	  
    /* output area of selected word */
    printf("%d\n", strlen(str) * WIDTH_CHAR * maxHeight(str, strlen(str)));

    return 0;
}
