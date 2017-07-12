/* plus-minus */
#include <stdio.h>

int main(void)
{
    /*input: the 1st line contains an integer, N, size of the array*/
    int N;
    scanf("%d", &N);

    /*input: the 2nd line contains N space-separated integers (a0, a1...)*/
    int *a;
    a = malloc(N*sizeof(int));
    if (a == NULL)
    {
        return (-1);
    }
    int index;
    for (index = 0; index < N; index++)
    {
        scanf(" %d", &a[index]);
    }

    /*output: fraction: positive, negative, zeroes*/
    int cnt_positive;
    cnt_positive = 0;
    int cnt_negative;
    cnt_negative = 0;
    int cnt_zeroes;
    cnt_zeroes = 0;
    for (index = 0; index < N; index++)
    {
        if (a[index] > 0)
        {
            cnt_positive++;
        }
        if (a[index] < 0)
        {
            cnt_negative++;
        }
        if (a[index] == 0)
        {
            cnt_zeroes++;
        }
    }
    printf("%.6f\n", (float)(cnt_positive)/(float)(N));
    printf("%.6f\n", (float)(cnt_negative)/(float)(N));
    printf("%.6f\n", (float)(cnt_zeroes)/(float)(N));
    return 0;
}
