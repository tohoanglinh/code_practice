#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int factorial(int N)
{
    if (1 == N)
    {
        return 1;
    }
    else
    {
        return (N * factorial(N-1));
    }
}

int main(void)
{
    int N;

    scanf("%d", &N);

    if ((N >= 2) && (N <= 12))
    {
        printf("%d", factorial(N));
    }
    return 0;
}
