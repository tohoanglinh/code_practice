/**
 * File   : drawing_book.c
 * Author : To Hoang Linh
 * Date   : 2017-08-28
 * ForWhat: Brie's Drawing teacher asks her class to open their n-page book
 * to page number p. Brie can either start tuning pages from the front of the
 * book (i.e., page number 1) or from the back of the book (i.e., page number n)
 * and she always turns page one-by-one (as opposed to skipping through multiple
 * pages at once). When she opens the book, page 1 is always on the right side.
 * Each page in the book has 2 sides, front and back, except for the last page
 * which may only have a front side depending on the total number of pages of
 * the book. Given n and p, print the minimum number of pages Brie must turn in
 * order to arrive at page p.
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
#define MAX_PAGES 100000
#define MIN_PAGES 1

/*******************************************************************************
 * Code
 ******************************************************************************/
int forward_turn(int total_pages, int wanted_page)
{
    return 2;
}

int reverse_turn(int total_pages, int wanted_page)
{
    return 1;
}

int min(int num1, int num2)
{
    return (num1 > num2 ? num2 : num1);
}
 
int main(void)
{
    /* input n: number of pages in the book */
    int n;
    n = 0;
    while (n < MIN_PAGES || n > MAX_PAGES)
    {
        scanf("%d", &n);
    }

    /* input p: the page that Brie's teacher wants her to turn to */
    int p;
    p = 0;
    while (p < MIN_PAGES || p > n)
    {
        scanf("%d", &p);
    }
    
    /* output */
    printf("%d", min(forward_turn(n,p), reverse_turn(n,p)));
    
    return 0;
}
