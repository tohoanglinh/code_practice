/**
 * File   : count.c
 * Author : To Hoang Linh
 * Date   : 2017-10-07
 * ForWhat: Line count challenge. Count total number of lines and take file as
 * argument. Lines are defined as ending with a newline character. Program usage
 * should be: count filename.txt
 * and the output should be the line count.
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
#define COUNT_VERSION 0.1

/*******************************************************************************
 * Code
 ******************************************************************************/
void wait(void)
{
    char c;
    c = getchar();
    while (getchar() != '\n');
}

int main(int argc, char *argv[])
{
    /* variable */
    char *file_name;

    /** usage
     * --help: display help information
     * --version: display version information
     * --file_path
     */

    if (argc < 2)
    {
        printf("wrong usage\n");
    }
    else
    {
        /* help information */
        if (0 == strcmp(argv[1], "--help"))
        {
            printf(
                   " --file file_path\n"
                   " --version: display version information\n"
                   " --help: display this help information\n"
                  );
        }
        /* version information */
        if (0 == strcmp(argv[1], "--version"))
        {
            printf("Count version %2.1f\n", COUNT_VERSION);
        }
        /* parsing file */
        if (0 == strcmp(argv[1], "--file"))
        {
            printf("Count %s\n", argv[2]);
        }

    }

    return 0;
}
