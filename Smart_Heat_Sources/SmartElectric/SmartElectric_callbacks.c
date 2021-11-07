#include "app/framework/include/af.h"
#include "hal/hal.h"
#include EMBER_AF_API_NETWORK_STEERING
#include "app/framework/include/af.h"
#include "app/util/ezsp/ezsp-enum.h"

#include "User_Typedefs.h"

day_setpoints_t week_setpoints[WEEK_SETPOINTS_CNT];
EmberEventControl Main_Cycle_Timer_EventControl;
uint8_t flag = 0;

boolean emberAfMainStartCallback(int* returnCode,
                                 int argc,
                                 char** argv)
{
  gpio_init();
  i2c_init();
  SPI_init();
  Clear_week_setpoints(week_setpoints);

  emberEventControlSetDelayMS(Main_Cycle_Timer_EventControl, MAIN_CYCLE_TIMEOUT_MS);

  return false;  // exit?
}

void emberAfMainInitCallback(void)
{
}

boolean emberAfBasicClusterResetToFactoryDefaultsCallback(void)
{
  emberAfCorePrintln("EVENT_FactoryReset");
  return FALSE;
}

boolean emberAfThermostatClusterSetpointRaiseLowerCallback(int8u mode,
                                                           int8s amount)
{
  int16_t current_setpoint = UNDEFENED_SETPOINT;

  emberAfCorePrintln("EVENT_Rize_Lower");

  Thermostat_read_Setpoint_attr(&current_setpoint);
  Thermostat_write_Setpoint_attr(current_setpoint + amount*10);
  return FALSE;
}

boolean emberAfThermostatClusterSetWeeklyScheduleCallback(int8u numberOfTransitionsForSequence,
                                                          int8u dayOfWeekForSequence,
                                                          int8u modeForSequence,
                                                          int8u* payload)
{
  emberAfCorePrintln("EVENT_SetWeek_day: , %d", dayOfWeekForSequence);
  //for (uint8_t i = 0; i < numberOfTransitionsForSequence*2; i++)
    //emberAfCorePrintln("%d", (payload[i*2 + 1] << 8 | payload[i*2]));

  Clear_day_setpoints(&week_setpoints[dayOfWeekForSequence]);
  for (uint8_t i = 0; i < numberOfTransitionsForSequence; i++)
  {
    week_setpoints[dayOfWeekForSequence].setpoints_time[i] = payload[i*4 + 1] << 8 | payload[i*4];
    week_setpoints[dayOfWeekForSequence].setpoints_value[i] = payload[i*4 + 3] << 8 | payload[i*4 + 2];
  }

  for (uint8_t i = 0; i < DAY_SETPOINTS_CNT; i++)
    emberAfCorePrintln("%d : %d", week_setpoints[dayOfWeekForSequence].setpoints_time[i], week_setpoints[dayOfWeekForSequence].setpoints_value[i]);

  switch (dayOfWeekForSequence)
  {
    case DAY_SUNDAY:
      halCommonSetToken(TOKEN_WEEK_DATA_SUN, &week_setpoints[DAY_SUNDAY]);
      break;

    case DAY_MONDAY:
      halCommonSetToken(TOKEN_WEEK_DATA_MON, &week_setpoints[DAY_MONDAY]);
      break;

    case DAY_TUESDAY:
      halCommonSetToken(TOKEN_WEEK_DATA_TUE, &week_setpoints[DAY_TUESDAY]);
      break;

    case DAY_WEDNESDAY:
      halCommonSetToken(TOKEN_WEEK_DATA_WED, &week_setpoints[DAY_WEDNESDAY]);
      break;

    case DAY_THURSDAY:
      halCommonSetToken(TOKEN_WEEK_DATA_THU, &week_setpoints[DAY_THURSDAY]);
      break;

    case DAY_FRIDAY:
      halCommonSetToken(TOKEN_WEEK_DATA_FRI, &week_setpoints[DAY_FRIDAY]);
      break;

    case DAY_SATURDAY:
      halCommonSetToken(TOKEN_WEEK_DATA_SAT, &week_setpoints[DAY_SATURDAY]);
      break;
  }

  return FALSE;
}

boolean emberAfThermostatClusterGetWeeklyScheduleCallback(int8u daysToReturn,
                                                          int8u modeToReturn)
{
  emberAfCorePrintln("EVENT_GetWeek");
  //TODO: return week_data
  return FALSE;
}

