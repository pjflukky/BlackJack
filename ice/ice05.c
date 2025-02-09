/**
 * @file ice05.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"
#include "io-sw.h"
#include "systick.h"

#if defined(ICE05)

char APP_DESCRIPTION[] = "ECE353: ICE 05 - SysTick";

/*****************************************************************************/
/* Macros                                                                    */
/*****************************************************************************/

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/

/*****************************************************************************/
/* Function Definitions                                                      */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    console_init();

    push_buttons_init(false);
}

/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    uint32_t sw1_pressed_ms = 0;
    button_state_t sw1_curr_state = BUTTON_RELEASED;
    uint32_t button_value = 0;

    printf("\x1b[2J\x1b[;H");
    printf("**************************************************\n\r");
    printf("* %s\n\r", APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    for (;;)
    {
        button_value = REG_PUSH_BUTTON_IN;
        sw1_pressed_ms = 0;

        printf("Wait for SW1 to be pressed\n\r");

        /* Wait for SW1 to be pressed */
        while((button_value & SW1_MASK) != 0x00){
            button_value = REG_PUSH_BUTTON_IN;
        }

        /* Start the SysTick Timer with a period of 1ms */  
        systick_start(TICKS_MS_001);
        printf("sw1 pressed\n");

        /* Count the number of times that the systick timer has expired 
         * while SW1 is pressed */
        while((button_value & SW1_MASK) == 0x00){
            button_value = REG_PUSH_BUTTON_IN;
            while(!systick_expired()){

            }
            sw1_pressed_ms++;

        }


        /* Print out how many milliseconds SW1 was pressed for */
        printf("SW1 was pressed for %lu mS\n\r", sw1_pressed_ms);

    }
}
#endif