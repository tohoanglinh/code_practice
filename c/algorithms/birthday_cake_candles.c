/* Birthday Cake Candles */
#include <stdio.h>
#include <stdlib.h>

int max_in_array(int *arr, int size_arr)
{
    int max, i;
    max = arr[0];
    for (i = 0; i < size_arr; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    return max;
}

int cnt_max_in_array(int *arr, int size_arr)
{
    int cnt, i, max;
    cnt = 0;
    
    max = max_in_array(arr, size_arr);
    
    for (i = 0; i < size_arr; i++)
    {
        if (arr[i] == max)
        {
            cnt++;
        }
    }
    return cnt;
}

int main(void)
{
    /*input: n - number of candles on the cake*/
    int n;
    scanf(" %d", &n);
    while (n < 1 || n > 100000)
    {
        scanf(" %d", &n);
    }
    
    /*input: n space-separated integers height[i]*/
    int *height;
    height = (int *)malloc(n * sizeof(int));
    int i;
    
    for (i = 0; i < n; i++)
    {
        scanf(" %d", &height[i]);
    }

    /*output: number of tallest candles*/
    int tallest;

    tallest = max_in_array(height, n);

    int cnt_tallest;

    cnt_tallest = cnt_max_in_array(height, n);
    
    printf("%d\n", cnt_tallest);

    return 0;
}