boolean emberAfThermostatClusterClearWeeklyScheduleCallback(void)
{
  emberAfCorePrintln("EVENT_ClearWeek");
  Clear_week_setpoints(week_setpoints);
  halCommonSetToken(TOKEN_WEEK_DATA_SUN, &week_setpoints[DAY_SUNDAY]);
  halCommonSetToken(TOKEN_WEEK_DATA_MON, &week_setpoints[DAY_MONDAY]);
  halCommonSetToken(TOKEN_WEEK_DATA_TUE, &week_setpoints[DAY_TUESDAY]);
  halCommonSetToken(TOKEN_WEEK_DATA_WED, &week_setpoints[DAY_WEDNESDAY]);
  halCommonSetToken(TOKEN_WEEK_DATA_THU, &week_setpoints[DAY_THURSDAY]);
  halCommonSetToken(TOKEN_WEEK_DATA_FRI, &week_setpoints[DAY_FRIDAY]);
  halCommonSetToken(TOKEN_WEEK_DATA_SAT, &week_setpoints[DAY_SATURDAY]);
  return FALSE;
}

boolean emberAfThermostatClusterGetRelayStatusLogCallback(void)
{
  emberAfCorePrintln("EVENT_GetRelay");
  //TODO: return relay status
  return FALSE;
}

uint32_t emberAfGetCurrentTimeCallback(void)
{
  //emberAfCorePrintln("EVENT_time1!!!!!");
  return 0;
}

boolean emberAfMessageSentCallback(EmberOutgoingMessageType type,
                                   int16u indexOrDestination,
                                   EmberApsFrame* apsFrame,
                                   int16u msgLen,
                                   int8u* message,
                                   EmberStatus status)
{
  //emberAfCorePrintln("EVENT_Msg_send!!!!!");
  return false;
}

boolean emberAfPreCommandReceivedCallback(EmberAfClusterCommand* cmd)
{
  sl_sleeptimer_date_t current_time = {0};
  sl_status_t status = 0;
  emberAfCorePrintln("EVENT_PreCMD_rcv");

  //TODO: Заменить на стандартные сообщения или добавить ON/OFF кластер
  if (cmd->apsFrame->clusterId == 513 && cmd->commandId == 1 && (cmd->buffer[3] == 2 || cmd->buffer[3] == 4) && cmd->buffer[4] == 0 && cmd->buffer[5] == 2)
  {
    switch (cmd->buffer[6])
    {
      case PRECOMMAND_SET_CLOCK:
        status = sl_sleeptimer_build_datetime(&current_time,
                                     (uint16_t)((cmd->buffer[9] << 8) | cmd->buffer[8]),
                                     (sl_sleeptimer_month_t)cmd->buffer[10],
                                     cmd->buffer[12],
                                     cmd->buffer[14],
                                     cmd->buffer[16],
                                     cmd->buffer[18],
                                     (sl_sleeptimer_time_zone_offset_t)(cmd->buffer[20]*60*60));
        if (status) emberAfCorePrintln("Time_set_error1 %x", status);
        status = sl_sleeptimer_set_datetime(&current_time);
        if (status) emberAfCorePrintln("Time_set_error2 %x", status);
        return true;
        break;

      case PRECOMMAND_SET_PROGRAM_MODE:
        if (cmd->buffer[8] == 0)
          Thermostat_write_ProgramMode_attr(THERMOSTAT_BASIC_MODE);
        else if (cmd->buffer[8] == 1)
          Thermostat_write_ProgramMode_attr(THERMOSTAT_PROGRAM_MODE);
        return true;
        break;

      case PRECOMMAND_SET_SYSTEM_TYPE:
        GPIO_PinOutClear(gpioPortA, 7);
        External_Valve_OFF_cmd();
        if (cmd->buffer[8] == 0)
          Thermostat_write_SystemType_attr(THERMOSTAT_TYPE_ELECTRIC);
        else if (cmd->buffer[8] == 1)
          Thermostat_write_SystemType_attr(THERMOSTAT_TYPE_WATER);
        return true;
        break;

      case PRECOMMAND_SET_SETPOINT:
        Thermostat_write_Setpoint_attr((int16_t)((cmd->buffer[9] << 8) | cmd->buffer[8]));
        return true;
        break;

      default:
        return true;
        break;
    }
  }

  return false;
}

