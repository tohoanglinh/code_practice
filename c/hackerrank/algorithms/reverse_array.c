#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /*
     * Array Reversal
     */

    /* Local variable declaration */
    int size_arr;
    int *arr;
    int i;

    scanf("%d", &size_arr);

    arr = (int *)malloc(sizeof(int)*size_arr);

    for (i = 0; i < size_arr; i++)
    {
        scanf(" %d", arr+i); 
    }

    // printf("Array Reversal\n");

    // for (i = 0; i < size_arr; i++)
    // {
    //     printf(" %d", *(arr+i));
    // }
    // printf("\n");

    for (i = (size_arr-1); i >= 0; i--)
    {
        printf("%d ", *(arr+i));
    }
    printf("\n");

    free(arr);

     return 0;
}