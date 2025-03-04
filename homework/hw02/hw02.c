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
char STUDENTS[] = "Ajinkya Dhamdhere, Pakorn Jantacumma";

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
    
    uint32_t reg_val;
    // Allocate the necessary space for both DeckA and DeckB
    deck_t DeckA;
    deck_t DeckB;

    // Initialize the two decks by calling our deck_init function
    deck_init(&DeckA);
    deck_init(&DeckB);

    // Control Deck is at position 0 and Random at 6
    DeckA.cards[0].hand_index = 0;
    DeckB.cards[0].hand_index = 6;
    DeckA.card_index = 0;
    DeckB.card_index = 6;

    // Draw the first card of each deck
    card_draw(&DeckA.cards[0]);
    card_draw(&DeckB.cards[0]);


    int card_ind = 0;
    while (1)
    {
        // button value
        reg_val = REG_PUSH_BUTTON_IN;

        // If Button 1 is pressed
        if (ECE353_Events.sw1 == 1)
        {
            //Set the index back to 0
            card_ind = 0;
            //Call our randomizer function
            deck_randomize(&DeckB);
            //Set the respective hand indexes of DeckA and DeckB
            DeckA.cards[card_ind].hand_index = 0;
            DeckB.cards[card_ind].hand_index = 6;

            //Draw the cards
            card_draw(&DeckA.cards[card_ind]);
            card_draw(&DeckB.cards[card_ind]);

            //Clear the "score"
            screen_display_stats_player_hand(88, LCD_COLOR_BLACK);
            
        }



        //If we move up, then increment the card index and check if we are within the bounds
        if (ECE353_Events.joystick == 1 && Joystick_Pos == JOYSTICK_POS_UP){
            card_ind++;
            if (card_ind > 51){
                card_ind = 0;
             
            }
            
        }
        //If down then decrement the card index and check if it is below th allowed bounds
        else if (ECE353_Events.joystick == 1 && Joystick_Pos == JOYSTICK_POS_DOWN){
            card_ind--;
            if (card_ind < 0){
                card_ind = 51;
                
            }
            
        }

        
        //If either we have moved up OR down we want to draw the cards and keep the hand index's correct
        if (ECE353_Events.joystick == 1 && (Joystick_Pos == JOYSTICK_POS_UP || Joystick_Pos == JOYSTICK_POS_DOWN)){
            DeckA.cards[card_ind].hand_index = 0;
            DeckB.cards[card_ind].hand_index = 6;

            //Clear the score
            screen_display_stats_player_hand(88, LCD_COLOR_BLACK);

            card_draw(&DeckA.cards[card_ind]);
            card_draw(&DeckB.cards[card_ind]);
        
            ECE353_Events.joystick = 0;
        }
        

        //Display the score
        screen_display_stats_player_hand(card_ind, LCD_COLOR_WHITE);
    }
}

#endif


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
char STUDENTS[] = "Ajinkya Dhamdhere, Pakorn Jantacumma";

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
    
    uint32_t reg_val;
    // Allocate the necessary space for both DeckA and DeckB
    deck_t DeckA;
    deck_t DeckB;

    // Initialize the two decks by calling our deck_init function
    deck_init(&DeckA);
    deck_init(&DeckB);

    // Control Deck is at position 0 and Random at 6
    DeckA.cards[0].hand_index = 0;
    DeckB.cards[0].hand_index = 6;
    DeckA.card_index = 0;
    DeckB.card_index = 6;

    // Draw the first card of each deck
    card_draw(&DeckA.cards[0]);
    card_draw(&DeckB.cards[0]);


    int card_ind = 0;
    while (1)
    {
        // button value
        reg_val = REG_PUSH_BUTTON_IN;

        // If Button 1 is pressed
        if (ECE353_Events.sw1 == 1)
        {
            //Set the index back to 0
            card_ind = 0;
            //Call our randomizer function
            deck_randomize(&DeckB);
            //Set the respective hand indexes of DeckA and DeckB
            DeckA.cards[card_ind].hand_index = 0;
            DeckB.cards[card_ind].hand_index = 6;

            //Draw the cards
            card_draw(&DeckA.cards[card_ind]);
            card_draw(&DeckB.cards[card_ind]);

            //Clear the "score"
            screen_display_stats_player_hand(88, LCD_COLOR_BLACK);
            
        }



        //If we move up, then increment the card index and check if we are within the bounds
        if (ECE353_Events.joystick == 1 && Joystick_Pos == JOYSTICK_POS_UP){
            card_ind++;
            if (card_ind > 51){
                card_ind = 0;
             
            }
            
        }
        //If down then decrement the card index and check if it is below th allowed bounds
        else if (ECE353_Events.joystick == 1 && Joystick_Pos == JOYSTICK_POS_DOWN){
            card_ind--;
            if (card_ind < 0){
                card_ind = 51;
                
            }
            
        }

        
        //If either we have moved up OR down we want to draw the cards and keep the hand index's correct
        if (ECE353_Events.joystick == 1 && (Joystick_Pos == JOYSTICK_POS_UP || Joystick_Pos == JOYSTICK_POS_DOWN)){
            DeckA.cards[card_ind].hand_index = 0;
            DeckB.cards[card_ind].hand_index = 6;

            //Clear the score
            screen_display_stats_player_hand(88, LCD_COLOR_BLACK);

            card_draw(&DeckA.cards[card_ind]);
            card_draw(&DeckB.cards[card_ind]);
        
            ECE353_Events.joystick = 0;
        }
        

        //Display the score
        screen_display_stats_player_hand(card_ind, LCD_COLOR_WHITE);
    }
}

#endif