#include <stdio.h>
#include <stdlib.h>

int summation(int *arr, int sizeArr)
{
    int index;
    int sum = 0;

    for (index = 0; index < sizeArr; index++)
    {
        sum = sum + *(arr+index);
    }

    return sum;
}

int main(void)
{
    /* integer number n */
    int n;

    scanf("%d", &n);

    int i;
    int *a;
    a = (int *)malloc(sizeof(int)*n);

    for (i = 0; i < n; i++)
    {
        scanf(" %d", a+i);
    }

    printf("%d", summation(a, n));
    free(a);
    return 0;
}
