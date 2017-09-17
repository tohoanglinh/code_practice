/*
 * uart.h
 *
 *  Created on: Mar 4, 2017
 *      Author: linhth8
 */

/**
 * @file      uart.h
 * @developer LinhTH8
 * @mentor    HaiND1
 * @topic     MCP_UART (Universal Asynchronous Receiver Transmitter)
 */

#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

#include "MKL46Z4.h"
#include "board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define OSR_MIN 3              /* over sampling ratio for receiver */
#define OSR_MAX 31             /* range: 3 (4x) --> 31 (32x) */

/* constants to control terminal (VT100) cursor */
#define UART_CLEAR_SCREEN "\033[2J"
#define UART_GO_TO_HOME "\033[0;0H"
#define UART_MAX_STR_PRINTF 100U
/*******************************************************************************
 * UART_APP_Layer
 ******************************************************************************/
/*!
 * @brief Print a character
 *
 * @param ch input character.
 *
 * @return none (display on screen).
 */
void UART_Printf_C(char ch);

/*!
 * @brief Scan (Get) a character
 * @how-to      ch = UART_Scanf_C();
 *              UART_Printf_C(ch);
 * @param none.
 *
 * @return a character.
 */
char UART_Scanf_C(void);

/*!
 * @brief Print a string
 *
 * @param str[] input string.
 *
 * @return none (display on screen).
 */
void UART_Printf_S(char str[]);
/*******************************************************************************
 * UART_HAL_Layer
 ******************************************************************************/
/*!
 * @brief Config UART
 *
 * @param baudrate input.
 *
 * @return none.
 */
void UART_Init(uint32_t baud_rate);

/*!
 * @brief find the optimal value of OSR based on baudrate input
 *
 * @param baudrate the desired value of baudrate from user.
 *
 * @return optimal osr value, at which difference of baudrates is minimum.
 */
uint8_t UART0_OsrOptimal(uint32_t baud_rate);
uint8_t UART0_OsrOptimal_HaiND(uint32_t baud_rate, uint32_t clk);

/*!
 * @brief init UART to work based on inputs: baudrate and over sampling ratio
 *
 * @param baudrate the desired value of baudrate from user.
 * @param osr over sampling ratio, derived from HAL_UART0_OSR_Optimal function.
 *
 * @return actual baudrate after configuration.
 */
uint32_t UART_BaudRateInit(uint32_t baud_rate, uint8_t osr);
#endif /* SOURCES_UART_H_ */
