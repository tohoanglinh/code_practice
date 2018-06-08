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
	uint32_t x;
	uint32_t y;
} usdhc_t;

#define BUFFER_SIZE 100

uint8_t g_data[BUFFER_SIZE];

void tc_01(void)
{
	g_data[10];
}

void tc_02(void)
{
	g_data[50];
}

int main(void)
{
    /* input */
    char str[] = "abc";

	uint32_t arr[8];
	
	printf("Hi arr %d\n", sizeof(usdhc_t));

    int length = 0;
    
	tc_01();
	
	tc_02();

    /* output */
    length = strlen(str);

    //printf("%d\n", charToIndex(str[1]));

    printf("Hello %d\n", maxHeight(str, length));

    return 0;
}
