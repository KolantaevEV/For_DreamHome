// This callback file is created for your convenience. You may add application
// code to this file. If you regenerate this file over a previous version, the
// previous version will be overwritten and any code you have added will be
// lost.

#include "app/framework/include/af.h"
#include "hal/hal.h"
#include EMBER_AF_API_NETWORK_STEERING
#include "app/framework/include/af.h"
#include "app/util/ezsp/ezsp-enum.h"

#include "User_Typedefs.h"

EmberEventControl LED_1_Timer_EventControl;
EmberEventControl LED_2_Timer_EventControl;
EmberEventControl LED_3_Timer_EventControl;
EmberEventControl Main_Cycle_Timer_EventControl;
uint8_t start_binding_valve_1 = false;
uint8_t start_binding_valve_2 = false;
uint8_t start_binding_outdoor_temp = false;
uint8_t Binding_Clear_code = 0;

boolean emberAfMainStartCallback(int* returnCode,
                                 int argc,
                                 char** argv)
{
  // NOTE:  argc and argv may not be supported on all platforms, so argv MUST be
  // checked for NULL before referencing it.  On those platforms without argc 
  // and argv "0" and "NULL" are passed respectively.
  gpio_init();
  emberEventControlSetDelayMS(Main_Cycle_Timer_EventControl, MAIN_CYCLE_TIMEOUT);
  emberEventControlSetDelayMS(LED_1_Timer_EventControl, 250);
  //emberEventControlSetDelayMS(LED_2_Timer_EventControl, 250);
  //emberEventControlSetDelayMS(LED_3_Timer_EventControl, 250);
  return false;  // exit?
}

void emberAfMainInitCallback(void)
{
}

boolean emberAfBasicClusterResetToFactoryDefaultsCallback(void)
{
  return FALSE;
}

boolean emberAfPreCommandReceivedCallback(EmberAfClusterCommand* cmd)
{
  return false;
}

boolean emberAfPreMessageReceivedCallback(EmberAfIncomingMessage* incomingMessage)
{
  return false;
}

boolean emberAfPreMessageSendCallback(EmberAfMessageStruct* messageStruct,
                                      EmberStatus* status)
{
  return false;
}

void emberAfPluginButtonInterfaceButton0PressedShortCallback(uint16_t timePressedMs)
{
  if (emberAfNetworkState() == EMBER_JOINED_NETWORK)
  {
    emberAfPluginFindAndBindTargetStart(THERMOSTATIC_VALVE_1);
  }
  else emberAfPluginNetworkSteeringStart();

  if (Binding_Clear_code >= 4 && Binding_Clear_code < 10) Binding_Clear_code += 3;
  else Binding_Clear_code = 0;
}

void emberAfPluginButtonInterfaceButton0PressedLongCallback(uint16_t timePressedMs,
                                                            bool pressedAtReset)
{

}

void emberAfPluginButtonInterfaceButton1PressedLongCallback(uint16_t timePressedMs,
                                                            bool pressedAtReset)
{

}

void emberAfPluginButtonInterfaceButton1PressedShortCallback(uint16_t timePressedMs)
{
  if (emberAfNetworkState() == EMBER_JOINED_NETWORK)
  {
    emberAfPluginFindAndBindTargetStart(THERMOSTATIC_VALVE_2);
  }

  if (Binding_Clear_code < 4) Binding_Clear_code += 2;
  else Binding_Clear_code = 0;
}

void emberAfPluginButtonInterfaceButton2PressedLongCallback(uint16_t timePressedMs,
                                                            bool pressedAtReset)
{

}

void emberAfPluginButtonInterfaceButton2PressedShortCallback(uint16_t timePressedMs)
{
  static uint8_t flag = 0;
  if (emberAfNetworkState() == EMBER_JOINED_NETWORK)
  {
    emberAfPluginFindAndBindTargetStart(OUTDOOR_TEMP);
  }

  if (flag) GPIO_PinOutSet(Relay_Mixer_Valve_Switch_port, Relay_Mixer_Valve_Switch_pin);
  else GPIO_PinOutClear(Relay_Mixer_Valve_Switch_port, Relay_Mixer_Valve_Switch_pin);
  flag = !flag;

  if (Binding_Clear_code == 0) Binding_Clear_code = 3;
  else Binding_Clear_code = 0;
}

void emberAfPluginNetworkSteeringCompleteCallback(EmberStatus status,
                                                  uint8_t totalBeacons,
                                                  uint8_t joinAttempts,
                                                  uint8_t finalState)
{
  //TODO: в случае неудачи повторить
}

void emberAfPluginIdentifyStartFeedbackCallback(uint8_t endpoint,
                                                uint16_t identifyTime)
{
  if (endpoint == THERMOSTATIC_VALVE_1)
    start_binding_valve_1 = true;
  else if (endpoint == THERMOSTATIC_VALVE_2)
    start_binding_valve_2 = true;
  else if (endpoint == OUTDOOR_TEMP)
    start_binding_outdoor_temp = true;
}

