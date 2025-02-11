/**
 * @file card.c
 * @author Ajinkya Dhamdhere
 * @brief
 * @version 0.1
 * @date 2025-01-13
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "card.h"
#include "fonts.h"
#include "image.h"
#include "io-lcd.h"
#include <sys/types.h>

/**
 * @brief
 *  Draws the specified card
 * @param card
 */

bool card_draw(card_t *card)
{
    if (!card)
        return false;


    uint16_t x_center;
    switch (card->hand_index)
    {
    case 0:
        x_center = CARD_VL_X0_CENTER;
        break;
    case 1:
        x_center = CARD_VL_X1_CENTER;
        break;
    case 2:
        x_center = CARD_VL_X2_CENTER;
        break;
    case 3:
        x_center = CARD_VL_X3_CENTER;
        break;
    case 4:
        x_center = CARD_VL_X4_CENTER;
        break;
    case 5:
        x_center = CARD_VL_X5_CENTER;
        break;
    case 6:
        x_center = CARD_VL_X6_CENTER;
        break;
    default:
        return false; 
    }
    image_t *card_suit_info = image_get_info(card->suit, card);
    image_t *card_id_info = image_get_info(card->card_id, card);

    // Draw outer border
    lcd_draw_rectangle(
        x_center - (CARD_X_OUTER_WIDTH / 2), // x start
        CARD_X_OUTER_WIDTH,
        CARD_HL_Y_CENTER - (CARD_Y_OUTER_HEIGHT / 2), // y start
        CARD_Y_OUTER_HEIGHT,
        card->border_color,
        true);

    // Draw inner white rectangle
    lcd_draw_rectangle(
        x_center - (CARD_X_INNER_WIDTH / 2), // x start
        CARD_X_INNER_WIDTH,
        CARD_HL_Y_CENTER - (CARD_Y_INNER_HEIGHT / 2), // y start
        CARD_Y_INNER_HEIGHT,
        LCD_COLOR_WHITE,
        true);

    // Draw suit at center
    lcd_draw_image(x_center,
                   CARD_HL_Y_CENTER,
                   card_suit_info->width,
                   card_suit_info->height,
                   card_suit_info,
                   LCD_COLOR_BLACK,
                   LCD_COLOR_WHITE,
                   true);


    // Draw card value at top left using lcd_draw_image
    lcd_draw_image(x_center - CARD_VL_X_TEXT_DELTA, 
                   CARD_HL_Y_UPPER,                 
                   card_id_info->width,
                   card_id_info->height,
                   card_id_info,                  
                   LCD_COLOR_RED,                   
                   LCD_COLOR_WHITE,                 
                   true                             
    );
    // Draw card value at bottom right using lcd_draw_image
    lcd_draw_image(x_center + CARD_VL_X_TEXT_DELTA, 
                   CARD_HL_Y_LOWER,                 
                   card_id_info->width,
                   card_id_info->height,
                   card_id_info,                   
                   LCD_COLOR_RED,                  
                   LCD_COLOR_WHITE,                
                   true                            
    );

    return true;
}
