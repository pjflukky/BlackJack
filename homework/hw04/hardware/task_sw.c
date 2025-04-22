/**
 * @file task_sw.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "task_sw.h"

#if defined(HW04)

/* Event Groups */
extern EventGroupHandle_t eg_UI;

/**
 * @brief
 * Function used to detect when SW1, SW2, and SW3 are been pressed.  
 * The task should detect the initial button press by debouncing 
 * the push button for 50mS.  Pressing the button for longer than 50mS 
 * should only result in a single button event.
 * 
 * @param param
 *  Unused
 */
void task_switches(void *param)
{
      /* Suppress warning for unused parameter */
      (void)param;

      // switch's states for all 3 switches
      button_state_t curr_sw1 = BUTTON_RELEASED;
      button_state_t prev_sw1 = BUTTON_RELEASED;
      button_state_t curr_sw2 = BUTTON_RELEASED;
      button_state_t prev_sw2 = BUTTON_RELEASED;
     


      /* Repeatedly running part of the task */
      for (;;)
      {
          /* ADD CODE */
          vTaskDelay(pdMS_TO_TICKS(50));

          // check switch press for all 3 switches
          if((PORT_BUTTONS->IN & SW1_MASK) == 0){
            curr_sw1 = BUTTON_PRESSED;
          }
          else{
            curr_sw1 = BUTTON_RELEASED;
          }

          if((PORT_BUTTONS->IN & SW2_MASK) == 0){
            curr_sw2 = BUTTON_PRESSED;
          }
          else{
            curr_sw2 = BUTTON_RELEASED;
          }

         
          ////////////////////////////////////////

          if(curr_sw1 == BUTTON_RELEASED && prev_sw1 == BUTTON_PRESSED){
            xEventGroupSetBits(eg_UI, EVENT_UI_SW1);
          }

          if(curr_sw2 == BUTTON_RELEASED && prev_sw2 == BUTTON_PRESSED){
            xEventGroupSetBits(eg_UI, EVENT_UI_SW2);
          }

         


          // update switch states
          prev_sw1 = curr_sw1;
          prev_sw2 = curr_sw2;
          
            
      }
}

/**
 * @brief
 * Initializes User Push Buttons and creates the corresponding FreeRTOS tasks for SW1 and SW2
 */
void task_sw_init(void)
{
  push_buttons_init(false);

  // Register the Task with FreeRTOS
  xTaskCreate(
      task_switches,
      "Task Switches",
      configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_UI_INPUT,
      NULL);
}

#endif
