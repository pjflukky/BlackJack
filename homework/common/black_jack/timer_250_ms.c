/**
 * @file pyl_handler_tmr_050_ms.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "timer_250_ms.h"
#include "ece353_events.h"

 #if defined (HW03) 

 /* 250mS Timer Handles*/
cyhal_timer_t       Timer_MS_250_Obj; 
cyhal_timer_cfg_t   Timer_MS_250_Cfg;

 /**
  * @brief 
  * Handler for the 250mS Timer Interrupt
  */
 void handler_timer_250_ms(void *callback_arg, cyhal_timer_event_t event)
 {
    uint16_t ch0 = ltr_light_sensor_get_ch0(); // get read value from channel 0
  if (ch0 < 100) {
    ECE353_Events.lux_less_100 = 1;
    ECE353_Events.lux_more_500 = 0;
    ECE353_Events.lux_between  = 0;
}
else if (ch0 > 500) {
    ECE353_Events.lux_less_100 = 0;
    ECE353_Events.lux_more_500 = 1;
    ECE353_Events.lux_between  = 0;
}
else {
    ECE353_Events.lux_less_100 = 0;
    ECE353_Events.lux_more_500 = 0;
    ECE353_Events.lux_between  = 1;
}

}

 /**
  * @brief 
  * Add the code required to initialize a 250mS TCPWM based timer interrupt
  */
void timer_250_ms_start(void)
{
  // generate interupt every 250 ms
  timer_init(&Timer_MS_250_Obj, &Timer_MS_250_Cfg, 25000000, handler_timer_250_ms);
  cyhal_timer_start(&Timer_MS_250_Obj);
}

#endif
