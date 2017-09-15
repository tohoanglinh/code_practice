#include <stdio.h>
#include <stdint.h>

#define SEED1 1
#define SEED2 2

uint8_t main(void)
{
    uint16_t fib[10];
    uint8_t i;

    printf("Fibonacci Numbers:\n");

    fib[0] = SEED1;
    fib[1] = SEED2;

//    printf("\nSize of Fib = %d (bytes)", sizeof(fib));
//    printf("\nSize of Fib = %d (elements)", sizeof(fib) / sizeof(uint16_t));
//    printf("\nEach element = %d (bytes)", sizeof(uint16_t));
//    getch();

    printf("%d\t%d\t", fib[0], fib[1]);
    /* fib(n) = fib(n-1) + fib(n-2)     if n > 2, n is integer */
    for (i = 2; i < sizeof(fib) / sizeof(uint16_t); i++)
    {
        fib[i] = fib[i-1] + fib[i-2];
        printf("%d\t", fib[i]);
    }

    return 0;
}
