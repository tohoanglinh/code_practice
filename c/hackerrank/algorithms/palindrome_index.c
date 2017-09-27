/**
 * File   : palindrome_index.c
 * Author : To Hoang Linh
 * Date   : 2017-09-26
 * ForWhat: given a string, S, of lowercase letters, determine the index of the
 * character whose removal will make S a palindrome. If S is already a palindrome,
 * or no such character exists, then print -1. There will always be a valid solution
 * , and any correct answer is acceptable. For example, if S = 'bcbc', we can
 * either remove 'b' at index 0 or 'c' at index 3.
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
#define MAX_CHAR 200

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
    /* input T: number of test cases */
    int T;
    scanf("%d", &T);
    char test_index;
    char char_index;
    char_index = 0;
    char str[3][MAX_CHAR];
    for (test_index = 0; test_index < T; test_index++)
    {
        while (str[test_index][char_index] != '\0')
        {
            scanf("%c", str[test_index][char_index]);
            char_index++;
        }
    }
    printf("Test");
    for (test_index = 0; test_index < T; test_index++)
    {
        printf("%s\n", str[test_index]);
    }
    /* output */
    //free(*str);
    //free(str);
    return 0;
}
