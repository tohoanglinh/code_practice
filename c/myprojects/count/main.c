/**
 * File   : count.c
 * Author : To Hoang Linh
 * Date   : 2017-10-07
 * ForWhat: Line count challenge. Count total number of lines and take file as
 * argument. Lines are defined as ending with a newline character. Program usage
 * should be: count filename.txt
 * and the output should be the line count.
 * Copyright © 2017 Hoang-Linh_TO. All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "count.h"
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void waitForEnter(void);

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CMD_LINE 1
#define LIB      0
#define VERSION  0.3

/*******************************************************************************
 * Code
 ******************************************************************************/
void waitForEnter(void)
{
    char c;
    c = getchar();
    while (getchar() != '\n');
}

int main(int argc, const char * argv[])
{
#if CMD_LINE
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
            printf("Version %2.1f\n", VERSION);
        }
        /* parsing file */
        if (0 == strcmp(argv[1], "--file"))
        {
            printf("Number of lines = %d\n", count((char*)argv[2]));
        }
    }
#endif /* CMD_LINE */

#if LIB
    printf("Number of lines = %d\n", count("/Users/linhto/gitworks/code_practice/c/count.c"));
#endif /* LIB */
    
    return 0;
}