boolean emberAfPreMessageReceivedCallback(EmberAfIncomingMessage* incomingMessage)
{
  //emberAfCorePrintln("EVENT_PreMsg_rcv!!!!!");
  return false;
}

boolean emberAfPreMessageSendCallback(EmberAfMessageStruct* messageStruct,
                                      EmberStatus* status)
{
  //emberAfCorePrintln("EVENT_PreMsg_send!!!!!");
  return false;
}

void emberAfSetTimeCallback(uint32_t utcTime)
{
  //emberAfCorePrintln("EVENT_time0!!!!!");
}

void emberAfPluginButtonInterfaceButton0PressedLongCallback(uint16_t timePressedMs,
                                                            bool pressedAtReset)
{
  emberAfCorePrintln("Butt_long0");


}

void emberAfPluginButtonInterfaceButton0PressedShortCallback(uint16_t timePressedMs)
{
  emberAfCorePrintln("Butt_short0!!!!!");

  if (emberAfNetworkState() == EMBER_JOINED_NETWORK)
  {
    EmberStatus status = emberAfPluginFindAndBindInitiatorStart(SWITCH_ENDPOINT);
    emberAfCorePrintln("Find and bind initiator %p: 0x%X", "start", status);
  }
  else emberAfPluginNetworkSteeringStart();
}

void emberAfPluginButtonInterfaceButton1PressedLongCallback(uint16_t timePressedMs,
                                                            bool pressedAtReset)
{
  emberAfCorePrintln("Butt_long1!!!!!");

}

void emberAfPluginButtonInterfaceButton1PressedShortCallback(uint16_t timePressedMs)
{
  emberAfCorePrintln("Butt_short1!!!!!");
  flag = !flag;
}

void emberAfPluginIdentifyStartFeedbackCallback(uint8_t endpoint,
                                                uint16_t identifyTime)
{
  //TODO: add blinking when identifyig?
  emberAfCorePrintln("EVENT_ident_start!!!!!");
}

void emberAfPluginIdentifyStopFeedbackCallback(uint8_t endpoint)
{
  emberAfCorePrintln("EVENT_ident_stop!!!!!");
}

boolean emberAfOnOffClusterOffCallback(void)
{
  emberAfCorePrintln("EVENT_OFF!!!!!");
  Thermostat_write_SystemMode_attr(THERMOSTAT_OFF);
  return FALSE;
}

boolean emberAfOnOffClusterOnCallback(void)
{
  emberAfCorePrintln("EVENT_ON!!!!!");
  Thermostat_write_SystemMode_attr(THERMOSTAT_ON);
  return FALSE;
}

boolean emberAfAlarmClusterResetAlarmCallback(int8u alarmCode,
                                              int16u clusterId)
{
  emberAfCorePrintln("EVENT_Reset_ALARM!!!!!");
  return FALSE;
}

boolean emberAfAlarmClusterGetAlarmCallback(void)
{
  emberAfCorePrintln("EVENT_Get_ALARM!!!!!");
  return FALSE;
}

//>>>>>>>>>>>>>USER_CODE<<<<<<<<<<<<<<<<<<

