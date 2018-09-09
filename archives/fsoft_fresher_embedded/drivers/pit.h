/*
 * pit.h
 *
 *  Created on: Mar 4, 2017
 *      Author: linhth8
 */

/**
 * @file      pit.h
 * @developer LinhTH8
 * @mentor    AnhNN14
 * @topic     MCP_PIT
 */

#ifndef SOURCES_PIT_H_
#define SOURCES_PIT_H_

#include "MKL46Z4.h"
#include "board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief start a timer to count from pit_load_value to 0
 *        then interrupt flag, then jump to PIT_IRQHandler()
 *
 * @param pit_channel 0 or 1 (Timer 0, Timer 1)
 * @param pit_delay desired delay value
 * @param pit_priority 1,2,3,4...
 *
 * @return none.
 */
void PIT_Init(uint8_t pit_channel, double pit_delay);

#endif /* SOURCES_PIT_H_ */
