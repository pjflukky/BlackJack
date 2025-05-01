/**
 * @file task_io_expander.c
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "task_io_expander.h"
#include "task_console.h"

#if defined(HW04) 

/* Event Groups */
extern EventGroupHandle_t eg_UI;

void hw04_handler_io_exp(void *callback_arg, cyhal_gpio_event_t event);

QueueHandle_t q_IO_Exp;

/**
 * @brief 
 * Handler used to inform non-isr code that a the IO expander push button has been pressed
 * @param callback_arg 
 * @param event 
 */
 void hw04_handler_io_exp(void *callback_arg, cyhal_gpio_event_t event)
 {
    /* ADD CODE */
    //io_expander_set_output_port(0xFF);
     /* For debugging - verify the handler is called */
     task_print_info("IO Expander interrupt triggered!");

    /* Set the event bit in the event group to notify that IO expander button was pressed */
   // BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    /* Set the EVENT_UI_IO_EXP_INT bit in the event group */
    //xEventGroupSetBitsFromISR(eg_UI, EVENT_UI_IO_EXP_INT, &xHigherPriorityTaskWoken);

    xEventGroupSetBits(eg_UI, EVENT_UI_IO_EXP_INT);
    
    /* If a higher priority task was woken, request a context switch */
   // portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

 }

/**
 * @brief 
 * Displays the number of whammies that have been selected
 * @param param 
 * Not Used
 */
void task_io_expander(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;

     /* Local variable to store received message */
     uint8_t led_command;

    /* Repeatedly running part of the task */
    for (;;)
    {
        /* ADD CODE */
        /* Wait for a message from other tasks */
        if (xQueueReceive(q_IO_Exp, &led_command, portMAX_DELAY) == pdTRUE)
        {
            /* Set the output port with the received command */
            io_expander_set_output_port(led_command);
        }
    }
}

void task_io_expander_init(void)
{
    i2c_init();

    q_IO_Exp = xQueueCreate(1, sizeof(uint8_t));

    /* Set all pins as outputs except for the IO_EXP_INT pin */
    io_expander_set_configuration(0x80);

    // set led to all off first 
    io_expander_set_output_port(0x00);

    /* Enable interrupts from the IO expander on the PSoC6*/
    /* ADD CODE */

    /* Enable interrupts from the IO expander on the PSoC6 */
    /* Configure the IO expander interrupt pin correctly */
    cyhal_gpio_init(
        P11_2,                      /* IO Expander interrupt pin */
        CYHAL_GPIO_DIR_INPUT,       /* Input direction */
        CYHAL_GPIO_DRIVE_PULLUP,      /* No drive mode for input */
        true                  /* Initial state LOW */
    );
    
    /* Register the callback function */
    static cyhal_gpio_callback_data_t cb_data;
    cb_data.callback = hw04_handler_io_exp;
    cb_data.callback_arg = NULL;

    cyhal_gpio_register_callback(P11_2, &cb_data);
    
    /* Enable the interrupt */
    cyhal_gpio_enable_event(
        P11_2,                      /* IO Expander interrupt pin */
        CYHAL_GPIO_IRQ_FALL,        /* Trigger on rising edge */
        CYHAL_ISR_PRIORITY_DEFAULT, /* Priority level */
        true                        /* Enable the interrupt */
    );

    xTaskCreate(
        task_io_expander,
        "Task IO Exp",
        configMINIMAL_STACK_SIZE,
        NULL,
        ECE353_TASK_PRIORITY_UI_INPUT,
        NULL);
}

#endif
