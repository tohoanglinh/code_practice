/**
 * File   : beautiful_days_at_the_movies.c
 * Author : To Hoang Linh
 * Date   : 2017-08-24
 * ForWhat: Lily likes to play games with integers and their reversals. For some
 * integer x, we define reversed(x) to be the reversal of all digits in x. For
 * example, reversed(123)=321, reversed(21)=12, and reversed(120)=21.
 * Logan wants to go to the movies with Lily on some day x satisfying i <= x <=j,
 * but he knows she only goes to the movies on days she considers to be beautiful.
 * Lily considers a day to be beautiful if the absolute value of the difference
 * between x and reversed(x) is divisible by k.
 * Given i, j and k, print the number of beautiful days when Logan and Lily can
 * go to the movies.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
int getLength(int num)
{
    int tmp_len = 0;

    while(num/10 != 0)
    {
        tmp_len++;
        num = num/10;
    }
    
    if (num/10 == 0)
    {
        tmp_len++;
    }
    return tmp_len;
}

int reversed(int num, int len)
{
    int new_num = 0;
    int remain;
    int idx;
    idx = len-1;

    while(num/10 != 0)
    {
        remain = num%10;
        new_num = new_num + remain*pow(10,idx);
        num = num/10;
        idx--;
    }
    
    if(num/10 == 0)
    {
        new_num = new_num+num%10;
    }
    
    return new_num;
}
 
int main(void)
{
    /* input: i, j, k */
    int i, j, k;
    scanf("%d %d %d", &i, &j, &k);
    
    /* output
       x tu i --> j
      |x - reversed(x)| % k == 0  */
    int x;
    int beautiful_cnt = 0;
    for (x = i; x < j; x++)
    {
        /* find beautiful days */
        if (abs(x-reversed(x,getLength(x))) % k == 0)
        {
            /* that's a beautiful day */
            beautiful_cnt++;
        }
    }
    
    printf("%d", beautiful_cnt);
    
    return 0;
}
