/*******************************************************************************
 * @dev: LinhTH8 [FR_EMB_HN17_01]
 * @men: MinhNQ2
 * @tit: MockTest1 FAT12
 * @dat: 25/1 - 9/2
 * @file: HAL.h
 * HAL - Hardware Abstraction Layer: a layer of programming that
 * allows a computer os to interact with a hardware device.
 ******************************************************************************/

#ifndef _HAL_H_
#define _HAL_H_

#include "config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SIZE_SECTOR 512

/*******************************************************************************
 * APIs
 ******************************************************************************/
/*!
 * @brief one read sector index into buff
 * This function read sector index into buff, return read byte.
 * @param ulong index.
 * @param uchar *buff.
 *
 * @return read byte.
 */
uint32_t kmc_read_sector (uint32_t indexSector, unsigned char *buff);
/*!
 * @brief read num sector contiguously, start from sector index, into array pointer buff
 *
 * @param ulong index.
 * @param uint num.
 * @param uchar *buff
 *
 * @return read num of byte.
 */
uint32_t kmc_read_multi_sector (uint32_t indexSector, uint16_t num, unsigned char *buff);

#endif /* _HAL_H_ */
