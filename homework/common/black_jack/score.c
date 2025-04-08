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
    uint8_t transmit_data[1] = {EEPROM_CMD_WRITE};
	uint8_t receive_data[1] = {0};
	cy_rslt_t rslt = CY_RSLT_SUCCESS;

    // Wait for any outstanding writes to complete
	eeprom_wait_for_write();

	// Enable writes to the eeprom
	eeprom_write_enable();

	// Set the CS Low
	cyhal_gpio_write(PIN_SPI_EEPROM_CS, 0);
	// Starts a data transfer
	rslt = cyhal_spi_transfer(
		&mSPI,
		transmit_data,
		1,
		receive_data,
		1,
		0x00);
	CY_ASSERT(rslt == CY_RSLT_SUCCESS); /* Halt MCU if SPI transaction fails*/

	// Set the CS High
	cyhal_gpio_write(PIN_SPI_EEPROM_CS, 1);

	// Disable writes to the eeprom
	eeprom_write_disable();


}

/**
 * @brief
 * Reads the current high water mark for the funds from the EEPROM
 * @return uint16_t
 * The value of the high water mark for the funds
 */
uint16_t score_read(void)
{
    uint8_t transmit_data[1] = {0};
	uint8_t receive_data[1] = {EEPROM_CMD_READ};
	cy_rslt_t rslt = CY_RSLT_SUCCESS;

	// Wait for any outstanding writes to complete
	eeprom_wait_for_write();

	// Enable writes to the eeprom
	eeprom_write_enable();

	// Set the CS Low
	cyhal_gpio_write(PIN_SPI_EEPROM_CS, 0);

	// Starts a data transfer
	rslt = cyhal_spi_transfer(
		&mSPI,
		transmit_data,
		1,
		receive_data,
		1,
		0x00);
	CY_ASSERT(rslt == CY_RSLT_SUCCESS); /* Halt MCU if SPI transaction fails*/

	// Set the CS High
	cyhal_gpio_write(PIN_SPI_EEPROM_CS, 1);

	// Disable writes to the eeprom
	eeprom_write_disable();

	// Return the value from the EEPROM to the user
	return rslt;

}