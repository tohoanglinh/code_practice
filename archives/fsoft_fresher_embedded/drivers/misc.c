/*
 * misc.c
 *
 *  Created on: Mar 4, 2017
 *      Author: linhth8
 */

/**
 * @file      misc.c
 * @developer LinhTH8
 * @mentor
 * @topic     MCP_MISC
 * @requires
 */

#include "misc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/**
 * @detail: generate a delay without accuracy requirement.
 *          suspend execution of a program for a particular time.
 * @how-to: delay(1000000);
 */
void delay(uint32_t delay_cnt)
{
    uint32_t i;

    for (i = 0; i < delay_cnt; i++)
    {
        __asm("nop");
    }
}

/**
 * @detail: convert a number to a string.
 *          which represents a binary string.
 *          Goal is to printf in binary format.
 * @how-to: printf("%s", byte_to_binary(number));
 */
const char *byte_to_binary(uint8_t x)
{
    static char b[9];
    b[0] = '\0';

    uint8_t z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

/**
 * @detail: set bit at bit_position of number to 1.
 *          bit_position is counted from 0
 * @how-to: BIT_Set(10010101, 3) --> 10011101
 */
uint8_t BIT_Set(uint8_t number, uint8_t bit_position)
{
    return (number |= (1 << bit_position));
}

/**
 * @detail: clear bit at bit_position of number to 0.
 */
uint8_t BIT_Clear(uint8_t number, uint8_t bit_position)
{
    return (number &= ~(1 << bit_position));
}

/**
 * @detail: toggle bit at bit_position of number.
 */
uint8_t BIT_Toggle(uint8_t number, uint8_t bit_position)
{
    return (number ^= (1 << bit_position));
}

/**
 * @detail: set bit at bit_position of number to 1 or 0.
 */
uint8_t BIT_SetToX(uint8_t number, uint8_t bit_position, uint8_t value)
{
    /* value is 1 or 0 only */
    if ((value == 0) || (value == 1))
    {
        return (number ^= (-value ^ number) & (1 << bit_position));
    }
    else
    {
        return EXIT_FAILURE;
    }
}

/**
 * @detail: config interrupt priority level and enable interrupt
 */
void NVIC_Config(IRQn_Type irq_type, uint8_t irq_priority_level)
{
  /* set priority of interrupts */
  NVIC_SetPriority(irq_type, irq_priority_level);

  /* clear pending (awaiting) nvic irq */
  NVIC_ClearPendingIRQ(irq_type);

  /* enable interrupts */
  NVIC_EnableIRQ(irq_type);
}