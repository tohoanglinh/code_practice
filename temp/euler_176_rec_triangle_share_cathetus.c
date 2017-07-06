#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/**
 *  Input :
 *      + integer q - no of queries
 *      + followed by an integer n
 *  Output:
 */

typedef struct
{
    int c1;
    int c2;
    int h;
} triangle_t;

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    unsigned long q;
    unsigned long n;
    
    scanf("%lu", &q);
    
    while ((q < 1) || (q > 250000))
    {
        scanf("%lu", &q);
    }
    
    // 1 <= n <= 1000000
    n = 4;
    
    // tim canh chung cua n=4 tam giac vuong --> catheti = com_leg = 12;
    int com_leg;
    int i;
    
    triangle_t tri[n];
    
    for (i = 0; i < n; i++)
    {
        tri[i].c1
    }
    
    c1^2 + c^2 = h1^2
    c2^2 + c^2 = h2^2
    c3^2 + c^2 = h3^2
    c4^2 + c^2 = h4^2
    
    //tim c
    
    
    //printf("%lu", q);

    
    return 0;
}

