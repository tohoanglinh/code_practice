#include <stdio.h>

int main(void)
{
    /* input: T number of test cases */
    int T;
    scanf("%d", &T);

    int i;
    int *N;
    N = malloc(sizeof(int)*T);
    for (i = 0; i < T; i++)
    {
        scanf("%d", N+i);
    }

    /* output */

    return 0;
}