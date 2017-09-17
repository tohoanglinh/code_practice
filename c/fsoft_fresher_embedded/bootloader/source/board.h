/*
 * board.h
 *
 *  Created on: Mar 4, 2017
 *      Author: linhth8
 */

/**
 * @file      board.h
 * @developer LinhTH8
 * @mentor
 * @topic     MCP_BOARD
 * @requires..FRDM-KL46Z
 */

#ifndef SOURCES_BOARD_H_
#define SOURCES_BOARD_H_

#include "MKL46Z4.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* HARDWARE */
/* LED */
#define RED_LED_GPIO GPIOE
#define RED_LED_PIN 29
#define GREEN_LED_GPIO GPIOD
#define GREEN_LED_PIN 5

/* SWITCH BUTTON */
#define SW1_GPIO GPIOC
#define SW1_PIN 3
#define SW2_GPIO GPIOC
#define SW2_PIN 12

/* UART */
#define UART0_TX_PORT PORTA
#define UART0_TX_PIN 2
#define UART0_RX_PORT PORTA
#define UART0_RX_PIN 1

#define UART1_TX_PORT PORTA
#define UART1_TX_PIN 1
#define UART1_RX_PORT PORTA
#define UART1_RX_PIN 2

#define UART2_TX_PORT PORTA
#define UART2_TX_PIN 1
#define UART2_RX_PORT PORTA
#define UART2_RX_PIN 2

/*******************************************************************************
 * API
 ******************************************************************************/

#endif /* SOURCES_BOARD_H_ */
