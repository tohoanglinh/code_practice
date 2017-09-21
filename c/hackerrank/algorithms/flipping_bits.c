/**
 * File   : flipping_bits.c
 * Author : To Hoang Linh
 * Date   : 2017-09-20
 * ForWhat: Given a list of 32 bits unsigned integers. You are required to output
 * the list of the unsigned integers you get by flipping bits in its binary representation
 * (i.e., unset bits must be set, and set bits must be unset).
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
unsigned char flip1bit(unsigned long bit);
unsigned long flipallbits(unsigned long num);
unsigned long *dec2bin(unsigned long decimal);
unsigned long bin2dec(unsigned long *binary);

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_T 100

/*******************************************************************************
 * Code
 ******************************************************************************/
unsigned long flipallbits(unsigned long num)
{
    int i;
    unsigned long *binary;
    unsigned long *flipped_binary;
    binary = malloc(sizeof(unsigned long)*32);
    flipped_binary = malloc(sizeof(unsigned long)*32);

    /* convert decimal to binary in array */
    binary = dec2bin(num);

    /* flipping bits */
    for (i = 31; i >= 0; i--)
    {
        flipped_binary[i] = flip1bit(binary[i]);
    }

    /* convert binary array to decimal */
    unsigned long result = bin2dec(flipped_binary);

    free(flipped_binary);

    return result;
}

unsigned char flip1bit(unsigned long bit)
{
    if (1 == bit)
    {
        return 0;
    }
    else if (0 == bit)
    {
        return 1;
    }
    else
    {
        return (-1);
    }
}

unsigned long *dec2bin(unsigned long decimal)
{
    static unsigned long bit[32];
    int i;
    int quotient;

    /* reset bit element to zeros
    * Please do not use memset. memset is for character
    * here is unsigned long --> clear manually
    */
    for (i = 0; i < 32; i++)
    {
        bit[i] = 0;
    }

    i = 0;
    /* convert decimal to binary number in array format */
    while (decimal > 0)
    {
        bit[i] = decimal % 2;
        i++;
        quotient = decimal / 2;
        decimal = quotient;
    }
    return bit;
}

unsigned long bin2dec(unsigned long *binary)
{
    int i;
    unsigned long decimal;
    decimal = 0;
    for (i = 31; i >= 0; i--)
    {
        decimal = decimal + binary[i]*pow(2,i);
    }
    return decimal;
}

int main(void)
{
    /* input T: list size */
    int T;
    T = 0;
    while (T < 1 || T > MAX_T)
    {
        scanf("%d", &T);
    }

    unsigned long *num;
    num = malloc(sizeof(unsigned long)*T);

    int i;
    for (i = 0; i < T; i++)
    {
        scanf("%lu", num+i);
    }

    /* output */
    for (i = 0; i < T; i++)
    {
        printf("%lu\n", flipallbits(*(num+i)));
    }

    free(num);
    return 0;
}
