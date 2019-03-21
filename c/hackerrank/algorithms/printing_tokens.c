#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH   (100)

int main(void)
{
    /*
    * Printing Tokens
    * Given a sentence, s, print each word of the sentence in a new line
    */

    char input_string[MAX_STRING_LENGTH];
    int i;
    int j;
    char word[MAX_STRING_LENGTH];
    int start_char = 0;
    int end_char = 0;

    scanf("%[^\n]s", input_string);

    // printf("Length of string = %d\n", strlen(input_string));

    for (i = 0; i < strlen(input_string); i++)
    {
        if ((' ' == input_string[i]) || ('\0' == input_string[i]))
        {
            // printf("found a word\n");
            end_char = i;
            // start_char -> end_char
            for (j = start_char; j < end_char; j++)
            {
                word[j - start_char] = input_string[j];
            }
            word[j+1] = '\0';
            printf(word);
            printf("\n");
            start_char = end_char+1;
        }
    }

    return 0;
}
