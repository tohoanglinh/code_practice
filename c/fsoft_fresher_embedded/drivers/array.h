/*
 * array.h
 *
 *  Created on: Mar 4, 2017
 *      Author: linhth8
 */

/**
 * @file      array.h
 * @developer LinhTH8
 * @topic     LIB_ARRAY
 */

#ifndef SOURCES_ARRAY_H_
#define SOURCES_ARRAY_H_

#include <stdint.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
// #define MACRO2 2

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief find minimum value in an array of integers
 *
 * @param array[] input array of integers 16-bit to process.
 * @param size size of input array in elements
 * @return the location (index) of min value in that array.
 */
uint8_t min_array(uint16_t array[], uint8_t size);

#endif /* SOURCES_ARRAY_H_ */
