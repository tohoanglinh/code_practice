/* The Hurdle Race -----------------------------------------------------------
 * Dan is playing a video game in which his character competes in a hurdle
 * race by jumping over n hurdles with heights, h0, h1, ..., hn-1. He can
 * initially jump a maximum height of k units, but he has an unlimited supply
 * of magic beverages that help him jump higher! Each time Dan drinks a magic
 * beverage, the maximum height he can jump during the race increases by 1 unit.
 * Given n, k, and the heights of all the hurdles, find and print the minimum
 * number of magic beverages Dan must drink to complete the race.
 */
#include <stdio.h>
#include <stdlib.h>

int max(int arr[], int size_arr)
{
    int i;
    int max;
    max = arr[0];
    for (i = 0; i < size_arr; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int main(void)
{
    /* n: number of hurdles, k: max height without beverages */
    int n, k;
    scanf("%d %d", &n, &k);

    /* n space-separated integers h0, h1, ..., hn-1 */
    int i;
    int *height;
    height = malloc(n*sizeof(int));
    if (NULL == height)
    {
        return (-1);
    }
    for (i = 0; i < n; i++)
    {
        scanf(" %d", height+i);
    }

    /* output: min of beverages that Dan must drink to complete race */
    int min;
    if (max(height,n) > k)
    {
        min = max(height,n) - k;
    }
    else
    {
        min = 0;
    }

    printf("%d", min);

    free(height);
    return 0;
}
