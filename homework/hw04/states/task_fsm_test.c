/**
 * @file task_fsm_start.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hw04.h"

extern char APP_DESCRIPTION[];
extern char APP_MEMBERS[];
extern char APP_TEAM_NUM[];

TaskHandle_t Task_Handle_FSM_TEST;
QueueHandle_t q_eeprom_fsm_test;

void task_fsm_test(void *param)
{
    EventBits_t active_events = 0;

    /* Suppress warning for unused parameter */
    (void)param;

    /* Send the Clear Screen Escape Sequence*/
    task_print("\x1b[2J\x1b[;H");
    task_print("**************************************************\n\r");
    task_print("* %s\n\r", "HW04 TEST TASK");
    task_print("* Date: %s\n\r", __DATE__);
    task_print("* Time: %s\n\r", __TIME__);
    task_print("* %s\n\r", APP_MEMBERS);
    task_print("* %s\n\r", APP_TEAM_NUM);
    task_print("**************************************************\n\r");

    while(1)
    {
        /* ADD CODE */
        /* Detect eg_UI events */
        active_events = xEventGroupWaitBits(
            eg_UI,
            EVENT_UI_SW1 | EVENT_UI_SW2 | EVENT_UI_SW3 | EVENT_UI_JOY_UP | EVENT_UI_JOY_DOWN,
            true,
            false,
            portMAX_DELAY
        );


       if(active_events & EVENT_UI_SW1)
       {
           task_print_info("SW1 pressed");

       /* ADD CODE */
       /* Write to the IO Expander to turn on the LEDS */
       /* Remember, you will need to send a message to the IO Expander Gate Keeper task */
       /* You cannot directly access hardware resources */
       }

       if(active_events & EVENT_UI_SW2)
       {
           task_print_info("SW2 pressed");
           eeprom_msg_t msg;

             /* read score from EEPROM */
           /* Remember, you will need to send a message to the EEPROM Gate Keeper task */
           /* You cannot directly access hardware resources */

            /* Create a queue to receive the score back from the EEPROM task */
            QueueHandle_t return_queue = xQueueCreate(1, sizeof(uint16_t));

            /* Set up the message to read from EEPROM */
            msg.operation = EEPROM_READ;
            msg.return_queue = return_queue;

            /* Send the read request to the EEPROM task */
            xQueueSend(q_EEPROM, &msg, portMAX_DELAY);

            /* Wait for the score to be returned */
            uint16_t current_score = 0;
            xQueueReceive(return_queue, &current_score, portMAX_DELAY);

            /* Increment the score read from EEPROM */
            task_print_info("HIGH SCORE READ: %d", current_score);
            current_score++;
            task_print_info("HIGH SCORE WRITE: %d", current_score);

            /* Write the new score to EEPROM */
            msg.operation = EEPROM_WRITE;
            msg.score = current_score;
            msg.return_queue = NULL; /* No return needed for a write operation */
            xQueueSend(q_EEPROM, &msg, portMAX_DELAY);

            /* Clean up the queue */
           // vQueueDelete(return_queue);
        }


       if(active_events & EVENT_UI_JOY_DOWN)
       {
            task_print_info("Joystick Moved Down");

           /* ADD CODE */
           /* Remember, you will need to send a message to the LCD Gate Keeper task */
           /* You cannot directly access hardware resources */

            /* Display the test number for the funds, bet, player, and dealer hand */
       }

       if(active_events & EVENT_UI_JOY_UP)
       {
            task_print_info("Joystick Moved Up");

           /* ADD CODE */
           /* Remember, you will need to send a message to the LCD Gate Keeper task */
           /* You cannot directly access hardware resources */

            /* Display the test number for the funds, bet, player, and dealer hand */

       }

       if(active_events & EVENT_UI_IO_EXP_INT)
       {
           task_print_info("U602 pressed");

           /* ADD CODE */
           /* Reset the high score in the EEPROM */
           /* Remember, you will need to send a message to the EEPROM Gate Keeper task */
           /* You cannot directly access hardware resources */
 
       }
    }
}

void task_fsm_test_init(void)
{
    q_eeprom_fsm_test = xQueueCreate(1, sizeof(eeprom_msg_t));

    /* Create the Task */
      xTaskCreate(
      task_fsm_test,
      "Task FSM Test",
      2*configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_FSM_TEST);
}
