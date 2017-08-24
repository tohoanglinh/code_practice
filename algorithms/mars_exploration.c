/**
 * File   : mars_exploration.c
 * Author : To Hoang Linh
 * Date   : 2017-07-24
 * ForWhat: Sami's spaceship crashed on Mars! She sends n sequential SOS messages
 * to Earth for help. Letters in some of the SOS messages are altered by cosmic
 * radiation during transmission. Given the signal received by Earth as a string,
 * S, determine how many letters of Sami's SOS have been changed by radiation.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_LEN 99

/*******************************************************************************
 * Code
 ******************************************************************************/
int getLength(char *str)
{
    int i;
    i = 0;
    while (i <= MAX_LEN)
    {
        if (str[i] == '\0')
        {
            return i;
        }
        i++;
    }
    return 0;
}
 
int main(void)
{
    /* input: a single string S */
    char *S;

    S = malloc(sizeof(char)*MAX_LEN);

    scanf("%s", S);

    printf("%d", getLength(S));
    getch();

    while ((getLength(S)%3 != 0) || (getLength(S) < 1) || (getLength(S) > 99))
    {
        printf("Please re-enter string S:\n");
        scanf("%s", S);
    }

    S = realloc(S, getLength(S));

    /* output: number of letters that was corrupted due to cosmic radiation */
    int idx;
    int err;
    err = 0;
    for (idx = 0; idx < getLength(S); idx+=3)
    {
        if (S[idx] != 'S')
        {
            err++;
        }

        if (S[idx+1] != 'O')
        {
            err++;
        }

        if (S[idx+2] != 'S')
        {
            err++;
        }
    }
    printf("%d", err);
    
    free(S);
    return 0;
}
