/**
 * @file ice01.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(EX01)

char APP_DESCRIPTION[] = "ECE353: Ex01 - Intro to C";

/*****************************************************************************/
/* Peripheral Initialization                                                  */
/*****************************************************************************/

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    console_init();
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
    int32_t arr1[20];
    int32_t arr2[20];
    int8_t count = 0;

    for(int8_t i=0; i < 20; i++){
        arr1[i] = rand();
        arr2[i] = rand();
    }

    for(int8_t i=0; i < 20; i++){
        if(arr1[i] > arr2[i])
            count++;
    }

    printf("count: %d\n\r", count);

        /* Send the Clear Screen Escape Sequence*/
        /*
    printf("\x1b[2J\x1b[;H");

    printf("**************************************************\n\r");
    printf("* %s\n\r",APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    /* Enter Infinite Loop*/
    while (1)
    {
    }
}
#endif
