/**
 * @file ice01.c
 * @author Pakorn Jantacumma (pjantacumma@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(EX02)

char APP_DESCRIPTION[] = "ECE353: Ex02 - Memory Mapped IO";

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
    console_init();

    /* There are no hardware resources to initialize*/
    push_buttons_init(false);
}

/**
 * @brief
 * This function implements the behavioral requirements for the application
 */
void main_app(void)
{
    uint32_t reg_val;
    uint32_t i = 0;

        /* Send the Clear Screen Escape Sequence*/
    printf("\x1b[2J\x1b[;H");

    printf("**************************************************\n\r");
    printf("* %s\n\r",APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");
    /* Enter Infinite Loop*/
    while (1)
    {
        reg_val = REG_PUSH_BUTTON_IN;
        printf("%d\n", reg_val);
        if((reg_val & 1000) == 0x00){
          //  i++;
          //  printf("%d\n", i);  
        }

        cyhal_system_delay_ms(100);
    }
}
#endif
