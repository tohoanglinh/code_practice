/*Mini-Max-Sum*/
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /*input: a single line of 5 space-separated integers*/
    /*input constraints: each integer is in the inclusive range[1, 10^9]*/
    int N, index;
    long int *a;
    long int sum;
    sum = 0;
    N = 5;
    a = (long int*)malloc(N*sizeof(long int));
    for (index = 0; index < N; index++)
    {
        scanf(" %ld", &a[index]);
        if (a[index] < 1 || a[index] > 1000000000)
        {
            scanf("Re-enter that number pls: %ld", &a[index]);
        }
        sum = sum + a[index];
    }
    /*output: 2 space-separated long integers, min and max values*/    
    long int *partial_sum;
    long int min, max;
    partial_sum = (long int*)malloc(N*sizeof(long int));
    partial_sum[0] = sum - a[0];
    min = partial_sum[0];
    max = partial_sum[0];
    for (index = 1; index < N; index++)
    {
        partial_sum[index] = sum - a[index];
        if (max < partial_sum[index])
        {
            max = partial_sum[index];
        }
        if (min > partial_sum[index])
        {
            min = partial_sum[index];
        }
    }
    printf("%ld %ld", min, max);
    
    /*deallocate pointers*/
    free(partial_sum);
    free(a);
    
    return 0;
}
