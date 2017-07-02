/*Mini-Max-Sum*/
#include <stdio.h>

int main(void)
{
    /*input: a single line of 5 space-separated integers*/
    int N, index;
    long int a[N];
    long int sum;
    sum = 0;
    N = 5;
    for (index = 0; index < N; index++)
    {
        scanf(" %ld", &a[index]);
        if (a[index] < 1 || a[index] > 1000000000)
        {
            scanf("Re-enter that number pls: %ld", &a[index]);
        }
        sum = sum + a[index];
    }
    printf("%ld", sum);
    /*input constraints: each integer is in the inclusive range[1, 109]*/
    /*output: 2 space-separated long integers, min and max values*/    
    long int partial_sum[N];
    for (index = 0; index < N; index++)
    {
        partial_sum[index] = sum - a[index];
    }
    
    return 0;
}
