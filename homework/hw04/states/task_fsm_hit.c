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

TaskHandle_t Task_Handle_FSM_HIT;

/**
 * @brief 
 * This task allows the user to take additional cards.  
 * When you enter this state 
 *      - Display the Player Funds in Green.
 *      - Display the Player Bet in Green.
 *      - Display the Player's cards (all visible) 
 *      - Display the Player's hand total (sum up the value of the current hand) 
 * 
 * You will need to monitor the following events
 *      - EVENT_UI_SW1      
 *          - Add a card to the hand
 *          - Display the card on the LCD
 *          - Display the Player's hand total (sum up the value of the current hand) 
 *          - Determine if the Player's hand is equal to 21
 *              - Transition to FSM DEALER HIT
 *          - Determine if the Player's hand is greater than 21
 *              - Transition to FSM HAND COMPLETE 
 *      - EVENT_UI_SW2      
 *          - Transition to FSM DEALER HIT
 * @param param 
 */
void task_fsm_hit(void *param)
{
    bool state_active = false;
    EventBits_t events;
    screen_data_t screen_data;
    int offset = 0;

    /* Suppress warning for unused parameter */
    (void)param;

    while(1)
    {
        if(state_active)
        {
            xEventGroupClearBits(eg_UI, EVENT_UI_SW1 | EVENT_UI_SW2);
            events = xEventGroupWaitBits(eg_UI,
            EVENT_UI_SW1 | EVENT_UI_SW2,
            true,
            false,
            portMAX_DELAY
            );

            if (events & EVENT_UI_SW1){
                xTaskNotifyGive(Task_Handle_FSM_HIT);
            }
            if (events & EVENT_UI_SW2){
                xQueueSend(q_EEPROM, 0, portMAX_DELAY);
            }
            state_active = false;
        }
        else
        {
             // wait for Notify from shuffle states
      ulTaskNotifyTake(true, portMAX_DELAY);
        
       // initiate first two card for the player
        // clear screen just in case
      screen_data.cmd = SCREEN_CMD_CLEAR_ALL;
      xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

      // Take semaphore to access Game_Info
      xSemaphoreTake(sem_Game_Info, portMAX_DELAY);

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

      // Display Player Hand Card #1
      Game_Info.deck->card_index++; // card 3 from deck
      hand_add_card(Game_Info.player_hand, &Game_Info.deck->cards[Game_Info.deck->card_index]); // card 1 from deck
      screen_data.cmd = SCREEN_CMD_DRAW_CARD;
      screen_data.payload.card = Game_Info.player_hand->cards[0];
      xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

       // Display Player Hand Card #2
      Game_Info.deck->card_index++; // card 3 from deck
      hand_add_card(Game_Info.player_hand, &Game_Info.deck->cards[Game_Info.deck->card_index]); // card 1 from deck
      screen_data.cmd = SCREEN_CMD_DRAW_CARD;
      screen_data.payload.card = Game_Info.player_hand->cards[1];
      screen_data.payload.card.hand_index++;
      xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

      // Display hand value 
      screen_data.cmd = SCREEN_CMD_DRAW_STATS_PLAYER_HAND;
      screen_data.payload.hand_value = Game_Info.player_hand->total;
      screen_data.font_color = LCD_COLOR_GREEN;
      xQueueSend(q_Screen, &screen_data, portMAX_DELAY);


      // Give the semaphore back
      xSemaphoreGive(sem_Game_Info);

        }
    }

}

void task_fsm_hit_init(void)
{
    /* Create the Task */
      xTaskCreate(
      task_fsm_hit,
      "Task FSM HIT",
      5*configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_FSM_HIT);
}
