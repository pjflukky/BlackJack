/**
 * @file screen.c
 * @author Pakorn Jantacumma
 * @brief 
 * @version 0.1
 * @date 2025-01-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "screen.h"

/**
 * @brief 
 * Used to update the player funds on the LCD
 * @param game_stats
 * Contains the current game stats 
 */
void screen_display_stats_funds(int16_t funds, uint16_t fcolor)
{
    // initialize all associate character
    image_t *F = (image_t *)malloc(sizeof(image_t));
    image_t *U = (image_t *)malloc(sizeof(image_t));
    image_t *N = (image_t *)malloc(sizeof(image_t));
    image_t *D = (image_t *)malloc(sizeof(image_t));
    image_t *S = (image_t *)malloc(sizeof(image_t));
    image_t *colon = (image_t *)malloc(sizeof(image_t));

    // get character image
    font_get_image('F', F);
    font_get_image('U', U);
    font_get_image('N', N);
    font_get_image('D', D);
    font_get_image('S', S);
    font_get_image(':', colon);

     // Turn LCD On F
     lcd_draw_image(
        LOC_GAME_LABEL_FUNDS_X,
        LOC_GAME_LABEL_FUNDS_Y,
        F->width,
        F->height,
        F->bitmap,
        fcolor,
        F->bcolor,
        false);

        // Turn LCD On U
     lcd_draw_image(
        LOC_GAME_LABEL_FUNDS_X + 15,
        LOC_GAME_LABEL_FUNDS_Y,
        U->width,
        U->height,
        U->bitmap,
        fcolor,
        U->bcolor,
        false);

        // Turn LCD On N
     lcd_draw_image(
        LOC_GAME_LABEL_FUNDS_X + 30,
        LOC_GAME_LABEL_FUNDS_Y,
        N->width,
        N->height,
        N->bitmap,
        fcolor,
        N->bcolor,
        false);

        // Turn LCD On D
     lcd_draw_image(
        LOC_GAME_LABEL_FUNDS_X + 45,
        LOC_GAME_LABEL_FUNDS_Y,
        D->width,
        D->height,
        D->bitmap,
        fcolor,
        D->bcolor,
        false);

        // Turn LCD On S
     lcd_draw_image(
        LOC_GAME_LABEL_FUNDS_X + 60,
        LOC_GAME_LABEL_FUNDS_Y,
        S->width,
        S->height,
        S->bitmap,
        fcolor,
        S->bcolor,
        false);

        
        // Turn LCD On :
     lcd_draw_image(
        LOC_GAME_LABEL_FUNDS_X + 75,
        LOC_GAME_LABEL_FUNDS_Y,
        colon->width,
        colon->height,
        colon->bitmap,
        fcolor,
        colon->bcolor,
        false);

        free(F);
        free(U);
        free(N);
        free(D);
        free(S);
        free(colon);

        /// the following code will be stat funds ///
        char str[100] = {0};
        itoa(funds, str, 10); // change integer to string array
      
        for(int i = 0; str[i] != NULL; i++){
            // initialize number character pointer 
            image_t *C = (image_t *)malloc(sizeof(image_t));
            font_get_image(str[i], C);

            // draw the character
            lcd_draw_image(
                LOC_GAME_STATS_FUNDS_X + (i*15),
                LOC_GAME_STATS_FUNDS_Y,
                C->width,
                C->height,
                C->bitmap,
                fcolor,
                C->bcolor,
                false);

            free(C);
        }
}

/**
 * @brief 
 * Used to update the player bet on the LCD
 * @param game_stats
 * Contains the current game stats 
 */
void screen_display_stats_bet(int16_t bet, uint16_t fcolor)
{
    // initialize all associate character
    image_t *B = (image_t *)malloc(sizeof(image_t));
    image_t *E = (image_t *)malloc(sizeof(image_t));
    image_t *T = (image_t *)malloc(sizeof(image_t));
    image_t *colon = (image_t *)malloc(sizeof(image_t));

    // get character image
    font_get_image('B', B);
    font_get_image('E', E);
    font_get_image('T', T);
    font_get_image(':', colon);

     // Turn LCD On B
     lcd_draw_image(
        LOC_GAME_LABEL_BET_X,
        LOC_GAME_LABEL_BET_Y,
        B->width,
        B->height,
        B->bitmap,
        fcolor,
        B->bcolor,
        false);

         // Turn LCD On E
     lcd_draw_image(
        LOC_GAME_LABEL_BET_X + 15,
        LOC_GAME_LABEL_BET_Y,
        E->width,
        E->height,
        E->bitmap,
        fcolor,
        E->bcolor,
        false);

        // Turn LCD On T
     lcd_draw_image(
        LOC_GAME_LABEL_BET_X + 30,
        LOC_GAME_LABEL_BET_Y,
        T->width,
        T->height,
        T->bitmap,
        fcolor,
        T->bcolor,
        false);

         // Turn LCD On colon
     lcd_draw_image(
        LOC_GAME_LABEL_BET_X + 45,
        LOC_GAME_LABEL_BET_Y,
        colon->width,
        colon->height,
        colon->bitmap,
        fcolor,
        colon->bcolor,
        false);

        free(B);
        free(E);
        free(T);
        free(colon);

        /// the following code will be bet amount ///
        char str[100] = {0};
        itoa(bet, str, 10); // change integer to string array
      
        for(int i = 0; str[i] != NULL; i++){
            // initialize number character pointer 
            image_t *C = (image_t *)malloc(sizeof(image_t));
            font_get_image(str[i], C);

            // draw the character
            lcd_draw_image(
                LOC_GAME_STATS_BET_X + (i*15),
                LOC_GAME_STATS_BET_Y,
                C->width,
                C->height,
                C->bitmap,
                fcolor,
                C->bcolor,
                false);

            free(C);
        }
}

/**
 * @brief 
 * Used to update the total of the dealer's hand
 * @param game_stats
 * Contains the current game stats 
 */
void screen_display_stats_dealer_hand(int16_t hand_value, uint16_t fcolor) 
{
     /// the following code will be the dealer hand  ///
     char str[100] = {0};
     itoa(hand_value, str, 10); // change integer to string array
   
     for(int i = 0; str[i] != NULL; i++){
         // initialize number character pointer 
         image_t *C = (image_t *)malloc(sizeof(image_t));
         font_get_image(str[i], C);

         // draw the character
         lcd_draw_image(
            LOC_GAME_STATS_DEALER_HAND_X + (i*15),
            LOC_GAME_STATS_DEALER_HAND_Y,
             C->width,
             C->height,
             C->bitmap,
             fcolor,
             C->bcolor,
             false);

         free(C);
     }
}

/**
 * @brief 
 * Used to update the total of the player's hand
 * @param game_stats
 * Contains the current game stats 
 */
void screen_display_stats_player_hand(int16_t hand_value, uint16_t fcolor) 
{
    /// the following code will be the player hand  ///
    char str[100] = {0};
    itoa(hand_value, str, 10); // change integer to string array
  
    for(int i = 0; str[i] != NULL; i++){
        // initialize number character pointer 
        image_t *C = (image_t *)malloc(sizeof(image_t));
        font_get_image(str[i], C);

        // draw the character
        lcd_draw_image(
           LOC_GAME_STATS_PLAYER_HAND_X + (i*15),
           LOC_GAME_STATS_PLAYER_HAND_Y,
            C->width,
            C->height,
            C->bitmap,
            fcolor,
            C->bcolor,
            false);

        free(C);
    }
}