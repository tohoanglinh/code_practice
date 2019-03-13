#include <stdio.h>

int sum_digits(int num)
{
    int sum = 0;

    while (num > 0)
    {
        sum += num % 10;
        num = num / 10;
    }

    return sum;
}

int main(void)
{
    int a_five_digit_number = 0;

    while ((10000 > a_five_digit_number) || (99999 < a_five_digit_number))
    {
        scanf("%d", &a_five_digit_number);
    }

    /* Sum of digits of a Five Digit Number */
    printf("%d\n", sum_digits(a_five_digit_number));

    return 0;
}