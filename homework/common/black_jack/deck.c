/**
 * @file deck.c
 * @author Ajinkya 
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
    int index = 0;
    for (int suit = 0 ; suit <= 3 ; suit++){
        for (int number = 2 ; number <= 14 ; number++){
            deck->cards[index].suit = suit;
            deck->cards[index].card_id = number;
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
