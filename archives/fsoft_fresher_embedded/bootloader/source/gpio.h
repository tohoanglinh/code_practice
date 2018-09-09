/*
 * gpio.h
 *
 *  Created on: Mar 4, 2017
 *      Author: linhth8
 */

/**
 * @file      gpio.h
 * @developer LinhTH8
 * @mentor    PhongLH
 * @topic     MCP_GPIO
 */

#ifndef SOURCES_GPIO_H_
#define SOURCES_GPIO_H_

#include "MKL46Z4.h"
#include "board.h"
#include "misc.h"
/*****************************************************************************
 * DEFINES
 *****************************************************************************/
/* defines to control LED states */
#define RED_LED_ON (RED_LED_GPIO->PCOR |= (1 << RED_LED_PIN))
#define RED_LED_OFF (RED_LED_GPIO->PSOR |= (1 << RED_LED_PIN))
#define RED_LED_TOGGLE (RED_LED_GPIO->PTOR |= (1 << RED_LED_PIN))
#define GREEN_LED_ON (GREEN_LED_GPIO->PCOR |= (1 << GREEN_LED_PIN))
#define GREEN_LED_OFF (GREEN_LED_GPIO->PSOR |= (1 << GREEN_LED_PIN))
#define GREEN_LED_TOGGLE (GREEN_LED_GPIO->PTOR |= (1 << GREEN_LED_PIN))

/* defines to recognize SW states
 * POOL: 0 PRESSED, 1 UNPRESSED
 * ISFR: 1 PRESSED, 0 UNPRESSED */
#define SW1_PRESSED_POOL   ((SW1_GPIO->PDIR >> SW1_PIN) & 1)
#define SW1_PRESSED_ISFR   ((PORTC->ISFR >> SW1_PIN) & 1)
#define SW2_PRESSED_POOL   ((SW2_GPIO->PDIR >> SW2_PIN) & 1)
#define SW2_PRESSED_ISFR   ((PORTC->ISFR >> SW2_PIN) & 1)

/*****************************************************************************
 * API
 *****************************************************************************/
/*!
 * @brief initialize and configure pin as GPIO input or output
 *        port control and interrupt
 * @param *base struct GPIO_Type, ex: GPIOA.
 * @param pin pin number, ex: 2.
 * @param direction direction of pin, ex: in~1, out~0.
 *        --> ex: PTA2 as input GPIO_Init(GPIOA, 2, 1)
 *        --> ex: PTE5 as output GPIO_Init(GPIOE, 5, 0)
 * @return none
 */
void GPIO_Init(GPIO_Type* base, uint8_t pin, uint8_t direction);

/*!
 * @brief write data (value) to Port[pin]
 *
 * @param *base struct GPIO_Type, ex: GPIOA.
 * @param pin pin number, ex: 2.
 * @param value value to write 0 or 1 (voltage level)
 *        --> ex: write 1 out to PTA2: GPIO_Write_Out(GPIOA, 2, 1)
 *        --> ex: write 0 out to PTE5: GPIO_Write_Out(GPIOE, 5, 0)
 * @return none
 */
void GPIO_Write(GPIO_Type* base, uint8_t pin, uint8_t value);

/*!
 * @brief initialize and configure pin as GPIO input or output
 *
 * @param *base struct GPIO_Type, ex: GPIOA.
 * @param pin pin number, ex: 2.
 *        --> ex: Read PTA2 as input: GPIO_Read_In(GPIOA, 2)
 *        --> ex: Read PTE5 as input: GPIO_Read_In(GPIOE, 5)
 * @return none
 */
uint8_t GPIO_Read(GPIO_Type* base, uint8_t pin);

#endif /* SOURCES_GPIO_H_ */
