/*
 * File   : tin_hoc_dai_cuong.c
 * Author : To Hoang Linh
 * Date   : 2017-07-10
 * ForWhat: Viet chuong trinh tnhap vao 1 day so thuc
 * x1, x2, ..., xn
 * S = tong (log_2 i+3/|x_i|)
 */

/**
 * INCLUDES
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * DEFINES & MACROS
 */
#define MAX_CNT 200

uint16_t sum(uint16_t *arr, uint8_t size_arr)
{
    uint16_t sum;
    sum = 0;
    uint8_t index;

    for (index = 0; index < size_arr; index++)
    {
        sum += *(arr + index);
    }
    return sum;
}

int main(void)
{
    /* input */
    int n;
    printf("Input total number\n");
    scanf("%d", &n);

    // uint8_t i;
    // uint16_t *x;
    // x = malloc(n*sizeof(uint16_t));
    // for (i = 0; i < n; i++)
    // {
    //     scanf(" %hd", x+i);
    // }

    // sum(x, n);

    // /* output */
    // free(x);
    return 0;
}
