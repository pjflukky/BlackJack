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
  // io_expander_enable_int();

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
  uint16_t bet = 0;
  uint16_t funds = 0;
  uint32_t reg_val = 0;
  uint16_t led_case = 0;
  uint16_t led_number = 0x00;
  uint16_t ch0 = 0;
  uint16_t ch1 = 0;

  // FONT color
  uint16_t font = LCD_COLOR_GREEN;

  while (1)
  {
    // lux handle
    if (ECE353_Events.lux_read == 1)
    {
      ch0 = ltr_light_sensor_get_ch0(); // get value from channel 0

      // ch0 is lux value and change color based on the condition
      if (ch0 < 100)
      {
        font = LCD_COLOR_BLUE;
      }
      else if (ch0 > 500)
      {
        font = LCD_COLOR_RED;
      }
      else
      {
        font = LCD_COLOR_GREEN;
      }

      ECE353_Events.lux_read == 0;
    }

    // If the joystick moves up increment bet by 50
    if (ECE353_Events.joystick == 1 && Joystick_Pos == JOYSTICK_POS_UP)
    {
      // If the bet is greater than or equal to the funds increment
      // Note: bet should never be greater than funds but for completeness
      if (bet >= funds)
      {
        funds += 50;
        // score_write(funds);
      }
      bet += 50;
    }
    // If down then decrement bet and make sure it is within the allowed bounds
    else if (ECE353_Events.joystick == 1 && Joystick_Pos == JOYSTICK_POS_DOWN)
    {
      if (bet >= 50)
      {
        bet -= 50;
        lcd_clear_screen(0x0000);
      }
    }
    //Display Player Stats
    screen_display_stats_funds(funds, font);
    screen_display_stats_bet(bet, font);

    reg_val = REG_PUSH_BUTTON_IN;
    // If Button 2 is pressed
    if (ECE353_Events.sw2 == 1)
    {
      if (led_case == 0x7F)
      {
        led_case = 0x00;
      }
      else
      {
        led_case = (led_case << 1) | 0x01;
      }
      io_expander_set_output_port(led_case);
      //Unused code for switch handling
      // switch(led_case){
      //   case 0:
      //     //No Lights On
      //     io_expander_set_output_port(0x00);
      //   case 1:
      //     //D605 Light On
      //     io_expander_set_output_port(0x01);
      //   case 2:
      //     //D606 Light On
      //     io_expander_set_output_port(0x03);
      //   case 3:
      //     //D600 Light On
      //     io_expander_set_output_port(0x07);
      //   case 4:
      //     //D601 Light On
      //     io_expander_set_output_port(0x0F);
      //   case 5:
      //     //D602 Light On
      //     io_expander_set_output_port(0x1F);
      //   case 6:
      //     //D603 Light On
      //     io_expander_set_output_port(0x3F);
      //   case 7:
      //     //D604 Light On
      //     io_expander_set_output_port(0x7F);
      // }
      ECE353_Events.sw2 = 0;
    }

    // U602 Activation, reset funds and bet then write new funds
    if (ECE353_Events.io_interrupt == 1)
    {
      funds = 0;
      bet = 0;
      score_write(funds);
      ECE353_Events.io_interrupt = 0;
      screen_display_stats_funds(funds, font);
    screen_display_stats_bet(bet, font);
    }
  }
}

#endif