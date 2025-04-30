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

TaskHandle_t Task_Handle_FSM_START;
QueueHandle_t q_eeprom_fsm_start;

/**
 * @brief 
 * This state is used to initialize the game. 
 * 
 * The initialization includes:
 *      - Print the banner with team information to the console 
 *      - Print the high score from the eeprom to the console
 *      - Initialize the player's funds to 1000
 *      - Initialize the initial bet to be 50
 *      - Display the ECE353 Blackjack start screen 
 *
 * You will need to monitor the following events
 *      - EVENT_UI_SW2      
 *          - Transition to state SHUFFLE 
 *      - EVENT_UI_IO_EXP_INT   
 *          - Reset the High Score in the EEPROM to 0.
 * 
 * @param param 
 */
void task_fsm_start(void *param)
{
    bool state_active = false;
    EventBits_t events;
    screen_data_t screen_data;
    eeprom_msg_t msg;
    QueueHandle_t return_queue = xQueueCreate(1, sizeof(uint16_t));


    /* Suppress warning for unused parameter */
    (void)param;

    /* Send the Clear Screen Escape Sequence*/
    task_print("\x1b[2J\x1b[;H");
    task_print("**************************************************\n\r");
    task_print("* %s\n\r", APP_DESCRIPTION);
    task_print("* Date: %s\n\r", __DATE__);
    task_print("* Time: %s\n\r", __TIME__);
    task_print("* %s\n\r", APP_MEMBERS);
    task_print("* %s\n\r", APP_TEAM_NUM);
    task_print("**************************************************\n\r");

    while(1)
    {
        if(state_active)
        {
            xEventGroupClearBits(eg_UI, EVENT_UI_IO_EXP_INT | EVENT_UI_SW2);
            events = xEventGroupWaitBits(eg_UI,
            EVENT_UI_IO_EXP_INT | EVENT_UI_SW2,
            true,
            false,
            portMAX_DELAY
            );

            if (events & EVENT_UI_SW2){
                xTaskNotifyGive(Task_Handle_FSM_SHUFFLE);
            }
            if (events & EVENT_UI_IO_EXP_INT){
                xQueueSend(q_EEPROM, 0, portMAX_DELAY);
            }
            state_active = false;
        }
        else
        {
            //wait for Notify from hw04.c
            ulTaskNotifyTake(true, portMAX_DELAY);

            // Set up the game
            xSemaphoreTake(sem_Game_Info, portMAX_DELAY);

            // Initialize player funds and bet
            Game_Info.player_funds = 1000;
            Game_Info.player_bet = 50;

             // Release semaphore
            xSemaphoreGive(sem_Game_Info);

             // activate the state
             state_active = true;

            // Read high score from EEPROM
            msg.operation = EEPROM_READ;
            msg.return_queue = return_queue;
            xQueueSend(q_EEPROM, &msg, portMAX_DELAY);
            uint16_t high_score = 0;
            xQueueReceive(return_queue, &high_score, portMAX_DELAY);

            // clear screen just in case
            screen_data.cmd = SCREEN_CMD_CLEAR_ALL;
            xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

             // Display start screen
             screen_data.cmd = SCREEN_CMD_DRAW_SPLASH_SCREEN;
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

            task_print_info("High Score: %d", high_score);
            task_print_info("current state: start");


        }
    }

}

void task_fsm_start_init(void)
{
    q_eeprom_fsm_start = xQueueCreate(1, sizeof(eeprom_msg_t));

    /* Create the Task */
      xTaskCreate(
      task_fsm_start,
      "Task FSM Start",
      2*configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_FSM_START);
}