void emberAfPluginIdentifyStopFeedbackCallback(uint8_t endpoint)
{
  if (endpoint == THERMOSTATIC_VALVE_1)
    start_binding_valve_1 = false;
  else if (endpoint == THERMOSTATIC_VALVE_2)
    start_binding_valve_2 = false;
  else if (endpoint == OUTDOOR_TEMP)
    start_binding_outdoor_temp = false;
}

EmberAfStatus emberAfExternalAttributeReadCallback(int8u endpoint,
                                                   EmberAfClusterId clusterId,
                                                   EmberAfAttributeMetadata *attributeMetadata,
                                                   int16u manufacturerCode,
                                                   int8u *buffer,
                                                   int16u maxReadLength)
{
  return EMBER_ZCL_STATUS_FAILURE;
}

EmberAfStatus emberAfExternalAttributeWriteCallback(int8u endpoint,
                                                    EmberAfClusterId clusterId,
                                                    EmberAfAttributeMetadata *attributeMetadata,
                                                    int16u manufacturerCode,
                                                    int8u *buffer)
{
  return EMBER_ZCL_STATUS_FAILURE;
}

boolean emberAfOnOffClusterOffCallback(void)
{
  return FALSE;
}

boolean emberAfOnOffClusterOnCallback(void)
{
  return FALSE;
}

boolean emberAfOnOffClusterToggleCallback(void)
{
  return FALSE;
}

boolean emberAfOnOffClusterOnCallback_VALVE_1(void)
{
  if (!GPIO_PinOutGet(Relay_Valve_1_port, Relay_Valve_1_pin)) GPIO_PinOutSet(Relay_Valve_1_port, Relay_Valve_1_pin);
  return TRUE;
}

boolean emberAfOnOffClusterOffCallback_VALVE_1(void)
{
  if (GPIO_PinOutGet(Relay_Valve_1_port, Relay_Valve_1_pin)) GPIO_PinOutClear(Relay_Valve_1_port, Relay_Valve_1_pin);
  return TRUE;
}

boolean emberAfOnOffClusterOnCallback_VALVE_2(void)
{
  if (!GPIO_PinOutGet(Relay_Valve_2_port, Relay_Valve_2_pin)) GPIO_PinOutSet(Relay_Valve_2_port, Relay_Valve_2_pin);
  return TRUE;
}

boolean emberAfOnOffClusterOffCallback_VALVE_2(void)
{
  if (GPIO_PinOutGet(Relay_Valve_2_port, Relay_Valve_2_pin)) GPIO_PinOutClear(Relay_Valve_2_port, Relay_Valve_2_pin);
  return TRUE;
}

//>>>>>>>>>>>>>USER_CODE<<<<<<<<<<<<<<<<<<

void Main_Cycle_Timer_EventHandler(void)
{
  Cycle_state_t Cycle_state = CYCLE_RESET_BINDINGS;

  while (Cycle_state != CYCLE_END)
  {
    switch (Cycle_state)
    {
      case CYCLE_RESET_BINDINGS:
        if (Binding_Clear_code == 10)
        {
          GPIO_PinOutClear(Relay_Pump_port, Relay_Pump_pin);
          GPIO_PinOutClear(Relay_Valve_1_port, Relay_Valve_1_pin);
          GPIO_PinOutClear(Relay_Valve_2_port, Relay_Valve_2_pin);
          GPIO_PinOutClear(Relay_Mixer_Valve_Switch_port, Relay_Mixer_Valve_Switch_pin);
          emberEventControlSetInactive(LED_1_Timer_EventControl);
          emberEventControlSetInactive(LED_2_Timer_EventControl);
          emberEventControlSetInactive(LED_3_Timer_EventControl);
          GPIO_PinOutSet(LED_1_port, LED_1_pin);
          GPIO_PinOutSet(LED_2_port, LED_2_pin);
          GPIO_PinOutSet(LED_3_port, LED_3_pin);
          emberClearBindingTable();
          sl_sleeptimer_delay_millisecond(5000);
          emberEventControlSetDelayMS(LED_1_Timer_EventControl, 250);
          emberEventControlSetDelayMS(LED_2_Timer_EventControl, 250);
          emberEventControlSetDelayMS(LED_3_Timer_EventControl, 250);
          Binding_Clear_code = 0;
        }
        Cycle_state++;
        break;

      case CYCLE_READ_TEMP_SENSORS:
        //TODO: Погодозависимое управление по уличному датчику температуры
        Cycle_state++;
        break;

      case CYCLE_DATA_PROCESSING:
        if (GPIO_PinOutGet(Relay_Valve_1_port, Relay_Valve_1_pin)
         || GPIO_PinOutGet(Relay_Valve_2_port, Relay_Valve_2_pin))
        {
          GPIO_PinOutSet(Relay_Pump_port, Relay_Pump_pin);
        }
        else GPIO_PinOutClear(Relay_Pump_port, Relay_Pump_pin);
        Cycle_state++;
        break;

      case CYCLE_IDLE:
        emberEventControlSetDelayMS(Main_Cycle_Timer_EventControl, MAIN_CYCLE_TIMEOUT);
        Cycle_state = CYCLE_END;
        break;

      default:
        Cycle_state = CYCLE_END;
        break;
    }
  }
}

