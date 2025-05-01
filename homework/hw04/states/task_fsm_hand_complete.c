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

TaskHandle_t Task_Handle_FSM_HAND_COMPLETE;
QueueHandle_t q_eeprom_fsm_hand_complete;

char WIN[] = "Win!";
char PUSH[] = "Push";
char LOSE[] = "Lose";

/**
 * @brief
 * This task determines if the user wins or looses the current hand.
 *
 * If the players wins
 *      - Add the bet amount to the player funds
 *      - Display the player funds in Green
 *      - Print "Win!" Green to the LCD screen at LOC_HAND_STATUS_X, LOC_HAND_STATUS_Y
 *      - Blink the Player Funds On/Off 4 times.
 *      - Use a delay of 250mS between blinking On/Off
 *      - Display the player's current win streak on the IO Expander
 *
 * If the players loses
 *      - Subtract the bet amount to the player funds
 *      - Display the player funds in Red
 *      - Print "Lose" in Red to the LCD screen at LOC_HAND_STATUS_X, LOC_HAND_STATUS_Y
 *      - Blink the Player Funds On/Off 4 times.
 *      - Use a delay of 250mS between blinking On/Off
 *      - Set the player's current win streak to 0 and update the IO Expander
 *
 * If the players pushes (tie)
 *      - Print "Push" in Grey to the LCD screen at LOC_HAND_STATUS_X, LOC_HAND_STATUS_Y
 *      - Delay for 2 seconds
 *
 * In all situations
 *      - Check to see if a new high score for the player funds. Write new high scores to the EEPROM.
 *      - If the player funds is equal to 0, transition to the START state.
 *      - If the player funds are greater than 0, check to see if the remaining cards in the deck are greater than 15
 *          - If greater than or equal to 15, transition to the BET state
 *          - If less than 15, transition to the SHUFFLE state
 * @param param
 */
void task_fsm_hand_complete(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;

    bool state_active = false;
    EventBits_t events;
    screen_data_t screen_data;
    uint8_t led_command = 0x00;

    while (1)
    {
        if (state_active)
        {
            xEventGroupClearBits(eg_UI, EVENT_UI_SW1 | EVENT_UI_SW2);

            // Take semaphore to access Game_Info
            xSemaphoreTake(sem_Game_Info, portMAX_DELAY);

            // Check to see if a new high score for the player funds. Write new high scores to the EEPROM.
            eeprom_msg_t msg;
            int score = 0;
            msg.operation = EEPROM_READ;
            msg.return_queue = xQueueCreate(1, sizeof(QueueHandle_t));
            xQueueSend(q_EEPROM, &msg, portMAX_DELAY);
            if (Game_Info.player_funds > score)
            {
                msg.score = Game_Info.player_funds;
                msg.operation = EEPROM_WRITE;
                xQueueSend(q_EEPROM, &msg, portMAX_DELAY);
            }

            // If the player funds is equal to 0, transition to the START state.
            if (Game_Info.player_funds == 0)
            {
                xTaskNotifyGive(Task_Handle_FSM_START);
            }
            else
            {

                if (51 - Game_Info.deck->card_index <= 14)
                {
                    xTaskNotifyGive(Task_Handle_FSM_SHUFFLE);
                }
                else
                {
                    xTaskNotifyGive(Task_Handle_FSM_BET);
                }
            }
            xSemaphoreGive(sem_Game_Info);
            state_active = false;
        }
        else
        {
            // wait for Notify from shuffle states
            ulTaskNotifyTake(true, portMAX_DELAY);

            // activate the state
            state_active = true;

            xSemaphoreTake(sem_Game_Info, portMAX_DELAY);

            // LOGIC FOR WIN
            if ((Game_Info.player_hand->total > Game_Info.dealer_hand->total && Game_Info.player_hand->total <= 21) || Game_Info.dealer_hand->total > 21 )
            {
                // Add the bet amount to the player funds
                Game_Info.player_funds += Game_Info.player_bet;
                // Display the player funds in Green
                screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
                screen_data.font_color = LCD_COLOR_GREEN;
                screen_data.payload.funds = Game_Info.player_funds;
                xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                // Print "Win!" Green to the LCD screen at LOC_HAND_STATUS_X, LOC_HAND_STATUS_Y
                screen_data.cmd = SCREEN_CMD_DRAW_HAND_STATUS;
                screen_data.payload.str_ptr = WIN;
                xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                // Blink the Player Funds On/Off 4 times.
                // Use a delay of 250mS between blinking On/Off
                for (int i = 0; i < 4; i++)
                {
                    screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
                    screen_data.font_color = LCD_COLOR_BLACK;
                    xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                    vTaskDelay(pdMS_TO_TICKS(250));
                    screen_data.font_color = LCD_COLOR_GREEN;
                    xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                    
                }

                // Display the player's current win streak on the IO Expander
                // TODO
                led_command = (led_command << 1) + 1;
                xQueueSend(q_IO_Exp, &led_command, portMAX_DELAY);

            }

            // LOGIC FOR PUSH
            else if (Game_Info.player_hand->total == Game_Info.dealer_hand->total)
            {
                // Print "Win!" Green to the LCD screen at LOC_HAND_STATUS_X, LOC_HAND_STATUS_Y
                screen_data.cmd = SCREEN_CMD_DRAW_HAND_STATUS;
                screen_data.payload.str_ptr = PUSH;
                xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

                vTaskDelay(pdMS_TO_TICKS(2000));
            }

            // LOGIC FOR LOSE
            else
            {
                // Subtract the bet amount to the player funds
                Game_Info.player_funds -= Game_Info.player_bet;
                // Display the player funds in Red
                screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
                screen_data.payload.funds = Game_Info.player_funds;
                screen_data.font_color = LCD_COLOR_RED;
                xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                // Print "Lose" in Red to the LCD screen at LOC_HAND_STATUS_X, LOC_HAND_STATUS_Y
                screen_data.cmd = SCREEN_CMD_DRAW_HAND_STATUS;
                screen_data.payload.str_ptr = LOSE;
                xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                // Blink the Player Funds On/Off 4 times.
                // Use a delay of 250mS between blinking On/Off
                for (int i = 0; i < 4; i++)
                {
                    screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
                    screen_data.font_color = LCD_COLOR_BLACK;
                    xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                    vTaskDelay(pdMS_TO_TICKS(250));
                    screen_data.font_color = LCD_COLOR_GREEN;
                    xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                    
                }

                // Set the player's current win streak to 0 and update the IO Expander
                // TODO
                led_command = 0x00;
                xQueueSend(q_IO_Exp, &led_command, portMAX_DELAY);
            }
            xSemaphoreGive(sem_Game_Info);
        }
    }
}

void task_fsm_hand_complete_init(void)
{
    /* Create the queue to return the high score */
    q_eeprom_fsm_hand_complete = xQueueCreate(1, sizeof(eeprom_msg_t));

    /* Create the Task */
    xTaskCreate(
        task_fsm_hand_complete,
        "Task FSM Hand Complete",
        5 * configMINIMAL_STACK_SIZE,
        NULL,
        ECE353_TASK_PRIORITY_FSM,
        &Task_Handle_FSM_HAND_COMPLETE);
}
