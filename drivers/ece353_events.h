/**
 * @file ece353_events.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
 #ifndef  __ECE353_EVENTS_H__
 #define  __ECE353_EVENTS_H__

 typedef struct ece353_events_t
{
    unsigned int sw1 : 1;       /* Falling edge of SW1 detected */
    unsigned int sw2 : 1;       /* Falling edge of SW2 detected */
    unsigned int sw3 : 1;       /* Falling edge of SW3 detected */
    unsigned int joystick : 1;  /* Joystick has moved position */
    unsigned int ipc_rx : 1;    /* Data received from remote board */
    unsigned int lux_less_100 : 1;    /* lux less than 100 */
    unsigned int lux_more_500 : 1; /* lux more than 500*/
    unsigned int lux_between : 1; /* lux between 100, 500*/
} ece353_events_t;

extern volatile ece353_events_t ECE353_Events;
extern volatile ece353_events_t ECE353_Events_250;

 #endif