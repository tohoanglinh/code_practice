/**
 * File   : pangrams.c
 * Author : To Hoang Linh
 * Date   : 2017-09-08
 * ForWhat: to create a generic template for C/C++ source coding.
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
#define MAX_STRING_SZ 200

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    /* input */
    char *string_input;
    string_input = malloc(sizeof(char)*MAX_STRING_SZ);
    fgets(string_input, MAX_STRING_SZ, stdin);

    /* output */

    free(string_input);
    return 0;
}
