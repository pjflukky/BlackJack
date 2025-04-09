/**
 * @file score.c
 * @author ADD YOUR NAMES
 * @brief
 * @version 0.1
 * @date 2025-02-04
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "score.h"
#include "eeprom.h"

/**
 * @brief
 *  Writes a 16-bit unsigned number to the eeprom
 *  Data is written to addresses 0x10 and 0x11
 * @param score
 */
void score_write(uint16_t score)
{
    //Low value is 0x10 (Given)
    uint16_t low = 0x10;
	//High value is 0x11 (Given)
	uint16_t high = 0x11;
	uint8_t low_bytes = score & 0x00FF;
	uint8_t high_bytes = (uint8_t)(score >> 8);

	//Write the low and high bytes
	eeprom_write_byte(low, low_bytes);
	eeprom_write_byte(high, high_bytes);

}

/**
 * @brief
 * Reads the current high water mark for the funds from the EEPROM
 * @return uint16_t
 * The value of the high water mark for the funds
 */
uint16_t score_read(void)
{

	//Low value is 0x10 (Given)
    uint16_t low = 0x10;
	//High value is 0x11 (Given)
	uint16_t high = 0x11;
	uint8_t low_bytes = eeprom_read_byte(low);
	uint8_t high_bytes = eeprom_read_byte(high);

	//Get the return result and return it by bit shifting the high bytes and oring it with the low
	uint16_t return_rslt = (high_bytes << 8) | low_bytes;

	return return_rslt;
	

}