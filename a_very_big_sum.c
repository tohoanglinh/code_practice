/* A Very Big Sum */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /*input: integer N, next line: N integers in array*/
    int N, i;
    scanf(" %d", &N);
    while (N < 1 || N > 10)
    {
        scanf(" %d", &N);
    }
    long long int *A;
    A = (long long int*) malloc(N*sizeof(long long int));

    for (i = 0; i < N; i++)
    {
        scanf(" %lld", &A[i]);
    }

    /*output: sum of the elements in the array*/
    long long int sum;
    sum = 0;
    for (i = 0; i < N; i++)
    {
        sum = sum + A[i];
    }

    printf("%lld", sum);

    free(A);

    return 0;
}