void LED_1_Timer_EventHandler(void)
{
  static uint8_t flag = 0;
  static uint8_t cnt = 0;

  if (emberAfNetworkState() == EMBER_JOINED_NETWORK)
  {
    if (flag && cnt > 3)
    {
      if (!start_binding_valve_1) GPIO_PinOutClear(LED_1_port, LED_1_pin);
      if (!start_binding_valve_2) GPIO_PinOutClear(LED_2_port, LED_2_pin);
      if (!start_binding_outdoor_temp) GPIO_PinOutClear(LED_3_port, LED_3_pin);
      cnt = 0;
      flag = !flag;
    }
    else if (cnt > 3)
    {
      if (!start_binding_valve_1) GPIO_PinOutSet(LED_1_port, LED_1_pin);
      if (!start_binding_valve_2) GPIO_PinOutSet(LED_2_port, LED_2_pin);
      if (!start_binding_outdoor_temp) GPIO_PinOutSet(LED_3_port, LED_3_pin);
      cnt = 0;
      flag = !flag;
    }
    if (start_binding_valve_1)
    {
      if (cnt % 2) GPIO_PinOutClear(LED_1_port, LED_1_pin);
      else GPIO_PinOutSet(LED_1_port, LED_1_pin);
    }
    if (start_binding_valve_2)
    {
      if (cnt % 2) GPIO_PinOutClear(LED_2_port, LED_2_pin);
      else GPIO_PinOutSet(LED_2_port, LED_2_pin);
    }
    if (start_binding_outdoor_temp)
    {
      if (cnt % 2) GPIO_PinOutClear(LED_3_port, LED_3_pin);
      else GPIO_PinOutSet(LED_3_port, LED_3_pin);
    }
    cnt++;
    emberEventControlSetDelayMS(LED_1_Timer_EventControl, 250);
  }
  else
  {
    if (flag == 0)
    {
      GPIO_PinOutSet(LED_1_port, LED_1_pin);
      GPIO_PinOutClear(LED_2_port, LED_2_pin);
      GPIO_PinOutClear(LED_3_port, LED_3_pin);
      flag++;
    }
    else if (flag == 1)
    {
      GPIO_PinOutClear(LED_1_port, LED_1_pin);
      GPIO_PinOutSet(LED_2_port, LED_2_pin);
      GPIO_PinOutClear(LED_3_port, LED_3_pin);
      flag++;
    }
    else if (flag == 2)
    {
      GPIO_PinOutClear(LED_1_port, LED_1_pin);
      GPIO_PinOutClear(LED_2_port, LED_2_pin);
      GPIO_PinOutSet(LED_3_port, LED_3_pin);
      flag = 0;
    }
    emberEventControlSetDelayMS(LED_1_Timer_EventControl, 250);
  }
}
void LED_2_Timer_EventHandler(void)
{/*
  static uint8_t flag = 0;

  if (emberAfNetworkState() == EMBER_JOINED_NETWORK && start_binding_valve_2)
  {
    if (flag) GPIO_PinOutClear(LED_2_port, LED_2_pin);
    else GPIO_PinOutSet(LED_2_port, LED_2_pin);
    flag = !flag;
    emberEventControlSetDelayMS(LED_2_Timer_EventControl, 250);
  }*/
}
void LED_3_Timer_EventHandler(void)
{/*
  static uint8_t flag = 0;

  if (emberAfNetworkState() == EMBER_JOINED_NETWORK && start_binding_outdoor_temp)
  {
    if (flag) GPIO_PinOutClear(LED_3_port, LED_3_pin);
    else GPIO_PinOutSet(LED_3_port, LED_3_pin);
    flag = !flag;
    emberEventControlSetDelayMS(LED_3_Timer_EventControl, 250);
  }*/
}

void gpio_init(void)
{
  CMU_ClockEnable(cmuClock_GPIO, true);
  GPIO_PinModeSet(LED_1_port,
                  LED_1_pin,
                  gpioModePushPull,
                  0);
  GPIO_PinModeSet(LED_2_port,
                  LED_2_pin,
                  gpioModePushPull,
                  0);
  GPIO_PinModeSet(LED_3_port,
                  LED_3_pin,
                  gpioModePushPull,
                  0);
  GPIO_PinModeSet(Relay_Valve_1_port,
                  Relay_Valve_1_pin,
                  gpioModePushPull,
                  0);
  GPIO_PinModeSet(Relay_Valve_2_port,
                  Relay_Valve_2_pin,
                  gpioModePushPull,
                  0);
  GPIO_PinModeSet(Relay_Pump_port,
                  Relay_Pump_pin,
                  gpioModePushPull,
                  0);
  GPIO_PinModeSet(Relay_Mixer_Valve_Direction_port,
                  Relay_Mixer_Valve_Direction_pin,
                  gpioModePushPull,
                  0);
  GPIO_PinModeSet(Relay_Mixer_Valve_Switch_port,
                  Relay_Mixer_Valve_Switch_pin,
                  gpioModePushPull,
                  0);
}
