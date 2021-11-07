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
#include "Seven_Segment_Display/ssd.h"
#include "spidrv.h"
#include <SPI_periferia/spi_periferia.h>
#include "em_gpio.h"
#include "sl_sleeptimer.h"
#include "hal/plugin/sim-eeprom/sim-eeprom.h"

#define THERMOSTAT_ENDPOINT 1
#define SWITCH_ENDPOINT 2
#define TEMP_HYSTERESIS 50 //temp*10
#define MAIN_CYCLE_TIMEOUT_MS 2000
#define DAY_SETPOINTS_CNT 6
#define WEEK_SETPOINTS_CNT 7
#define DEFAULT_SETPOINT 2500
#define UNDEFENED_SETPOINT 0x1FFF

typedef enum
{
  THERMOSTAT_OFF = (uint8_t)0x00,
  THERMOSTAT_ON = (uint8_t)0x01,
  THERMOSTAT_TYPE_WATER = (uint8_t)0b00010000,
  THERMOSTAT_TYPE_ELECTRIC = (uint8_t)0x00,
} Thermostat_mode_t;

typedef enum
{
  THERMOSTAT_BASIC_MODE = (uint8_t)0x00,
  THERMOSTAT_PROGRAM_MODE = (uint8_t)0x01
} Thermostat_program_mode_t;

typedef enum
{
  CYCLE_LOAD_DATA,
  CYCLE_READ_TEMP_SENSORS,
  CYCLE_SET_CURRENT_TEMPERATURE,
  CYCLE_DATA_PROCESSING,
  CYCLE_IDLE,
  CYCLE_END
} Cycle_state_t;

typedef enum
{
  PRECOMMAND_SET_CLOCK = 100,
  PRECOMMAND_SET_PROGRAM_MODE,
  PRECOMMAND_SET_SYSTEM_TYPE,
  PRECOMMAND_SET_SETPOINT
} PreCommand_handle_state_t;

typedef struct
{
  uint16_t setpoints_time[DAY_SETPOINTS_CNT];
  int16_t setpoints_value[DAY_SETPOINTS_CNT];
} day_setpoints_t;

EmberStatus emberAfPluginFindAndBindInitiatorStart(uint8_t endpoint);
void gpio_init(void);
void Main_Cycle_Timer_EventHandler(void);
void My_emAfServiceDiscoveryCallback(const EmberAfServiceDiscoveryResult* result);
int16_t Get_current_setpoint(sl_sleeptimer_weekDay_t Day_of_week, uint32_t time_in_minutes);
void Clear_week_setpoints(day_setpoints_t *week_setpoints);
void Clear_day_setpoints(day_setpoints_t *day_setpoints);
EmberStatus External_Valve_ON_cmd(void);
EmberStatus External_Valve_OFF_cmd(void);
EmberAfStatus Thermostat_read_Setpoint_attr(int16_t *data);
EmberAfStatus Thermostat_write_Setpoint_attr(int16_t data);
EmberAfStatus Thermostat_read_SystemMode_attr(uint8_t *data);
EmberAfStatus Thermostat_write_SystemMode_attr(uint8_t data);
EmberAfStatus Thermostat_read_ProgramMode_attr(uint8_t *data);
EmberAfStatus Thermostat_write_ProgramMode_attr(uint8_t data);
EmberAfStatus Thermostat_read_SystemType_attr(uint8_t *data);
EmberAfStatus Thermostat_write_SystemType_attr(uint8_t data);

#endif /* USER_TYPEDEFS_H_ */
