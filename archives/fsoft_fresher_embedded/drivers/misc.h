/*
 * misc.h
 *
 *  Created on: Mar 4, 2017
 *      Author: linhth8
 */

/**
 * @file      misc.h
 * @developer LinhTH8
 * @topic     LIB_MISC
 */

#ifndef SOURCES_MISC_H_
#define SOURCES_MISC_H_

#include "board.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* DATA TYPES */
typedef enum
{
    FALSE,
    TRUE
} Boolean;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief generate a simple delay
 *
 * @param delay_cnt number of instructions nop to produce delay
 *
 * @return none
 */
void delay(uint32_t delay_cnt);

/*!
 * @brief generate a simple delay
 *
 * @param delay_cnt number of instructions nop to produce delay
 *
 * @return none
 */
const char *byte_to_binary(uint8_t x);

/*!
 * @brief generate a simple delay
 *
 * @param delay_cnt number of instructions nop to produce delay
 *
 * @return none
 */
uint8_t BIT_Set(uint8_t number, uint8_t bit_position);

/*!
 * @brief generate a simple delay
 *
 * @param delay_cnt number of instructions nop to produce delay
 *
 * @return none
 */
uint8_t BIT_Clear(uint8_t number, uint8_t bit_position);

/*!
 * @brief generate a simple delay
 *
 * @param delay_cnt number of instructions nop to produce delay
 *
 * @return none
 */
uint8_t BIT_Toggle(uint8_t number, uint8_t bit_position);

/*!
 * @brief generate a simple delay
 *
 * @param delay_cnt number of instructions nop to produce delay
 *
 * @return none
 */
uint8_t BIT_SetToX(uint8_t number, uint8_t bit_position, uint8_t value);

/*!
 * @brief generate a simple delay
 *
 * @param delay_cnt number of instructions nop to produce delay
 *
 * @return none
 */
void NVIC_Config(IRQn_Type irq_type, uint8_t irq_priority_level);

#endif /* SOURCES_MISC_H_ */
