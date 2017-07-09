/** 
 * Divisible Sum Pairs
 * Challenge: Algorithms--Implementation
 * To Hoang Linh
 **/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* input: n, k */
    int n, k;
    scanf("%d %d", &n, &k);
    int i,j;
    int *a;
    a = (int*)malloc(n*sizeof(int));
    for (i=0; i<n; i++)
    {
        scanf(" %d", &a[i]);
    }

    /* output: no of pairs divisible by k */
    int cnt;
    cnt = 0;
    for (i=0; i<n; i++)
    {
        for (j=i+1; j<n; j++)
        {
            if ((a[i] + a[j]) % k == 0)
            {
                cnt++;
            }
        }
    }
    printf("%d", cnt); 
    return 0;
}
