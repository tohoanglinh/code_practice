/* Diagonal Difference */

#include <stdio.h>
#include <stdlib.h>

/* print out or display matrix */
void matrix_print(int size, int **matrix)
{
    int i, j;
    printf("-----------------------------\n");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("-----------------------------\n");
}

/* return absolute value of an integer number */
unsigned int absolute(int a)
{
    if (a > 0)
    {
        return a;
    }
    else
    {
        return (0 - a);
    }
}

int main(void)
{
    /*given a square matrix of size NxN, calculate absolute difference between sums of its diagonals*/
    /*input: a single integer N*/
    /*input: matrix's rows and columns*/
    int N, i,j;
    scanf("%d", &N);
    int **a;

    /*allocate the array matrix*/
    a = (int**)malloc(N*sizeof(int*));
    
    for (i = 0; i < N; i++)
    {
        a[i] = (int*)malloc(N*sizeof(int));
    }
    
    /*get element matrix values*/
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            scanf(" %d", &a[i][j]);
            if ((N-1) == j)
            {
                break;
            }
        }
    }
    
    /*primary diagonal*/
    int pd;
    pd = 0;
    i = 0;
    while (i < N)
    {
        pd = pd + a[i][i];
        i++;
    }

    /*secondary diagonal*/
    int sd;
    sd = 0;
    i = 0;
    j = N-1;
    while (i < N)
    {
        sd = sd + a[i][j];
        i++;
        j--;
    }

    /*difference between diagonals*/
    printf("%d", absolute(pd-sd));
    
    /*deallocate the array matrix*/
    for (i = 0; i < N; i++)
    {
        free(a[i]);
    }
    free(a);
    return 0;
}