void Main_Cycle_Timer_EventHandler(void)
{
  uint16_t data[3] = {0};
  static sl_sleeptimer_date_t date_time = {0};
  static int16_t setpoint = DEFAULT_SETPOINT;
  static uint8_t Thermostat_type = THERMOSTAT_TYPE_ELECTRIC;
  static uint8_t Thermostat_On_Off = THERMOSTAT_OFF;
  static uint8_t on_off_flag = 0;
  static uint8_t week_flag = 0;
  sl_status_t status = 0;
  int16_t new_setpoint = UNDEFENED_SETPOINT;

  Cycle_state_t Cycle_state;
  Cycle_state = (week_flag != 2) ? CYCLE_LOAD_DATA : CYCLE_READ_TEMP_SENSORS;

  while (Cycle_state != CYCLE_END)
  {
    switch (Cycle_state)
    {
      case CYCLE_LOAD_DATA:
        GPIO_PinOutClear(gpioPortA, 7);
        External_Valve_OFF_cmd();

        halCommonGetToken(&week_flag, TOKEN_WEEK_FLAG);
        if (week_flag)
        {
          halCommonGetToken(&week_setpoints[DAY_SUNDAY], TOKEN_WEEK_DATA_SUN);
          halCommonGetToken(&week_setpoints[DAY_MONDAY], TOKEN_WEEK_DATA_MON);
          halCommonGetToken(&week_setpoints[DAY_TUESDAY], TOKEN_WEEK_DATA_TUE);
          halCommonGetToken(&week_setpoints[DAY_WEDNESDAY], TOKEN_WEEK_DATA_WED);
          halCommonGetToken(&week_setpoints[DAY_THURSDAY], TOKEN_WEEK_DATA_THU);
          halCommonGetToken(&week_setpoints[DAY_FRIDAY], TOKEN_WEEK_DATA_FRI);
          halCommonGetToken(&week_setpoints[DAY_SATURDAY], TOKEN_WEEK_DATA_SAT);
          Thermostat_read_Setpoint_attr(&setpoint);
          week_flag = 2;
        }
        else
        {
          halCommonSetToken(TOKEN_WEEK_DATA_SUN, &week_setpoints[DAY_SUNDAY]);
          halCommonSetToken(TOKEN_WEEK_DATA_MON, &week_setpoints[DAY_MONDAY]);
          halCommonSetToken(TOKEN_WEEK_DATA_TUE, &week_setpoints[DAY_TUESDAY]);
          halCommonSetToken(TOKEN_WEEK_DATA_WED, &week_setpoints[DAY_WEDNESDAY]);
          halCommonSetToken(TOKEN_WEEK_DATA_THU, &week_setpoints[DAY_THURSDAY]);
          halCommonSetToken(TOKEN_WEEK_DATA_FRI, &week_setpoints[DAY_FRIDAY]);
          halCommonSetToken(TOKEN_WEEK_DATA_SAT, &week_setpoints[DAY_SATURDAY]);
          week_flag = 1;
          halCommonSetToken(TOKEN_WEEK_FLAG, &week_flag);
        }
        Cycle_state = CYCLE_IDLE;
        break;

      case CYCLE_READ_TEMP_SENSORS:
        if (mcp3202_read(data)) emberAfCorePrintln("Sensor_get_error"); //TODO: error handler
        Cycle_state++;
        break;

      case CYCLE_SET_CURRENT_TEMPERATURE:
        status = sl_sleeptimer_get_datetime(&date_time);
        if (status) emberAfCorePrintln("Time_get_error");

        if (flag)
        {
          if (!status) lcd_print_to_display((date_time.hour*100+date_time.min), LCD_DEC, 0, 3, true);
        }
        else lcd_print_to_display(data[0], LCD_DEC, 0, 7, false);

        Thermostat_read_SystemMode_attr(&Thermostat_On_Off);
        if (Thermostat_On_Off == THERMOSTAT_OFF)
        {
          if (!on_off_flag)
          {
            GPIO_PinOutClear(gpioPortA, 7);
            External_Valve_OFF_cmd();
            on_off_flag = 1;
          }
          Cycle_state = CYCLE_IDLE;
        }
        else
        {
          on_off_flag = 0;
          Cycle_state++;
        }
        break;

      case CYCLE_DATA_PROCESSING:
        new_setpoint = Get_current_setpoint(date_time.day_of_week, (date_time.hour*60 + date_time.min));
        if (new_setpoint != UNDEFENED_SETPOINT) setpoint = new_setpoint;
        emberAfCorePrintln("> Setpoint_set: %d <", setpoint);

        Thermostat_read_SystemType_attr(&Thermostat_type);

        if ((data[0] * 10) >= (setpoint + TEMP_HYSTERESIS))
        {
          if (Thermostat_type == THERMOSTAT_TYPE_ELECTRIC)
            GPIO_PinOutClear(gpioPortA, 7);
          else if (Thermostat_type == THERMOSTAT_TYPE_WATER)
            External_Valve_OFF_cmd();
        }
        else if ((data[0] * 10) < (setpoint - TEMP_HYSTERESIS))
        {
          if (Thermostat_type == THERMOSTAT_TYPE_ELECTRIC)
            GPIO_PinOutSet(gpioPortA, 7);
          else if (Thermostat_type == THERMOSTAT_TYPE_WATER)
            External_Valve_ON_cmd();
        }
        Cycle_state++;
        break;

      case CYCLE_IDLE:
        emberEventControlSetDelayMS(Main_Cycle_Timer_EventControl, MAIN_CYCLE_TIMEOUT_MS);
        Cycle_state = CYCLE_END;
        break;

      default:
        Cycle_state = CYCLE_END;
        break;
    }
  }
}

