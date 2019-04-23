/**
 * File   : digit_frequency.c
 * Author : To Hoang Linh
 * Date   : 2019-04-23
 * ForWhat: Digit Frequency
 * Given a string consisting of alphabets and digits, find the frequency of each digit in the given string.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_STRING_LENGTH (1000U)

/*******************************************************************************
 * Code
 ******************************************************************************/
static int count_frequency(char number, char *strnum, int length_strnum)
{
    int i;
    int count = 0;

    for (i = 0; i < length_strnum; i++)
    {
        if (strnum[i] == number)
        {
            count++;
        }
    }

    return count;
}

int main(void)
{
    char *input_stringnum;
    int i;

    input_stringnum = (char *)malloc(sizeof(char)*MAX_STRING_LENGTH);

    if (input_stringnum == NULL)
    {
        printf("Failed to allocate memory\n");
        return 1;
    }

    scanf("%[^\n]s", input_stringnum);

    printf("%d ", count_frequency('0', input_stringnum, strlen(input_stringnum)));
    printf("%d ", count_frequency('1', input_stringnum, strlen(input_stringnum)));
    printf("%d ", count_frequency('2', input_stringnum, strlen(input_stringnum)));
    printf("%d ", count_frequency('3', input_stringnum, strlen(input_stringnum)));
    printf("%d ", count_frequency('4', input_stringnum, strlen(input_stringnum)));
    printf("%d ", count_frequency('5', input_stringnum, strlen(input_stringnum)));
    printf("%d ", count_frequency('6', input_stringnum, strlen(input_stringnum)));
    printf("%d ", count_frequency('7', input_stringnum, strlen(input_stringnum)));
    printf("%d ", count_frequency('8', input_stringnum, strlen(input_stringnum)));
    printf("%d ", count_frequency('9', input_stringnum, strlen(input_stringnum)));

    free(input_stringnum);

    return 0;
}
