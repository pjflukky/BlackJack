/**
 * @file io-expander.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2023-10-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "io-expander.h"

/** Write a register on the TCA9534
 *
 * @param reg The reg address to read
 * @param value The value to be written
 *
 */
static void io_expander_write_reg(uint8_t reg, uint8_t value)
{
	cy_rslt_t rslt;

	/* ADD CODE */
	/* Allocate the write data packet that will be sent to the IO Expander */

	/* ADD CODE */
	/* Use cyhal_i2c_master_write to write the required data to the device. */

	CY_ASSERT(rslt == CY_RSLT_SUCCESS);
}

/** Read a register on the TCA9534
 *
 * @param reg The reg address to read
 *
 */
static uint8_t io_expander_read_reg(uint8_t reg)
{
	cy_rslt_t rslt;
	uint8_t return_val = 0;

	/* ADD CODE */
	/* Allocate the write data packet that will be sent to the IO Expander */
	
	/* ADD CODE */
	/* Allocate the read data packet that will be sent from the IO Expander */

	/* ADD CODE */
	/* Use cyhal_i2c_master_write to write the required data to the device. */
	
	CY_ASSERT(rslt == CY_RSLT_SUCCESS);

	/* ADD CODE */
	/* Use cyhal_i2c_master_read to read the required data from the device. */
	
	CY_ASSERT(rslt == CY_RSLT_SUCCESS);

	return return_val;
}

/** Read the value of the input port
 *
 * @param reg The reg address to read
 *
 */
uint8_t io_expander_get_input_port(void)
{
	return io_expander_read_reg(TCA9534_INPUT_PORT_ADDR);

}

/** Write the value of the output port
 *
 * @param value The value written
 *
 */
void io_expander_set_output_port(uint8_t value)
{
	io_expander_write_reg(TCA9534_OUTPUT_PORT_ADDR, value);
}

/** Write the polarity inversion register
 *
 * @param value The value written
 *
 */
void io_expander_set_polarity_inversion(uint8_t value)
{
	io_expander_write_reg(TCA9534_POLARITY_ADDR, value);
}

/** Write the value of the configuration Register
 *
 * @param value The value written
 *
 */
void io_expander_set_configuration(uint8_t value)
{
	io_expander_write_reg(TCA9534_CONFIG_ADDR, value);
}