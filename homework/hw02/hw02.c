/**
 * @file hw01.c
 * @author Pakorn Ajinkya
 * @brief
 * @version 0.1
 * @date 2025-01-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "hw02.h"

#if defined(HW02)

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: S25 HW02";
char STUDENTS[] = "Your Names";

/* Random Number Generator Handle*/
cyhal_trng_t trng_obj;

/* Allocate space for two decks of cards */
deck_t *DeckA;
deck_t *DeckB;

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE.
 *
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void peripheral_init(void)
{
    /* Initialize the hardware random number generator*/
    cyhal_trng_init(&trng_obj);

    /* Enable the push buttons*/
    push_buttons_init(false);

    ece353_enable_lcd();

    joystick_init();

    console_init();

    timer_050_ms_start();
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 */
void main_app(void)
{

    printf("\x1b[2J\x1b[;H");
    printf("**************************************************\n\r");
    printf("* %s\n\r", APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    peripheral_init();
    
    uint32_t reg_val;
    // Allocate the necessary space for both DeckA and DeckB
    DeckA = (deck_t *)malloc(sizeof(deck_t));
    DeckB = (deck_t *)malloc(sizeof(deck_t));
    ;

    // If either are null just return
    if (DeckA == NULL || DeckB == NULL)
    {
        printf("DeckA or DeckB is null");
        return;
    }

    // Initialize the two decks by calling our deck_init function
    deck_init(DeckA);
    deck_init(DeckB);

    // Control Deck is at position 0 and Random at 6
    DeckA->cards[0].hand_index = 0;
    DeckB->cards[0].hand_index = 0;

    // Draw the first card of each deck
    card_draw(&DeckA->cards[0]);
    card_draw(&DeckB->cards[0]);

    screen_display_stats_player_hand(0, LCD_COLOR_WHITE);
    int card_index = 0;
    while (1)
    {
        // button value
        reg_val = REG_PUSH_BUTTON_IN;
        // If Button 1 is pressed
        if ((reg_val & SW1_MASK) == 0x00)
        {
            deck_randomize(DeckB);
            card_index = 0;
            DeckA->cards[card_index].hand_index = 0;
            DeckB->cards[card_index].hand_index = 6;

            card_draw(&DeckA->cards[card_index]);
            card_draw(&DeckB->cards[card_index]);

            screen_display_stats_player_hand(card_index, LCD_COLOR_WHITE);
        }

        joystick_position_t joystick_position = joystick_get_pos();

        if (joystick_position == JOYSTICK_POS_UP){
            card_index++;
            if (card_index > 53){
                card_index = 0;
            }
        }
        else if (joystick_position == JOYSTICK_POS_DOWN){
            card_index--;
            if (card_index < 0){
                card_index = 51;
            }
        }

        if (joystick_position == JOYSTICK_POS_UP || joystick_position == JOYSTICK_POS_DOWN){
            DeckA->cards[card_index].hand_index = 0;
            DeckB->cards[card_index].hand_index = 6;

            card_draw(&DeckA->cards[card_index]);
            card_draw(&DeckB->cards[card_index]);

            screen_display_stats_player_hand(card_index, 0x0400);
            //Display the Stats
        screen_display_stats_funds(0, 0x0400);
        screen_display_stats_bet(50, 0x0400);
        screen_display_stats_dealer_hand(9, 0x7800);

        cyhal_system_delay_ms(250);
        }
    }
}

#endif
