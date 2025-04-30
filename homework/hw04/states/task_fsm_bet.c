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

TaskHandle_t Task_Handle_FSM_BET;

/**
 * @brief 
 * This task allows the user to select the amount used for the next bet.  
 * When you enter this state 
 *      - Display the IMAGE_BITMAP_BET_SCREEN in the center of the screen.
 *      - Display the Player Funds in Green.
 *      - Display the Player Bet in Green.
 * 
 * You will need to monitor the following events
 *      - EVENT_UI_JOY_DOWN 
 *          - Decreases the bet by $50.  
 *          - Cannot decrease the bet to a value lower than $50
 *          - Update the LCD with the bet value
 *      - EVENT_UI_JOY_UP   
 *          - Increases the bet by $50.  
 *          - Cannot increase the bet to a value larger than the player funds 
 *          - Update the LCD with the bet value
 *      - EVENT_UI_SW1      
 *          - Transitions the FSM to DEALER SHOW 
 * @param param 
 */
void task_fsm_bet(void *param)
{
    bool state_active = false;
    screen_data_t screen_data;
    EventBits_t events;

    /* Suppress warning for unused parameter */
    (void)param;

    while(1)
    {
        if(state_active)
        {   // clear before check event
            xEventGroupClearBits(eg_UI, EVENT_UI_SW1 | EVENT_UI_JOY_UP | EVENT_UI_JOY_DOWN);
            events = xEventGroupWaitBits(
            eg_UI,
            EVENT_UI_SW1 | EVENT_UI_JOY_UP | EVENT_UI_JOY_DOWN,
            true,
            false,
            portMAX_DELAY
            );

            //event joy up
            if (events & EVENT_UI_JOY_UP){
                if(Game_Info.player_bet + 50 <= Game_Info.player_funds)
                    Game_Info.player_bet += 50;

                    // clear screen just in case
                screen_data.cmd = SCREEN_CMD_CLEAR_ALL;
                xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

                // Display bet screen
                screen_data.cmd = SCREEN_CMD_DRAW_BET_SCREEN;
                xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

            // Display funds
            screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
            screen_data.payload.funds = Game_Info.player_funds;
            screen_data.font_color = LCD_COLOR_GREEN;
            xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

            // Display bet
            screen_data.cmd = SCREEN_CMD_DRAW_STATS_BET;
            screen_data.payload.bet = Game_Info.player_bet;
            screen_data.font_color = LCD_COLOR_GREEN;
            xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
            }

            //event joy down
            if (events & EVENT_UI_JOY_DOWN){
                if(Game_Info.player_bet - 50 >= 50)
                    Game_Info.player_bet -= 50;

                    // clear screen just in case
                screen_data.cmd = SCREEN_CMD_CLEAR_ALL;
                xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

                // Display bet screen
                screen_data.cmd = SCREEN_CMD_DRAW_BET_SCREEN;
                xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

            // Display funds
            screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
            screen_data.payload.funds = Game_Info.player_funds;
            screen_data.font_color = LCD_COLOR_GREEN;
            xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

            // Display bet
            screen_data.cmd = SCREEN_CMD_DRAW_STATS_BET;
            screen_data.payload.bet = Game_Info.player_bet;
            screen_data.font_color = LCD_COLOR_GREEN;
            xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
            }

            //event switch 1
            if (events & EVENT_UI_SW1){
                xTaskNotifyGive(Task_Handle_FSM_DEALER_SHOW);
                state_active = false;
            }
              
        }

        else
        {
             //wait for Notify from shuffle states
             ulTaskNotifyTake(true, portMAX_DELAY);

            // activate the state
            state_active = true;

            // clear screen just in case
            screen_data.cmd = SCREEN_CMD_CLEAR_ALL;
            xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

            // Display bet screen
            screen_data.cmd = SCREEN_CMD_DRAW_BET_SCREEN;
            xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

           // Display funds
           screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
           screen_data.payload.funds = Game_Info.player_funds;
           screen_data.font_color = LCD_COLOR_GREEN;
           xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

           // Display bet
           screen_data.cmd = SCREEN_CMD_DRAW_STATS_BET;
           screen_data.payload.bet = Game_Info.player_bet;
           screen_data.font_color = LCD_COLOR_GREEN;
           xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

           task_print_info("current state: bet");
        }
    }

}

void task_fsm_bet_init(void)
{
    /* Create the Task */
      xTaskCreate(
      task_fsm_bet,
      "Task FSM BET",
      5*configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_FSM_BET);
}
