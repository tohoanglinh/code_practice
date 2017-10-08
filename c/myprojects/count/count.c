//
//  count.c
//  count
//
//  Created by Hoang-Linh_TO on 10/8/17.
//  Copyright © 2017 Hoang-Linh_TO. All rights reserved.
//

#include "count.h"

int count(char file_path[])
{
    FILE *fp;
    char c;
    int total_line;
    
    fp = fopen(file_path, "r");
    
    if (NULL == fp)
    {
        /* failed to open */
        return (-1);
    }
    else
    {
        /* success to open */
        total_line = 0;
        
        /* parsing file, searching for EOL to count line number */
        do
        {
            c = fgetc(fp);
            if (EOL == c)
            {
                total_line++;
            }
        } while (c != EOF);
        
        /* close file */
        fclose(fp);
    }
    
    return total_line;
}
