/*
 * gpio.c
 *
 *  Created on: Mar 4, 2017
 *      Author: linhth8
 */

/**
 * @file      gpio.c
 * @developer LinhTH8
 * @mentor    PhongLH
 * @topic     MCP_GPIO
 */

#include "gpio.h"
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void PORTC_PORTD_IRQHandler(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
Boolean g_flag_sw1_irq;
Boolean g_flag_sw2_irq;

/*****************************************************************************
 * FUNCTIONs
 *****************************************************************************/
void GPIO_Init(GPIO_Type* base, uint8_t pin, uint8_t direction)
{
    PORT_Type* port;

    /* enable clock */
    if (base == GPIOA)
    {
        SIM->SCGC5 |= SIM_SCGC5_PORTA(1);
        port = PORTA;
    }
    else if (base == GPIOB)
    {
        SIM->SCGC5 |= SIM_SCGC5_PORTB(1);
        port = PORTB;
    }
    else if (base == GPIOC)
    {
        SIM->SCGC5 |= SIM_SCGC5_PORTC(1);
        port = PORTC;
    }
    else if (base == GPIOD)
    {
        SIM->SCGC5 |= SIM_SCGC5_PORTD(1);
        port = PORTD;
    }
    else if (base == GPIOE)
    {
        SIM->SCGC5 |= SIM_SCGC5_PORTE(1);
        port = PORTE;
    }

    /* configure mux mode as GPIO */
    port->PCR[pin] |= PORT_PCR_MUX(1);

    /* configure direction as output (0) or input (1) */
    if (direction == 0)
    {
        base->PDDR |= (1 << pin);

        /* reset clear pin output */
        base->PCOR |= (1 << pin);
    }
    else if (direction == 1)
    {
        base->PDDR &= ~(1 << pin);

        /* enable pull up resistor */
        port->PCR[pin] |= PORT_PCR_PE(1);
        port->PCR[pin] |= PORT_PCR_PS(1);

        /* configure interrupts/DMA requests
         * ---------------------------------------
         * Page 194(RM)
         * 0000 Interrupt/DMA request disabled
         * 0001 DMA request on rising edge.
         * 0010 DMA request on falling edge.
         * 0011 DMA request on either edge.
         * 1000 Interrupt when logic zero.
         * 1001 Interrupt on rising edge.
         * 1010 Interrupt on falling edge.
         * 1011 Interrupt on either edge.
         * 1100 Interrupt when logic one
         * ---------------------------------------
         * a falling edge = high-to-low transition
         * a rising  edge = low-to-high transition
         */
        port->PCR[pin] |= PORT_PCR_IRQC(10); /* falling edge */
    }
}

void GPIO_Write(GPIO_Type* base, uint8_t pin, uint8_t value)
{
    if (value == 0)
    {
        base->PCOR |= (1 << pin);
    }
    else
    {
        base->PSOR |= (1 << pin);
    }
}

uint8_t GPIO_Read(GPIO_Type* base, uint8_t pin)
{
    if (base->PDIR & (1 << pin))
    {
        return 1;
    }
    return 0;
}

void PORTC_PORTD_IRQHandler(void)
{
    /* check interrupt source is SW1 (PTC3) ? */
    if (SW1_PRESSED_ISFR)
    {
      /* set software flag for sw1 */
      g_flag_sw1_irq = TRUE;
    }

    /* check interrupt source is SW2 (PTC12) ? */
    if (SW2_PRESSED_ISFR)
    {
      /* set software flag for sw2 */
      g_flag_sw2_irq = TRUE;
    }

    /* must clear interrupt flag, set 1 to clear */
    PORTC->ISFR |= (1 << SW1_PIN);
    PORTC->ISFR |= (1 << SW2_PIN);
}
