/**
 * @file task_lcd_game_stats.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2025-01-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "task_screen.h"
#if defined(HW04)

QueueHandle_t q_Screen;

/******************************************************************************
 * FreeRTOS Related Functions
 ******************************************************************************/

/**
 * @brief
 * @param param
 */
void task_screen(void *param)
{
    screen_data_t lcd_data;
    /* Suppress warning for unused parameter */
    (void)param;

    /* Repeatedly running part of the task */
    for (;;)
    {
        /* ADD CODE */
        xQueueReceive(q_Screen, &lcd_data, portMAX_DELAY);

        switch (lcd_data.cmd)
        {

          case SCREEN_CMD_DRAW_BET_SCREEN:
          {
              // draw a start screen
            lcd_draw_image(
              160,
              120,
              IMAGE_PIXELS_WIDTH_BET_SCREEN,
              IMAGE_PIXELS_HEIGHT_BET_SCREEN,
              IMAGE_BITMAP_BET_SCREEN,
              LCD_COLOR_BLUE,
              LCD_COLOR_BLACK,
              true
            );
            break;
          }

        case SCREEN_CMD_DRAW_SPLASH_SCREEN:
        {
            // draw a start screen
            lcd_draw_image(
              160,
              120,
              IMAGE_PIXELS_WIDTH_START_SCREEN,
              IMAGE_PIXELS_HEIGHT_START_SCREEN,
              IMAGE_BITMAP_START_SCREEN,
              LCD_COLOR_RED,
              LCD_COLOR_BLACK,
              true
            );
            break;
        }

        case SCREEN_CMD_DRAW_CARD:
        {
            /* The operation indicates that we are drawing a card,
              so treat the union as a card */
            card_draw(&lcd_data.payload.card);
            break;
        }
        case SCREEN_CMD_DRAW_STATS_FUNDS:
        {
            /* The operation indicated we are drawing the Funds to the LCD,
              so treat the union as funds */
            screen_display_stats_funds(lcd_data.payload.funds, lcd_data.font_color);
            break;
        }
        case SCREEN_CMD_CLEAR_ALL:
        {
            /* The operation indicated we are clearing the LCD,
              so treat the union as funds */
            lcd_clear_screen(LCD_COLOR_BLACK);
            break;
        }
        case SCREEN_CMD_DRAW_STATS_DEALER_HAND:
        {
            /* The operation indicated we are drawing the Dealer Hand to the LCD,
              so treat the union as funds */
            screen_display_stats_dealer_hand(lcd_data.payload.hand_value, lcd_data.font_color);
            break;
        }
        case SCREEN_CMD_DRAW_STATS_PLAYER_HAND:
        {
            /* The operation indicated we are drawing the Player Hand to the LCD,
              so treat the union as funds */
            screen_display_stats_player_hand(lcd_data.payload.hand_value, lcd_data.font_color);
            break;
        }
        case SCREEN_CMD_DRAW_STATS_BET:
        {
            /* The operation indicated we are drawing the Player Hand to the LCD,
              so treat the union as funds */
            screen_display_stats_bet(lcd_data.payload.bet, lcd_data.font_color);
            break;
        }

        
        }
    }
}

void task_screen_init(void)
{
    /* Initialize the LCD hardware */
    ece353_enable_lcd();

    /* Create LCD Queues */
    q_Screen = xQueueCreate(1, sizeof(screen_data_t));

    xTaskCreate(
        task_screen,
        "Task Screen",
        10 * configMINIMAL_STACK_SIZE,
        NULL,
        ECE353_TASK_PRIORITY_UI_OUTPUT,
        NULL);
}

#endif