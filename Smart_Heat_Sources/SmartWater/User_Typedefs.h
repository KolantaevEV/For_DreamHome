/*
 * User_Typedefs.h
 *
 *  Created on: 28 окт. 2021 г.
 *      Author: Kolan
 */

#ifndef USER_TYPEDEFS_H_
#define USER_TYPEDEFS_H_

#include <stdbool.h>
#include <stdint.h>
#include "em_gpio.h"
#include "find-and-bind-target.h"

#define MAIN_CYCLE_TIMEOUT                (2000)
#define THERMOSTATIC_VALVE_1              (1)
#define THERMOSTATIC_VALVE_2              (2)
#define OUTDOOR_TEMP                      (3)
#define LED_3_port                        (gpioPortC)
#define LED_3_pin                         (0)
#define LED_1_port                        (gpioPortA)
#define LED_1_pin                         (5)
#define LED_2_port                        (gpioPortA)
#define LED_2_pin                         (6)
#define Relay_Valve_1_port                (gpioPortB)
#define Relay_Valve_1_pin                 (1)
#define Relay_Valve_2_port                (gpioPortB)
#define Relay_Valve_2_pin                 (0)
#define Relay_Mixer_Valve_Direction_port  (gpioPortD)
#define Relay_Mixer_Valve_Direction_pin   (1)
#define Relay_Mixer_Valve_Switch_port     (gpioPortD)
#define Relay_Mixer_Valve_Switch_pin      (0)
#define Relay_Pump_port                   (gpioPortC)
#define Relay_Pump_pin                    (2)

typedef enum
{
  CYCLE_RESET_BINDINGS,
  CYCLE_READ_TEMP_SENSORS,
  CYCLE_DATA_PROCESSING,
  CYCLE_IDLE,
  CYCLE_END
} Cycle_state_t;

/*
EmberEventControl LED_1_Timer_EventControl;
EmberEventControl LED_2_Timer_EventControl;
EmberEventControl LED_3_Timer_EventControl;
EmberEventControl Main_Cycle_Timer_EventControl;
*/

void gpio_init(void);
void LED_1_Timer_EventHandler(void);
void LED_2_Timer_EventHandler(void);
void LED_3_Timer_EventHandler(void);
void emberAfPluginButtonInterfaceButton2PressedEventHandler(void);
void emberAfPluginButtonInterfaceButton2ReleasedEventHandler(void);

#endif /* USER_TYPEDEFS_H_ */
