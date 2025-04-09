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
void peripheral_init(void) {
  /* Enable the push buttons*/
  push_buttons_init(false);

  console_init();

  joystick_init();

  ece353_enable_lcd();

  i2c_init();
  
  // Set bit 7 as input, bits 6-0 as outputs
  io_expander_set_configuration( 0x80);  
  
  // Turn OFF all LEDs
  io_expander_set_output_port(0x00); 
 
  // Turn on io expander interrupts
  //io_expander_enable_int();          
  
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
void main_app(void) {
  printf("\x1b[2J\x1b[;H");
  printf("**************************************************\n\r");
  printf("* %s\n\r", APP_DESCRIPTION);
  printf("* Date: %s\n\r", __DATE__);
  printf("* Time: %s\n\r", __TIME__);
  printf("* Name:%s\n\r", NAME);
  printf("**************************************************\n\r");

  ltr_light_sensor_start();
  uint16_t bet = 0;
  uint16_t funds = score_read();
  uint32_t reg_val = 0;
  uint16_t led_case = 0;
  uint16_t ch0 = 0;
  uint16_t ch1 = 0;
  
  // FONT color
  uint16_t font = 0xFFFF;


  while (1) {
    // lux handle
    if(ECE353_Events.lux_read == 1){
      ch0 = ltr_light_sensor_get_ch0;
    }

    if(ch0 < 100){
      font = LCD_COLOR_BLUE;
    }
    else if (ch0 > 500){
      font = LCD_COLOR_RED;
    }
    else{
      font = LCD_COLOR_GREEN;
    }
    
    screen_display_stats_funds(funds, font);
    screen_display_stats_bet(bet, font);
    

  // If the joystick moves up increment bet by 50
    if (ECE353_Events.joystick == 1 && Joystick_Pos == JOYSTICK_POS_UP)
    {
      // If the bet is greater than or equal to the funds increment
      // Note: bet should never be greater than funds but for completeness
      if (bet >= funds)
      {
        funds += 25;
        score_write(funds);
      }
      bet += 50;
    }
    // If down then decrement bet and make sure it is within the allowed bounds
    else if (ECE353_Events.joystick == 1 && Joystick_Pos == JOYSTICK_POS_DOWN)
    {
      if (bet >= 25)
      {
        bet -= 25;
      lcd_clear_screen(0x0000);
      }
      else
      {
        bet -= 50;
      }
    }

    reg_val = REG_PUSH_BUTTON_IN;
    // If Button 2 is pressed
    if ((reg_val & SW2_MASK) == 0x00)
    {
      led_case++;

      if (led_case > 7) {
        led_case = 0;
      }

      switch(led_case){
        case 0:
          //No Lights On
        case 1:
          //D605 Light On
        case 2:
          //D606 Light On
        case 3:
          //D600 Light On
        case 4:
          //D601 Light On
        case 5:
          //D602 Light On
        case 6:
          //D603 Light On
        case 7:
          //D604 Light On
      }
      // TODO ADD CASE LOGIC FOR WHICH LED WILL TURN ON
    }

  }
}

#endif