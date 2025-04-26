/**
 * @file task_joystick.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2025-01-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #include "task_joystick.h"

 #if defined(HW04) 
/* Event Groups */
extern EventGroupHandle_t eg_UI;

/**
 * @brief 
 * This function is used to detect when the user presses the joystick UP or DOWN
 * @param pvParameters 
 */
 void task_joystick(void *param)
{
    uint16_t test_num = 0;
    joystick_position_t cur_pos = JOYSTICK_POS_CENTER;
    joystick_position_t prev_pos = JOYSTICK_POS_CENTER;


    /* Suppress warning for unused parameter */
    (void)param;

    /* Repeatedly running part of the task */
    for (;;)
    {
        /* ADD CODE */
        vTaskDelay(pdMS_TO_TICKS(50));

        // read joystick position
        cur_pos = joystick_get_pos();

        //determine if up or down and update event accordingly
        if(cur_pos == JOYSTICK_POS_UP && prev_pos == JOYSTICK_POS_CENTER){
            xEventGroupSetBits(eg_UI, EVENT_UI_JOY_UP);
        }

        if(cur_post == JOYSTICK_POS_DOWN && prev_pos == JOYSTICK_POS_CENTER){
            xEventGroupSetBits(eg_UI, EVENT_UI_JOY_DOWN);
        }

        //update position
        prev_pos = cur_pos;

    }
}

/**
 * @brief
 * Initializes User Push Buttons and creates the corresponding FreeRTOS tasks for SW1 and SW2
 */
void task_joystick_init(void)
{
  joystick_init(); 

  // Register the Task with FreeRTOS
  xTaskCreate(
      task_joystick,
      "Task Joystick",
      configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_UI_INPUT,
      NULL);
}
#endif