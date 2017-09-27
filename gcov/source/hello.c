#include "hello.h"
#include "mathlib.h"

int main(void)
{
    int i;
    i = 1;
    printf("(1)hello\n");
    if (i == 1)
    {
        printf("(2)i = %d, MAX = %d\n", i, MAX);
        printf("sum(i + MAX) = %d\n", sum(i, MAX));
    }
    else
    {
        printf("(3)N/A");
    }
    return 0;
}