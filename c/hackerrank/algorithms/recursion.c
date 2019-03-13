#include <stdio.h>

int nth_term(int n, int a, int b, int c)
{
    int result = 0;

    switch (n)
    {
        case 1:
            result = a;
            break;
        case 2:
            result = b;
            break;
        case 3:
            result = c;
            break;
        default:
            result = nth_term(n-1, a, b, c)+ nth_term(n-2, a, b, c)+ nth_term(n-3, a, b, c);
            break;
    }

    return result;
}

int main(void)
{
    int integer_number;
    int a, b, c;

    scanf("%d", &integer_number);
    scanf("%d %d %d", &a, &b, &c);

    // printf("integer_number = %d\n", integer_number);
    // printf("a = %d; b = %d; c = %d\n", a, b, c);

    printf("%d\n", nth_term(integer_number, a, b, c));

    return 0;
}