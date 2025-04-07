/**
 * @file hw01.c
 * @author <ADD YOUR NAMES>
 * @brief
 * @version 0.1
 * @date 2025-01-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "hw03.h"
#include "io-lcd.h"
#include "io-leds.h"
#include "joystick.h"
#include "light-sensor.h"
#include "score.h"
#include "screen.h"
#include "timer_050_ms.h"
#include <stdio.h>

#if defined(HW03)

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: S25 HW03";
char STUDENTS[] = "ADD  YOUR NAMES";

/* Random Number Generator Handle*/
cyhal_trng_t trng_obj;

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE.
 *
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void peripheral_init(void)
{
  /* Enable the push buttons*/
  push_buttons_init(false);

  console_init();

  joystick_init();

  ece353_enable_lcd();

  i2c_init();

  // Set bit 7 as input, bits 6-0 as outputs
  io_expander_set_configuration(0x80);

  // Turn OFF all LEDs
  io_expander_set_output_port(0x00);

  // Turn on io expander interrupts
  io_expander_enable_int();

  spi_init();
  eeprom_cs_init();

  timer_050_ms_start();
  timer_250_ms_start();
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 */
void main_app(void)
{

  printf("\x1b[2J\x1b[;H");
  printf("**************************************************\n\r");
  printf("* %s\n\r", APP_DESCRIPTION);
  printf("* Date: %s\n\r", __DATE__);
  printf("* Time: %s\n\r", __TIME__);
  printf("* Name:%s\n\r", NAME);
  printf("**************************************************\n\r");

  ltr_light_sensor_start();

  uint32_t bet = 0;
  uint32_t funds = 0;

  while (1)
  {

    // If the joystick moves up increment bet by 50
    if (ECE353_Events.joystick == 1 && Joystick_Pos == JOYSTICK_POS_UP)
    {
      //If the bet is greater than or equal to the funds increment
      //Note: bet should never be greater than funds but for completeness
      if (bet >= funds) {
        funds += 50;
      }
      bet += 50;
    }
    // If down then decrement bet and make sure it is within the allowed bounds
    else if (ECE353_Events.joystick == 1 && Joystick_Pos == JOYSTICK_POS_DOWN)
    {
      if (bet <= 50)
      {
        bet == 0;
      }
      else
      {
        bet -= 50;
      }
    }
  }
}

#endif