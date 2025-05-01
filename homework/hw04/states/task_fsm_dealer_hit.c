/**
 * @file task_fsm_dealer_hit.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-01-15
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "hw04.h"

TaskHandle_t Task_Handle_FSM_DEALER_HIT;

/**
 * @brief
 * This task draws cards for the dealers hand
 * When you enter this state
 *      - Display the Player Funds in Green
 *      - Display the Player Bet in Green
 *      - Erase the Player's cards
 *      - Add/display cards to the Dealer's hand
 *      - Update the Dealer's hand total for each card added
 *      - Delay 1 second between drawing cards
 *      - Continue to add cards to the Dealer's hand until the total
 *        of the Dealer's hand is greater than OR equal to 17
 *      - When the Dealer's hand is greater than or equal to 17,
 *        transition to HAND_COMPLETE
 * @param param
 */
void task_fsm_dealer_hit(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;
    screen_data_t screen_data;
    EventBits_t events;
    bool state_active = false;
    int offset = 0;

    while (1)
    {

        // wait for Notify from shuffle states
        ulTaskNotifyTake(true, portMAX_DELAY);

        // activate the state
        state_active = true;
        offset = 0;

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

        // Display player hand value
        screen_data.cmd = SCREEN_CMD_DRAW_STATS_PLAYER_HAND;
        screen_data.payload.hand_value = Game_Info.player_hand->total;
        int player_value = screen_data.payload.hand_value;
        screen_data.font_color = LCD_COLOR_GREEN;
        xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

        // now display first two card of the dealer initially in dealer show states
        // Display Dealer Hand Card #1
        screen_data.cmd = SCREEN_CMD_DRAW_CARD;
        screen_data.payload.card = Game_Info.dealer_hand->cards[0];
        xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
        // Display Dealer Hand Card #2
        offset++;
        screen_data.payload.card = Game_Info.dealer_hand->cards[1];
        screen_data.payload.card.hidden = false; // initially true
        screen_data.payload.card.hand_index = offset;
        xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

        // Display dealer hand value
        screen_data.cmd = SCREEN_CMD_DRAW_STATS_DEALER_HAND;
        screen_data.payload.hand_value = Game_Info.dealer_hand->total;
        screen_data.font_color = LCD_COLOR_RED;
        xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

        // Give the semaphore back
        xSemaphoreGive(sem_Game_Info);

        int hand_value = Game_Info.dealer_hand->total;

        while (hand_value < 17)
        {
            // Take semaphore to access Game_Info
            xSemaphoreTake(sem_Game_Info, portMAX_DELAY);

            vTaskDelay(pdMS_TO_TICKS(1000));
            // Display Dealer Hand Card #XX
            Game_Info.deck->card_index++;
            hand_add_card(Game_Info.dealer_hand, &Game_Info.deck->cards[Game_Info.deck->card_index]); 

            // Update the local variable with the new total
            hand_value = Game_Info.dealer_hand->total;

            // display the new card and new hand value to the screen
            screen_data.cmd = SCREEN_CMD_DRAW_STATS_DEALER_HAND;
            screen_data.payload.hand_value = hand_value;
            screen_data.font_color = LCD_COLOR_RED;
            xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

            offset++;
            screen_data.cmd = SCREEN_CMD_DRAW_CARD;
            screen_data.payload.card = Game_Info.dealer_hand->cards[offset];
            screen_data.payload.card.hidden = false; // initially true
            screen_data.payload.card.hand_index = offset;
            xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

            // Give the semaphore back
            xSemaphoreGive(sem_Game_Info);
        }
         xTaskNotifyGive(Task_Handle_FSM_HAND_COMPLETE);
    }
}

void task_fsm_dealer_hit_init(void)
{
    /* Create the Task */
    xTaskCreate(
        task_fsm_dealer_hit,
        "Task FSM Dealer Hit",
        5 * configMINIMAL_STACK_SIZE,
        NULL,
        ECE353_TASK_PRIORITY_FSM,
        &Task_Handle_FSM_DEALER_HIT);
}