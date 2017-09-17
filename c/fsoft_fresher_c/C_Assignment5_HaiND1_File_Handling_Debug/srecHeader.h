/*******************************************************************************
 * Assignment 5: SREC (17-1)
 * @dev: linhth8
 * @mentor: haind1
 * @topic: file handling, debugging
 ******************************************************************************/
 
#ifndef _SRECHEADER_H_
#define _SRECHEADER_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SREC_MAX_LENGTH_LINE 100

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
uint32_t g_srecByteCount;
FILE *g_fsrec_out;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief Get checksum value from two last bytes in a line
 *
 * @param tmp_line a line string as input param.
 *
 * @return checksum information contained in a line
 */
uint8_t srecChecksumGet(char *tmp_line);

/*!
 * @brief Calculate checksum value of a line
 * @howto checksum = bytecount + address + data
 *
 * @param tmp_line a line string as input param.
 *
 * @return checksum information calculated from that string line.
 */
uint8_t srecChecksumCal(char *tmp_line);

/*!
 * @brief Get data type of a line
 *
 * @param tmp_line .
 *
 * @return Address data types (2 bytes, 3 bytes, 4 bytes)
 */
uint8_t srecGetType(char *tmp_line);

/*!
 * @brief Test format of a line as SREC or not
 *
 * @param tmp_line .
 *
 * @return 1 if SREC, 0 if non-SREC.
 */
uint8_t srecFormat(char *tmp_line);

/*!
 * @brief Extract and display address and data field of each line
 *
 * @param tmp_line.
 * @param type: data type get from srecGetType(tmp_line).
 *
 * @return Display address and data.
 */
void srecDisplayAddressData(char *tmp_line, uint8_t type);

/*!
 * @brief Convert a character to a number
 *
 * @param c: character.
 *
 * @return '0' --> 0; 'A' --> 10.
 */
uint8_t charToNum(char c);

/*!
 * @brief Convert hex number (character) to decimal
 *
 * @param a: character a.
 * @param b: character b.
 *
 * @return decimal value of hex number 0xAB.
 */
uint32_t hexToDec(char a, char b);

#endif /* _SRECHEADER_H_ */
