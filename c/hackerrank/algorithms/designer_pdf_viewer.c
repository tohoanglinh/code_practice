/**
 * File   : designer_pdf_viewer.c
 * Author : To Hoang Linh
 * Date   : 2017-08-28
 * ForWhat: to create a generic template for C/C++ source coding.
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
#define MAX_CNT 200

int g_array[26] = {1, 3, 1, 3, 1, 4, 1, 3, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7};

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
    int max;

    for (i = 0; i < length_str; i++)
    {
        if (g_array[charToIndex(tmp_str[i+1])] > g_array[charToIndex(tmp_str[i])])
        {
            max = g_array[charToIndex(tmp_str[i+1])];
        }
        else
        {
            max = g_array[charToIndex(tmp_str[i])];
        }
    }
    return max;
}

typedef struct
{
	struct gcov_info *info;	
} GcovInfo;

struct gcov_info *infotest;
GcovInfo *fileGcovInfo;

int main(void)
{
    /* input */
    char str[] = "abc";
    
    fileGcovInfo = 
    

    /* output */

    return 0;
}
