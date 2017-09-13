#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

uint8_t * dec2bin(uint8_t *size, uint32_t tmp_number);
uint8_t consecutive_one(uint8_t *size, uint8_t tmp_bin[]);

int main(){
    int n;
    scanf("%d",&n);

    while ((n < 1) || (n > 1000000))
    {
        scanf("%d", &n);
    }

    uint8_t *bin, *n_size;

    bin = dec2bin(&n_size, n);

    printf("%d\n", consecutive_one(n_size, bin));

    return 0;
}

uint8_t * dec2bin(uint8_t *size, uint32_t tmp_number)
{
    uint8_t i;
    uint16_t remainder;
    static uint8_t bin[100];

    i = 0;
    bin[0] = 0;

    while (tmp_number != 0)
    {
        remainder = tmp_number % 2;
        tmp_number = tmp_number /2;
        bin[i] = remainder;
        i++;
    }

    *size = i;

    return bin;

}

uint8_t consecutive_one(uint8_t *size, uint8_t tmp_bin[])
{
    uint8_t i, j;
    uint8_t tmp_cnt;
    uint8_t cnt;

    i = 0;
    j = 0;
    tmp_cnt = 0;
    cnt = 1;

    /* count no of consecutive one's */
    while (i < *size)
    {
        if (1 == tmp_bin[i])
        {
            for (j = i; j < *size; j++)
            {
                if (0 == tmp_bin[j])
                {
                    tmp_cnt = j - i;
                    if (tmp_cnt >= cnt)
                    {
                        cnt = tmp_cnt;
                    }
                    break;
                }
            }
            i = i + tmp_cnt;
        }
        else
        {
            i = i + 1;
        }
    }

    return cnt;
}

