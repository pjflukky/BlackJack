/**
 * @file ice01.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(EX03)

char APP_DESCRIPTION[] = "ECE353: Ex03 PSoC6 IO Ports";

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
 * This function will initialize hardware resources 
 */
void peripheral_init(void)
{
    cy_rslt_t rslt;

    console_init();

    /* Initialize SW1 P6_3 as an input */
    rslt = cyhal_gpio_init(PIN_SW1, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);

    /* Initialize Red LED P9_0 as an output*/
    rslt = cyhal_gpio_init(PIN_RGB_RED, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);

}

/**
 * @brief
 * This function implements the behavioral requirements for the application
 */
void main_app(void)
{
    bool sw1_cur = false;
    bool sw1_prev = false; 

     /* Send the Clear Screen Escape Sequence*/
    printf("\x1b[2J\x1b[;H");

    printf("**************************************************\n\r");
    printf("* %s\n\r",APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    

    while(1){
        if((PORT_BUTTONS->IN & SW1_MASK) == 0x00)
            sw1_cur = true;
        else 
            sw1_cur = false;

        if(sw1_cur && !sw1_prev){
            printf("SW1 is pressed\n");
            PORT_RGB_RED->OUT |= MASK_RGB_RED; // because it is active high we use 'or' operand
        }

        if(!sw1_cur && sw1_prev){
            printf("SW1 is released\n");
            PORT_RGB_RED->OUT &= ~MASK_RGB_RED; 
        }

        sw1_prev = sw1_cur;

        cyhal_system_delay_ms(100);
    };
}
#endif