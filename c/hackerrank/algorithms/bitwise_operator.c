#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.

void calculate_the_maximum(int n, int k) {
  //Write your code here.
    /* S = {1, 2, 3, 4, 5...,n} */
    int a, b;
    int and, newAnd;
    int or, newOr;
    int xor, newXor;
    int i;
    int *sum = (int *)malloc(n*sizeof(int));

    for (i = 0; i < n; i++)
    {
        sum[i] = i+1;
    }

    and = 0;
    or = 0;
    xor = 0;

    for (a = 0; a < (n-1); a++)
    {
        for (b = a + 1; b < n; b++)
        {
            newAnd = sum[a] & sum[b];
            newOr = sum[a] | sum[b];
            newXor = sum[a] ^ sum[b];
            if ((newAnd < k) && (newAnd > and))
            {
                and = newAnd;
            }
            if ((newOr < k) && (newOr > or))
            {
                or = newOr;
            }
            if ((newXor < k) && (newXor > xor))
            {
                xor = newXor;
            }
        }
    }

    /* MAX AND */
    printf("%d\n", and);
    /* MAX OR */
    printf("%d\n", or);
    /* MAX XOR */
    printf("%d\n", xor);

    free(sum);
}

int main() {
    int n, k;

    scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);

    return 0;
}
