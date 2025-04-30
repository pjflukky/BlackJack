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

TaskHandle_t Task_Handle_FSM_DEALER_SHOW;

/**
 * @brief
 * This task displays the dealers hand to the user.
 *
 * The first card should be visible to the user.
 *
 * The second card should be hidden from the user (Blue border, grey inner rectangle)
 *
 * You will need to monitor the following events
 *      - EVENT_UI_SW2
 *          - Transitions the FSM to PLAYER HIT
 * @param param
 */
void task_fsm_dealer_show(void *param)
{
  bool state_active = false;
  screen_data_t screen_data;
  EventBits_t events;


  /* Suppress warning for unused parameter */
  (void)param;

  while (1)
  {
    if (state_active)
    {
      xEventGroupClearBits(eg_UI, EVENT_UI_SW2);
      events = xEventGroupWaitBits(eg_UI,
                                   EVENT_UI_SW2,
                                   true,
                                   false,
                                   portMAX_DELAY);

      if (events & EVENT_UI_SW2)
      {
        xTaskNotifyGive(Task_Handle_FSM_HIT);
      }
      state_active = false;
    }
    else
    {
      // wait for Notify from shuffle states
      ulTaskNotifyTake(true, portMAX_DELAY);

      // activate the state
      state_active = true;

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

      // Get and show the dealer hand card #1
      hand_add_card(Game_Info.dealer_hand, &Game_Info.deck->cards[Game_Info.deck->card_index]); // card 0 from deck

      // Display Dealer Hand Card #1
      screen_data.cmd = SCREEN_CMD_DRAW_CARD;
      screen_data.payload.card = Game_Info.dealer_hand->cards[0];
      
      xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

      // Display Dealer Hand Card #2
      Game_Info.deck->card_index++;
      hand_add_card(Game_Info.dealer_hand, &Game_Info.deck->cards[Game_Info.deck->card_index]); // card 3 from deck

      screen_data.cmd = SCREEN_CMD_DRAW_CARD;

      screen_data.payload.card = Game_Info.dealer_hand->cards[Game_Info.deck->card_index];
      screen_data.payload.card.hidden = true;
      screen_data.payload.card.hand_index++;
      xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

      // Give the semaphore back
      xSemaphoreGive(sem_Game_Info);
    }
  }
}

void task_fsm_dealer_show_init(void)
{
  /* Create the Task */
  xTaskCreate(
      task_fsm_dealer_show,
      "Task FSM DEALER SHOW",
      5 * configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_FSM_DEALER_SHOW);
}
