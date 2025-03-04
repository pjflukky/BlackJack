/**
 * @file deck.c
 * @author Ajinkya Dhamdhere
 * @brief 
 * @version 0.1
 * @date 2025-01-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "deck.h"
#include "cyip_pass.h"

 extern cyhal_trng_t     trng_obj;

/**
 * @brief 
 * Initializes the deck of cards
 * @param deck
 * Pointer to the deck of cards 
 * @return true 
 * @return false 
 */
bool deck_init(deck_t *deck)
{
    if (deck == NULL) {
        printf("Error: deck is NULL in deck_init()\n");
        return false;
    }


    int index = 0;
    for (int suit = 0; suit <= 3; suit++) {
        for (int number = 2; number <= 14; number++) {
            deck->cards[index].suit = (image_type_t)suit;
            deck->cards[index].border_color = LCD_COLOR_BLUE;
            deck->cards[index].hidden = true;


            // Correct mapping of card_id
            switch (number) {
                case 10:
                    deck->cards[index].card_id = CARD_ID_10;
                    break;
                case 11:
                    deck->cards[index].card_id = CARD_ID_J;
                    break;
                case 12:
                    deck->cards[index].card_id = CARD_ID_Q;
                    break;
                case 13:
                    deck->cards[index].card_id = CARD_ID_K;
                    break;
                case 14:
                    deck->cards[index].card_id = CARD_ID_A;
                    break;
                default:
                    deck->cards[index].card_id = (card_id_t)('0' + number); // Convert to ASCII
                    break;
            }


            // Debugging output
            printf("Deck[%d]: Suit=%d, Rank=%c, Hidden=%d\n", 
                   index, deck->cards[index].suit, deck->cards[index].card_id, deck->cards[index].hidden);


            index++;
        }
    }
    return true;
}

/**
 * @brief 
 * Function used to randomize the card deck
 * @param arr 
 */
void deck_randomize(deck_t *deck) 
{ 
    for (int i = 51 ; i > 0 ; i--){
        uint32_t random_val = cyhal_trng_generate(&trng_obj);

        int j = random_val % (i + 1);

        card_t temporary = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temporary;
    }
}
