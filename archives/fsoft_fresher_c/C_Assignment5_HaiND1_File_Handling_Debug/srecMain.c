/*******************************************************************************
 * Assignment 5: SREC (17-1)
 * @dev: linhth8
 * @mentor: haind1
 * @topic: file handling, debugging
 * Main Function: PARSE FILE SREC
 * Check Format and Checksum of each line
 *      isError  --> printout Error
 *      notError --> printout Address + Data
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "srecHeader.h"

uint8_t main(void)
{
    /* variable declaration and init */
    FILE *fsrec_in;
    uint16_t line_count = 1; /* uint16_t data types count upto 1667 lines in test.srec */
    char *line;

    /* allocate memory to each line pointer */
    line = (char*)malloc(SREC_MAX_LENGTH_LINE*sizeof(char));

    /* header line */
    printf("PARSE FILE MOTOROLA S-RECORD.\n");

    /* open file input.srec in reading mode */
    fsrec_in = fopen("input.srec", "r+");
    /* open file output.srec to write out all parsed information */
    g_fsrec_out = fopen("output.srec","w+");

    /* read file srec line-by-line */
    do
    {
        /* fscanf file fsrec_in per line */
        fscanf(fsrec_in, "%s", line);

        /* output and display line no: line */
        printf("------------------------------------------\n");
        fprintf(g_fsrec_out, "------------------------------------------\n");
        printf("Line %d:\n%s\n", line_count, line);
        fprintf(g_fsrec_out,"Line %d:\n%s\n", line_count, line);

        /* test format of each line */
        if (srecFormat(line))
        {
            /* test checksum of each line */
            if (srecChecksumGet(line)==srecChecksumCal(line))
            {
                srecDisplayAddressData(line, srecGetType(line));
            }
            else
            {
                printf("SREC incorrect checksum.\n");
                fprintf(g_fsrec_out, "SREC incorrect checksum.\n");
            }
        }
        else
        {
            printf("SREC invalid format.\n");
            fprintf(g_fsrec_out, "SREC invalid format.\n");
        }

        /* increase line no */
        line_count++;
    } while (fgetc(fsrec_in) != EOF); /* end of file condition */

    /* free memory allocated to pointer line */
    free(line);

    /* close file srec in and out*/
    fclose(fsrec_in);
    fclose(g_fsrec_out);

    return(0);
}
