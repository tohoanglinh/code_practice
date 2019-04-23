/**
 * File   : printing_tokens.c
 * Author : To Hoang Linh
 * Date   : 2019-04-23
 * ForWhat: Printing Tokens
 * Given a sentence, s, print each word of the sentence in a new line
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_STRING_LENGTH   (500)

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    char *input_string;
    int i;

    input_string = (char *)malloc(sizeof(char)*MAX_STRING_LENGTH);

    if (input_string == NULL)
    {
        printf("Failed to allocate memory\n");
        return 1;
    }

    scanf("%[^\n]s", input_string);

    for (i = 0; i < strlen(input_string); i++)
    {
        if (' ' == input_string[i])
        {
            printf("\n");
        }
        else
        {
            printf("%c", input_string[i]);
        }
    }

    free(input_string);

    return 0;
}
