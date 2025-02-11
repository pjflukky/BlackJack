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

    // Check to make sure it is a card
    if (!card)
    {
        return false;
    }
    // Initialize the x coordinate based on hand_index
    uint16_t x_center;

    // Change the center of the card based on the hand_index(how many times the button has been clicked)
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

    //     int card_suit_width = 0;
    // int card_suit_height= 0;
    // uint8_t *card_suit_bitmap;

    // Draw outer border
    lcd_draw_rectangle(
        x_center - (CARD_X_OUTER_WIDTH / 2), // x start
        CARD_X_OUTER_WIDTH,
        CARD_HL_Y_CENTER - (CARD_Y_OUTER_HEIGHT / 2), // y start
        CARD_Y_OUTER_HEIGHT,
        card->border_color,
        false);

    // Draw inner white rectangle
    lcd_draw_rectangle(
        x_center - (CARD_X_INNER_WIDTH / 2), // x start
        CARD_X_INNER_WIDTH,
        CARD_HL_Y_CENTER - (CARD_Y_INNER_HEIGHT / 2), // y start
        CARD_Y_INNER_HEIGHT,
        LCD_COLOR_WHITE,
        false);

    // Create the image of the number/letter of the card
    image_t card_id_image;
    font_get_image(card->card_id, &card_id_image);

    // If the Suit is a heart, draw based accordingly on width, height, and bitmap
    if (card->suit == IMAGE_TYPE_HEART)
    {
        // Draw suit at center
        lcd_draw_image(x_center,
                       CARD_HL_Y_CENTER,
                       IMAGE_PIXELS_WIDTH_HEART,
                       IMAGE_PIXELS_HEIGHT_HEART,
                       IMAGE_BITMAP_HEART,
                       LCD_COLOR_RED,
                       LCD_COLOR_WHITE,
                       true);

        // Draw card value at top left using lcd_draw_image
        lcd_draw_image(x_center - CARD_VL_X_TEXT_DELTA,
                       CARD_HL_Y_UPPER,
                       card_id_image.width,
                       card_id_image.height,
                       card_id_image.bitmap,
                       LCD_COLOR_RED,
                       LCD_COLOR_WHITE,
                       true);
        // Draw card value at bottom right using lcd_draw_image
        lcd_draw_image(x_center + CARD_VL_X_TEXT_DELTA,
                       CARD_HL_Y_LOWER,
                       card_id_image.width,
                       card_id_image.height,
                       card_id_image.bitmap,
                       LCD_COLOR_RED,
                       LCD_COLOR_WHITE,
                       true);
    }

    // If the Suit is a club, draw based accordingly on width, height, and bitmap
    if (card->suit == IMAGE_TYPE_CLUB)
    {
        // Draw suit at center
        lcd_draw_image(x_center,
                       CARD_HL_Y_CENTER,
                       IMAGE_PIXELS_WIDTH_CLUB,
                       IMAGE_PIXELS_HEIGHT_CLUB,
                       IMAGE_BITMAP_CLUB,
                       LCD_COLOR_BLACK,
                       LCD_COLOR_WHITE,
                       true);

        // Draw card value at top left using lcd_draw_image
        lcd_draw_image(x_center - CARD_VL_X_TEXT_DELTA,
                       CARD_HL_Y_UPPER,
                       card_id_image.width,
                       card_id_image.height,
                       card_id_image.bitmap,
                       LCD_COLOR_BLACK,
                       LCD_COLOR_WHITE,
                       true);
        // Draw card value at bottom right using lcd_draw_image
        lcd_draw_image(x_center + CARD_VL_X_TEXT_DELTA,
                       CARD_HL_Y_LOWER,
                       card_id_image.width,
                       card_id_image.height,
                       card_id_image.bitmap,
                       LCD_COLOR_BLACK,
                       LCD_COLOR_WHITE,
                       true);
    }

    // If the Suit is a spade, draw based accordingly on width, height, and bitmap
    if (card->suit == IMAGE_TYPE_SPADE)
    {
        // Draw suit at center
        lcd_draw_image(x_center,
                       CARD_HL_Y_CENTER,
                       IMAGE_PIXELS_WIDTH_SPADE,
                       IMAGE_PIXELS_HEIGHT_SPADE,
                       IMAGE_BITMAP_SPADE,
                       LCD_COLOR_BLACK,
                       LCD_COLOR_WHITE,
                       true);
        // Draw card value at top left using lcd_draw_image
        lcd_draw_image(x_center - CARD_VL_X_TEXT_DELTA,
                       CARD_HL_Y_UPPER,
                       card_id_image.width,
                       card_id_image.height,
                       card_id_image.bitmap,
                       LCD_COLOR_BLACK,
                       LCD_COLOR_WHITE,
                       true);
        // Draw card value at bottom right using lcd_draw_image
        lcd_draw_image(x_center + CARD_VL_X_TEXT_DELTA,
                       CARD_HL_Y_LOWER,
                       card_id_image.width,
                       card_id_image.height,
                       card_id_image.bitmap,
                       LCD_COLOR_BLACK,
                       LCD_COLOR_WHITE,
                       true);
    }

    // If the Suit is a diamond, draw based accordingly on width, height, and bitmap
    if (card->suit == IMAGE_TYPE_DIAMOND)
    {
        // Draw suit at center
        lcd_draw_image(x_center,
                       CARD_HL_Y_CENTER,
                       IMAGE_PIXELS_WIDTH_DIAMOND,
                       IMAGE_PIXELS_HEIGHT_DIAMOND,
                       IMAGE_BITMAP_DIAMOND,
                       LCD_COLOR_RED,
                       LCD_COLOR_WHITE,
                       true);
        // Draw card value at top left using lcd_draw_image
        lcd_draw_image(x_center - CARD_VL_X_TEXT_DELTA,
                       CARD_HL_Y_UPPER,
                       card_id_image.width,
                       card_id_image.height,
                       card_id_image.bitmap,
                       LCD_COLOR_RED,
                       LCD_COLOR_WHITE,
                       true);
        // Draw card value at bottom right using lcd_draw_image
        lcd_draw_image(x_center + CARD_VL_X_TEXT_DELTA,
                       CARD_HL_Y_LOWER,
                       card_id_image.width,
                       card_id_image.height,
                       card_id_image.bitmap,
                       LCD_COLOR_RED,
                       LCD_COLOR_WHITE,
                       true);
    }

    return true;
}
