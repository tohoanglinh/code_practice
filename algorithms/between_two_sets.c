/* Between Two Sets */
/* Challenge: Algorithms--Implementation */

#include <stdio.h>
#include <stdlib.h>

int find_max_value(int arr[], int size_arr)
{
    int index;
    int max;
    max = arr[0];
    for(index = 1; index < size_arr; index++)
    {
        if (max < arr[index])
        {
            max = arr[index];
        }
    }
    return max;
}

int find_min_value(int arr[], int size_arr)
{
    int index;
    int min;
    min = arr[0];
    for(index = 1; index < size_arr; index++)
    {
        if (min > arr[index])
        {
            min = arr[index];
        }
    }
    return min;
}

int find_between(int a[], int size_a, int b[], int size_b)
{
    /* x >= max(a), x <= min(b) */
    int max;
    max = find_max_value(a, size_a);
    int min;
    min = find_min_value(b, size_b);

    int x;
    int i;
    int found_cnt;
    found_cnt = 0;
    int test_a, test_b;
    test_a = 0;
    test_b = 0;

    for (x = max; x <= min; x++)
    {
        for (i = 0; i < size_a; i++)
        {
            if (x % a[i] == 0)
            {
                test_a = 1;
            }
            else
            {
                test_a = 0;
                break;
            }
        }
        for (i = 0; i < size_b; i++)
        {
            if (b[i] % x == 0)
            {
                test_b = 1;
            }
            else
            {
                test_b = 0;
                break;
            }
        }
        if ((1 == test_a) && (1 == test_b))
        {
            /* found x, increase counter found */
            //printf("Found the between number is %d\n", x);
            found_cnt++;
        }
    }

    return found_cnt;
}

int main(void)
{
    /* input: no of elements in set A and B */
    int i, n, m;
    n = 0;
    m = 0;
    while ((n < 1) || (n > 10) || (m < 1) || (m > 10))
    {
        scanf("%d %d", &n, &m);
    }

    int *a;
    int *b;
    a = (int*) malloc(n*sizeof(int));
    b = (int*) malloc(m*sizeof(int));

    for(i = 0; i < n; i++)
    {
        scanf(" %d", a+i);
    }

    for (i = 0; i < m; i++)
    {
        scanf(" %d", b+i);
    }

    /* output: no of integers that are considered to be between A and B */
    printf("%d", find_between(a, n, b, m));

    free(b);
    free(a);

    return 0;
}
