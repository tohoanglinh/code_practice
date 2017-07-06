#include <stdio.h>
#include <string.h>

void DecToBin(int dec_num)
{
    int bit[100], quotient, i;
    i = 0;
    /* convert decimal to binary number */
    while (dec_num > 0)
    {
        bit[i] = dec_num % 2;
        i++;
        quotient = dec_num / 2;
        dec_num = quotient;
    }
    int cnt_num;
    cnt_num = i;
    /* display binary number */
    while (i > 0)
    {
        printf("%d", bit[i-1]);
        i--;
    }
    /* count number of consecutive 1's */
    /* bit[2] bit[1] bit[0] */
    int cnt_sec_one;
    cnt_one = 0;
    int j;
    for (j = 0; j < cnt_num; j++)
    {
        if (bit[j] == 1)
        {
            cnt_sec_one++;
        }
    }
    printf("\nnumber of one's = %d", cnt_sec_one);
}

int main(void)
{
    int n;
    scanf("%d", &n);

    DecToBin(n);

    return 0;
}
