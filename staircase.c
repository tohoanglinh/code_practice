/* Staircase */
#include <stdio.h>

int main(void)
{
    /*input: a single integer, n, size of staircase*/
    int n;
    scanf(" %d", &n);

    /*output: a staircase, made up from symbol #*/
    int row, col;
    row = 1;
    while (row <= n)
    {
        for (col = 1; col <= (n-row); col++)
        {
            printf(" ");
        }
        for (col = (n-row); col <= n; col++)
        {
            printf("#");
        }
        printf("\n");
        row++;
    }

    return 0;
}
