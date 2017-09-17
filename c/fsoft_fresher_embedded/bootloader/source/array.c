/*
 * array.c
 *
 *  Created on: Mar 4, 2017
 *      Author: linhth8
 */

/**
 * @file      array.c
 * @developer LinhTH8
 * @topic     LIB_ARRAY
 */

#include "array.h"

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
 * @detail: find minimum value in an array of integers
 */
uint8_t min_array(uint16_t array[], uint8_t size)
{
  uint8_t i;

  /* init a min value as the first (0) element of input array */
  uint16_t min_value;
  min_value = array[0];

  /* init the location of the min value (min_location) as 0 */
  uint8_t min_location;
  min_location = 0;

  /* compare the next value to min_value, if less than,
  *  - then assign  min_value = next
  *  - update location of min_value = min_location
  */
  for (i = 0; i < size; i++)
  {
      if (array[i] < min_value)
      {
        min_value = array[i];
        min_location = i;
      }
  }

  /* return the location (index) of min value in that array */
  return min_location;
}
