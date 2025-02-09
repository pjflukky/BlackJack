/**
 * @file ice16.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2023-11-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(ICE16)

char APP_DESCRIPTION[] = "ECE353: ICE 16 - FreeRTOS Semaphores";

/*****************************************************************************/
/*  FreeRTOS Handles                                                         */
/*****************************************************************************/
TaskHandle_t Task_Handle_Button_SW1 = NULL;
TaskHandle_t Task_Handle_Button_SW2 = NULL;
TaskHandle_t Task_Handle_RGB_LED = NULL;
TaskHandle_t Task_Handle_Buzzer = NULL;

/* ADD CODE */
/* Allocate a semaphore that will be used to control the RGB LED */

/* ADD CODE */
/* Allocate a semaphore that will be used to control the Buzzer */

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/
void task_button_sw1(void *pvParameters);
void task_button_sw2(void *pvParameters);
void task_RGB_LED(void *pvParameters);
void task_buzzer(void *pvParameters);

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* Peripheral Initialization                                                  */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    console_init();

    /* Initialize the RGB LEDs */
    leds_init();

    /* Initialize the buttons */
    push_buttons_init(false);

    /* Initialize the Buzzer */
    pwm_buzzer_init();
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
     /* Send the Clear Screen Escape Sequence*/
    printf("\x1b[2J\x1b[;H");

    printf("**************************************************\n\r");
    printf("* %s\n\r",APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    /* ADD CODE */
    /* Create Semaphores */

    /* Create SW1 Task */
    xTaskCreate(task_button_sw1,
                "SW1 Task",
                configMINIMAL_STACK_SIZE,
                NULL,
                1,
                &Task_Handle_Button_SW1);

    /* Create SW1 Task */
    xTaskCreate(task_button_sw2,
                "SW2 Task",
                configMINIMAL_STACK_SIZE,
                NULL,
                1,
                &Task_Handle_Button_SW2);

    /* Create RGB LED Task */
    xTaskCreate(task_RGB_LED,
                "RGB Task",
                configMINIMAL_STACK_SIZE,
                NULL,
                1,
                &Task_Handle_RGB_LED);

    /* Create Buzzer Task */
    xTaskCreate(task_buzzer,
                "Buzzer Task",
                configMINIMAL_STACK_SIZE,
                NULL,
                1,
                &Task_Handle_Buzzer);

    /* Start the Scheduler */
    vTaskStartScheduler();

    while (1)
    {
    };
}

/**
 * @brief
 * This task will monitor SW1.  When SW1 is pressed, the task will give a 
 * semaphore to the RGB LED task to update the currently active color.
 *  @param pvParameters
 */
void task_button_sw1(void *pvParameters)
{
    /* Allocate any local variables used in this task */
    bool state_button_prev = false;
    bool state_button_curr = false;

    while (1)
    {
        /* Sleep for 50mS -- DO NOT use any cyhal_ functions to delay */
        vTaskDelay(50);

        /* Check the current state of the button */
        if ((PORT_BUTTONS->IN & SW1_MASK) == 0x00)
        {
            state_button_curr = true;
        }
        else
        {
            state_button_curr = false;
        }

        /* Detect if the button has been pressed */
        if (state_button_curr && !state_button_prev)
        {
            /* ADD CODE */
            /* Give the semaphore to the RGB Task */

            printf("SW1 Detected \n\r");
        }

        /* Update the previous button state */
        state_button_prev = state_button_curr;
    }
}

/**
 * @brief
 * This task will detect when SW2 is pressed.  When SW2 is pressed, it will give a semaphore
 * to the Buzzer task indicating that the frequency of the buzzer should be updated.
 * @param pvParameters
 */
void task_button_sw2(void *pvParameters)
{
    /* Allocate any local variables used in this task */
    bool state_button_prev = false;
    bool state_button_curr = false;

    while (1)
    {
        /* Sleep for 50mS -- DO NOT use any cyhal_ functions to delay */
        vTaskDelay(50);

        /* Check the current state of the button */
        if ((PORT_BUTTONS->IN & SW2_MASK) == 0x00)
        {
            state_button_curr = true;
        }
        else
        {
            state_button_curr = false;
        }

        /* Detect if the button has been pressed */
        if (state_button_curr && !state_button_prev)
        {
            /* ADD CODE */
            /* Give the semaphore to the Buzzer Task */
            
            printf("SW2 Detected \n\r");
        }

        /* ADD CODE */
        /* Update the previous button state */
        state_button_prev = state_button_curr;
    }
}

/**
 * @brief 
 * Controls the color displayed on the RGB LED.  The active color changes every time 
 * the task successfully takes a semaphore 
 * @param pvParameters 
 */
void task_RGB_LED(void *pvParameters)
{
    uint8_t color = 0;

    /* Turn all of the LEDs off */
    PORT_RGB_RED->OUT_CLR = MASK_RGB_RED;
    PORT_RGB_GRN->OUT_CLR = MASK_RGB_GRN;
    PORT_RGB_BLU->OUT_CLR = MASK_RGB_BLU;

    while (1)
    {
        /* ADD CODE */
        /* Take the RGB Color Semaphore */

        /* ADD CODE to cycle through the colors.  The colors
         * should change every time a semaphore is successfully
         * taken.  
         * 
         * All OFF->Red     Semaphore Taken
         * Red->Green       Semaphore Taken
         * Green->Blue      Semaphore Taken
         * Blue->ALL OFF    Semaphore Taken
         * All OFF->red     Semaphore Taken
         * Repeat...
         * 
         */
        printf("Changing Color... ");
    }
}
/**
 * @brief 
 *  The task controls the frequency of the buzzer.  The frequency of the buzzer changes every time
 *  the task successfully takes a semaphore. 
 * @param pvParameters 
 */
void task_buzzer(void *pvParameters)
{
    uint16_t buzz_freq = 0;

    /* Stop the buzzer */
    pwm_buzzer_stop();
    while (1)
    {
        /* ADD CODE */
        /* wait for a semaphore to change the state of the buzzer */

        /* ADD CODE */
        /* The buzzer should start OFF.  Each time a semaphore is taken, increment the current
         * frequency of the buzzer by 1Khz.  The supported frequencies are 0, 1Khz, 2Khz, 3Khz.
         *
         * 0 Hz         Semaphore Taken
         * 1000 Hz      Semaphore Taken
         * 2000 Hz      Semaphore Taken
         * 3000 Hz      Semaphore Taken
         * 0 Hz         Semaphore Taken
         * Repeat...
         * 
         * */
        printf("Changing Freq...%d\n\r", buzz_freq);

    }
}
//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while (1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    // Handle FreeRTOS Stack Overflow
    while (1)
    {
    }
}

#endif