void gpio_init(void)
{
  CMU_ClockEnable(cmuClock_GPIO, true);
  GPIO_PinModeSet(gpioPortA,
                  7,
                  gpioModePushPull,
                  0);
}

void My_emAfServiceDiscoveryCallback(const EmberAfServiceDiscoveryResult* result)
{
  EmberAfServiceDiscoveryResult* result_new;
  result_new = (EmberAfServiceDiscoveryResult*)result;
  emberAfCorePrintln("RESULT RECEIVE: %d", result_new->status);
}

int16_t Get_current_setpoint(sl_sleeptimer_weekDay_t Day_of_week, uint32_t time_in_minutes)
{
  int16_t setpoint = UNDEFENED_SETPOINT;
  uint8_t program_mode = THERMOSTAT_BASIC_MODE;
  Thermostat_read_ProgramMode_attr(&program_mode);

  if (program_mode == THERMOSTAT_PROGRAM_MODE) //работаем по программе
  {
    for (uint8_t i = 0; i < DAY_SETPOINTS_CNT; i++)
    {
      if (time_in_minutes >= week_setpoints[Day_of_week].setpoints_time[i])
      {
        setpoint = week_setpoints[Day_of_week].setpoints_value[i]; //TODO: определение ближайшего подхлодящего значения?
      }
      else
      {
        emberAfCorePrintln("> New_setpoint: %d <", setpoint);
        break;
      }
    }
  }
  else
  {
    Thermostat_read_Setpoint_attr(&setpoint);
  }

  return setpoint;
}

void Clear_week_setpoints(day_setpoints_t *week_setpoints)
{
  for (uint8_t i = 0; i < WEEK_SETPOINTS_CNT; i++)
  {
    Clear_day_setpoints(&week_setpoints[i]);
  }
  //TODO: clear from EEPROM
}

void Clear_day_setpoints(day_setpoints_t *day_setpoints)
{
    for (uint8_t j = 0; j < DAY_SETPOINTS_CNT; j++)
    {
      day_setpoints->setpoints_time[j] = UNDEFENED_SETPOINT;
      day_setpoints->setpoints_value[j] = UNDEFENED_SETPOINT;
    }
    //TODO: clear from EEPROM
}

EmberStatus External_Valve_ON_cmd(void)
{
  EmberStatus status = 0xFF;

  if (emberAfNetworkState() == EMBER_JOINED_NETWORK)
  {
    emberAfGetCommandApsFrame()->sourceEndpoint = SWITCH_ENDPOINT;
    emberAfFillCommandOnOffClusterOn();
    status = emberAfSendCommandUnicastToBindings();
    emberAfCorePrintln("%p: 0x%X", "Send to bindings", status);
  }

  return status;
}

EmberStatus External_Valve_OFF_cmd(void)
{
  EmberStatus status = 0xFF;

  if (emberAfNetworkState() == EMBER_JOINED_NETWORK)
  {
    emberAfGetCommandApsFrame()->sourceEndpoint = SWITCH_ENDPOINT;
    emberAfFillCommandOnOffClusterOff();
    status = emberAfSendCommandUnicastToBindings();
    emberAfCorePrintln("%p: 0x%X", "Send to bindings", status);
  }

  return status;
}

EmberAfStatus Thermostat_read_Setpoint_attr(int16_t *data)
{
  EmberAfStatus status;
  status = emberAfReadServerAttribute(1, ZCL_THERMOSTAT_CLUSTER_ID, ZCL_OCCUPIED_HEATING_SETPOINT_ATTRIBUTE_ID, (uint8_t *)data, 2);
  emberAfCorePrintln("> New_setpoint: %d <", *data);
  return status;
}

EmberAfStatus Thermostat_write_Setpoint_attr(int16_t data)
{
  uint16_t new_data = 0;
  EmberAfStatus status;
  status = emberAfWriteServerAttribute(1, ZCL_THERMOSTAT_CLUSTER_ID, ZCL_OCCUPIED_HEATING_SETPOINT_ATTRIBUTE_ID, (uint8_t *)(&data), 2);
  status = emberAfReadServerAttribute(1, ZCL_THERMOSTAT_CLUSTER_ID, ZCL_OCCUPIED_HEATING_SETPOINT_ATTRIBUTE_ID, (uint8_t *)(&new_data), 2);
  if (new_data == data) emberAfCorePrintln("> %d <", new_data);
  else emberAfCorePrintln("Attr write error");
  return status;
}

