/**
 * @file timer_050_ms.c
 * @author Pakorn Jantacumma
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
 #include "timer_050_ms.h"

volatile joystick_position_t Joystick_Pos;

 #if defined(HW02) || defined (HW03) 
/* 50mS Timer Handles*/
cyhal_timer_t       Timer_MS_050_Obj; 
cyhal_timer_cfg_t   Timer_MS_050_Cfg;

 void handler_timer_050_ms(void *callback_arg, cyhal_timer_event_t event)
 {
    /* Static Vars */
    static button_state_t sw1_curr = BUTTON_RELEASED;
    static button_state_t sw1_prev = BUTTON_RELEASED;
    static button_state_t sw2_curr = BUTTON_RELEASED;
    static button_state_t sw2_prev = BUTTON_RELEASED;
    static button_state_t sw3_curr = BUTTON_RELEASED;
    static button_state_t sw3_prev = BUTTON_RELEASED;

    uint32_t reg_val = PORT_BUTTONS->IN;

    // check press for all switch
    if((reg_val & SW1_MASK) == 0x00){
        sw1_curr = BUTTON_PRESSED;
    }
    else
        sw1_curr = BUTTON_RELEASED;

    if((reg_val & SW2_MASK) == 0x00){
        sw2_curr = BUTTON_PRESSED;
    }
    else
        sw2_curr = BUTTON_RELEASED;

    if((reg_val & SW3_MASK) == 0x00){
        sw3_curr = BUTTON_PRESSED;
    }
        sw3_curr = BUTTON_RELEASED;

    /// Event happen if any of the switch is falling edge
    if(sw1_curr == BUTTON_RELEASED && sw1_prev == BUTTON_PRESSED)
        ECE353_Events.sw1 = 1;
    else
        ECE353_Events.sw1 = 0;

    if(sw2_curr == BUTTON_RELEASED && sw2_prev == BUTTON_PRESSED)
        ECE353_Events.sw2 = 1;
    else
        ECE353_Events.sw2 = 0;
    
    if(sw3_curr == BUTTON_RELEASED && sw3_prev == BUTTON_PRESSED)
        ECE353_Events.sw3 = 1;
    else
        ECE353_Events.sw3 = 0;

    /// update prev switch status
    sw1_prev = sw1_curr;
    sw2_prev = sw2_curr;
    sw3_prev = sw3_curr;

    /// next is the joystick events ///
    
    // staring position of joy stick
    joystick_position_t center_position = JOYSTICK_POS_CENTER;
    static joystick_position_t prev_position = JOYSTICK_POS_CENTER;
    Joystick_Pos = joystick_get_pos();

    // event happen when JoyStick is move out of center, and the previous location is not the same location
    if(Joystick_Pos != center_position && Joystick_Pos != prev_position)
        ECE353_Events.joystick = 1;
    else
        ECE353_Events.joystick = 0;
    
    // update previous position
    prev_position = Joystick_Pos;




 }

/* Configure a general purpose timer to generate an interrupt every 50mS*/
 void timer_050_ms_start(void)
 {

    // generate interupt every 50 ms
    timer_init(&Timer_MS_050_Obj, &Timer_MS_050_Cfg, 5000000, handler_timer_050_ms);
    cyhal_timer_start(&Timer_MS_050_Obj);
 }

#endif
