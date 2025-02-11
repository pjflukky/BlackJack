/**
 * @file hw01.c
 * @author Pakorn Jantacumma & Ajinka
 * @brief 
 * @version 0.1
 * @date 2025-01-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #include "hw01.h"
#include "card.h"
#include "console.h"
#include "cyhal_system.h"
#include "image.h"
#include "io-lcd.h"
#include "screen.h"

#if defined(HW01)

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: S25 HW01";
char STUDENTS[] = "Pakorn Jantacumma , Ajinkya Dhamdhere";     /* Modify */
char TEAM[] = "Team14";                 /* Modify */

 cyhal_trng_t trng_obj;


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

    console_init();
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
    printf("* Team:%s\n\r", TEAM);
    printf("* Names:%s\n\r", STUDENTS);
    printf("**************************************************\n\r");

    u_int32_t fund = 0;
    uint32_t reg_val;

    card_t spades_two = {
        .border_color = LCD_COLOR_BLUE,
        .suit = IMAGE_TYPE_SPADE,
        .card_id = CARD_ID_2,
        .hand_index = 0
    };


    card_draw(&spades_two);

    while (1)
    {
        
        // button value
        reg_val = REG_PUSH_BUTTON_IN;

        if((reg_val &  SW1_MASK) == 0x00)
            fund += 50;

        screen_display_stats_funds(fund, 0x0400);
        screen_display_stats_bet(50, 0x0400);
        screen_display_stats_player_hand(21, 0x0400);
        screen_display_stats_dealer_hand(9, 0x7800);

        cyhal_system_delay_ms(250);
    }
}

#endif