EmberAfStatus Thermostat_read_SystemMode_attr(uint8_t *data)
{
  EmberAfStatus status;
  status = emberAfReadServerAttribute(1, ZCL_THERMOSTAT_CLUSTER_ID, ZCL_SYSTEM_MODE_ATTRIBUTE_ID, (uint8_t *)data, 1);
  emberAfCorePrintln("> %d <", *data);
  return status;
}

EmberAfStatus Thermostat_write_SystemMode_attr(uint8_t data)
{
  uint8_t new_data = 0;
  EmberAfStatus status;
  status = emberAfWriteServerAttribute(1, ZCL_THERMOSTAT_CLUSTER_ID, ZCL_SYSTEM_MODE_ATTRIBUTE_ID, (uint8_t *)(&data), 1);
  status = emberAfReadServerAttribute(1, ZCL_THERMOSTAT_CLUSTER_ID, ZCL_SYSTEM_MODE_ATTRIBUTE_ID, (uint8_t *)(&new_data), 1);
  if (new_data == data) emberAfCorePrintln("> %d <", new_data);
  else emberAfCorePrintln("Attr write error");
  return status;
}

EmberAfStatus Thermostat_read_ProgramMode_attr(uint8_t *data)
{
  EmberAfStatus status;
  status = emberAfReadServerAttribute(1, ZCL_THERMOSTAT_CLUSTER_ID, ZCL_THERMOSTAT_PROGRAMMING_OPERATION_MODE_ATTRIBUTE_ID, (uint8_t *)data, 1);
  emberAfCorePrintln("> %d <", *data);
  return status;
}

EmberAfStatus Thermostat_write_ProgramMode_attr(uint8_t data)
{
  uint8_t new_data = 0;
  EmberAfStatus status;
  status = emberAfWriteServerAttribute(1, ZCL_THERMOSTAT_CLUSTER_ID, ZCL_THERMOSTAT_PROGRAMMING_OPERATION_MODE_ATTRIBUTE_ID, (uint8_t *)(&data), 1);
  status = emberAfReadServerAttribute(1, ZCL_THERMOSTAT_CLUSTER_ID, ZCL_THERMOSTAT_PROGRAMMING_OPERATION_MODE_ATTRIBUTE_ID, (uint8_t *)(&new_data), 1);
  if (new_data == data) emberAfCorePrintln("> %d <", new_data);
  else emberAfCorePrintln("Attr write error");
  return status;
}

EmberAfStatus Thermostat_read_SystemType_attr(uint8_t *data)
{
  EmberAfStatus status;
  status = emberAfReadServerAttribute(1, ZCL_THERMOSTAT_CLUSTER_ID, ZCL_HVAC_SYSTEM_TYPE_CONFIGURATION_ATTRIBUTE_ID, (uint8_t *)data, 1);
  emberAfCorePrintln("> %d <", *data);
  return status;
}

EmberAfStatus Thermostat_write_SystemType_attr(uint8_t data)
{
  uint8_t new_data = 0;
  EmberAfStatus status;
  status = emberAfWriteServerAttribute(1, ZCL_THERMOSTAT_CLUSTER_ID, ZCL_HVAC_SYSTEM_TYPE_CONFIGURATION_ATTRIBUTE_ID, (uint8_t *)(&data), 1);
  status = emberAfReadServerAttribute(1, ZCL_THERMOSTAT_CLUSTER_ID, ZCL_HVAC_SYSTEM_TYPE_CONFIGURATION_ATTRIBUTE_ID, (uint8_t *)(&new_data), 1);
  if (new_data == data) emberAfCorePrintln("> %d <", new_data);
  else emberAfCorePrintln("Attr write error");
  return status;
}

/*Read any attribute
uint8_t endpoint = 1;
EmberAfClusterId cluster = ZCL_THERMOSTAT_CLUSTER_ID;
EmberAfAttributeId attributeID = ZCL_OCCUPIED_HEATING_SETPOINT_ATTRIBUTE_ID;
uint8_t readLength = 2;
emberAfReadServerAttribute(endpoint, cluster, attributeID, (uint8_t *)(&setpoint), readLength);
emberAfCorePrintln("> %d <", setpoint);
*/
