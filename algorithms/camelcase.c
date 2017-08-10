/**
 * File   : camelcase.c
 * Author : To Hoang Linh
 * Date   : 2017-07-24
 * ForWhat: Alice wrote a sequence of words in CamelCase as a string of letters,
 * s , having the following properties:
 * - It is a concatenation of one or more words consisting of English letters.
 * - All letters in the first word are lowercase.
 * - For each of the subsequent words, the first letter is uppercase and rest of
 * the letters are lowercase.
 * Given s, print the number of words in s on a new line.
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
#define MAX_LENGTH 100000

/*******************************************************************************
 * Code
 ******************************************************************************/
bool isCapital(char ch)
{
    /* is this character capital? */
    if ((ch >= 'A') && (ch <= 'Z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(void)
{
    /* input */
    char *string_s;
    string_s = malloc(MAX_LENGTH*sizeof(char));
    scanf("%s", string_s);

    /* output */
    int i;
    i = 0;
    int cnt;
    cnt = 1;
    while (string_s[i] != '\0')
    {
        if (true == isCapital(string_s[i]))
        {
            cnt++;
        }
        i++;
    }

    printf("%d", cnt);
    
    free(string_s);
    return 0;
}
