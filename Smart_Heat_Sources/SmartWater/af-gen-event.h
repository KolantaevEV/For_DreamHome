// This file is generated by Simplicity Studio.  Please do not edit manually.
//
//

// Enclosing macro to prevent multiple inclusion
#ifndef __AF_GEN_EVENT__
#define __AF_GEN_EVENT__


// Code used to configure the cluster event mechanism
#define EMBER_AF_GENERATED_EVENT_CODE \
  EmberEventControl emberAfIdentifyClusterServerTickCallbackControl1; \
  EmberEventControl emberAfIdentifyClusterServerTickCallbackControl2; \
  EmberEventControl emberAfIdentifyClusterServerTickCallbackControl3; \
  extern EmberEventControl LED_1_Timer_EventControl; \
  extern EmberEventControl LED_2_Timer_EventControl; \
  extern EmberEventControl LED_3_Timer_EventControl; \
  extern EmberEventControl Main_Cycle_Timer_EventControl; \
  extern EmberEventControl emberAfPluginButtonInterfaceButton0PressedEventControl; \
  extern EmberEventControl emberAfPluginButtonInterfaceButton0ReleasedEventControl; \
  extern EmberEventControl emberAfPluginButtonInterfaceButton1PressedEventControl; \
  extern EmberEventControl emberAfPluginButtonInterfaceButton1ReleasedEventControl; \
  extern EmberEventControl emberAfPluginButtonInterfaceButton2PressedEventControl; \
  extern EmberEventControl emberAfPluginButtonInterfaceButton2ReleasedEventControl; \
  extern EmberEventControl emberAfPluginButtonInterfaceButtonTimeoutEventControl; \
  extern EmberEventControl emberAfPluginFormAndJoinCleanupEventControl; \
  extern EmberEventControl emberAfPluginNetworkSteeringFinishSteeringEventControl; \
  extern EmberEventControl emberAfPluginReportingTickEventControl; \
  extern EmberEventControl emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventControl; \
  extern void LED_1_Timer_EventHandler(void); \
  extern void LED_2_Timer_EventHandler(void); \
  extern void LED_3_Timer_EventHandler(void); \
  extern void Main_Cycle_Timer_EventHandler(void); \
  extern void emberAfPluginButtonInterfaceButton0PressedEventHandler(void); \
  extern void emberAfPluginButtonInterfaceButton0ReleasedEventHandler(void); \
  extern void emberAfPluginButtonInterfaceButton1PressedEventHandler(void); \
  extern void emberAfPluginButtonInterfaceButton1ReleasedEventHandler(void); \
  extern void emberAfPluginButtonInterfaceButton2PressedEventHandler(void); \
  extern void emberAfPluginButtonInterfaceButton2ReleasedEventHandler(void); \
  extern void emberAfPluginButtonInterfaceButtonTimeoutEventHandler(void); \
  extern void emberAfPluginFormAndJoinCleanupEventHandler(void); \
  extern void emberAfPluginNetworkSteeringFinishSteeringEventHandler(void); \
  extern void emberAfPluginReportingTickEventHandler(void); \
  extern void emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventHandler(void); \
  static void networkEventWrapper(EmberEventControl *control, EmberAfNetworkEventHandler handler, uint8_t networkIndex) \
  { \
    emberAfPushNetworkIndex(networkIndex); \
    emberEventControlSetInactive(*control); \
    (*handler)(); \
    emberAfPopNetworkIndex(); \
  } \
  EmberEventControl emberAfPluginScanDispatchScanNetworkEventControls[1]; \
  extern void emberAfPluginScanDispatchScanNetworkEventHandler(void); \
  void emberAfPluginScanDispatchScanNetworkEventWrapper0(void) { networkEventWrapper(&emberAfPluginScanDispatchScanNetworkEventControls[0], emberAfPluginScanDispatchScanNetworkEventHandler, 0); } \
  static void clusterTickWrapper(EmberEventControl *control, EmberAfTickFunction callback, uint8_t endpoint) \
  { \
    emberAfPushEndpointNetworkIndex(endpoint); \
    emberEventControlSetInactive(*control); \
    (*callback)(endpoint); \
    emberAfPopNetworkIndex(); \
  } \
  void emberAfIdentifyClusterServerTickCallbackWrapperFunction1(void) { clusterTickWrapper(&emberAfIdentifyClusterServerTickCallbackControl1, emberAfIdentifyClusterServerTickCallback, 1); } \
  void emberAfIdentifyClusterServerTickCallbackWrapperFunction2(void) { clusterTickWrapper(&emberAfIdentifyClusterServerTickCallbackControl2, emberAfIdentifyClusterServerTickCallback, 2); } \
  void emberAfIdentifyClusterServerTickCallbackWrapperFunction3(void) { clusterTickWrapper(&emberAfIdentifyClusterServerTickCallbackControl3, emberAfIdentifyClusterServerTickCallback, 3); } \


// EmberEventData structs used to populate the EmberEventData table
#define EMBER_AF_GENERATED_EVENTS   \
  { &emberAfIdentifyClusterServerTickCallbackControl1, emberAfIdentifyClusterServerTickCallbackWrapperFunction1 }, \
  { &emberAfIdentifyClusterServerTickCallbackControl2, emberAfIdentifyClusterServerTickCallbackWrapperFunction2 }, \
  { &emberAfIdentifyClusterServerTickCallbackControl3, emberAfIdentifyClusterServerTickCallbackWrapperFunction3 }, \
  { &LED_1_Timer_EventControl, LED_1_Timer_EventHandler }, \
  { &LED_2_Timer_EventControl, LED_2_Timer_EventHandler }, \
  { &LED_3_Timer_EventControl, LED_3_Timer_EventHandler }, \
  { &Main_Cycle_Timer_EventControl, Main_Cycle_Timer_EventHandler }, \
  { &emberAfPluginButtonInterfaceButton0PressedEventControl, emberAfPluginButtonInterfaceButton0PressedEventHandler }, \
  { &emberAfPluginButtonInterfaceButton0ReleasedEventControl, emberAfPluginButtonInterfaceButton0ReleasedEventHandler }, \
  { &emberAfPluginButtonInterfaceButton1PressedEventControl, emberAfPluginButtonInterfaceButton1PressedEventHandler }, \
  { &emberAfPluginButtonInterfaceButton1ReleasedEventControl, emberAfPluginButtonInterfaceButton1ReleasedEventHandler }, \
  { &emberAfPluginButtonInterfaceButton2PressedEventControl, emberAfPluginButtonInterfaceButton2PressedEventHandler }, \
  { &emberAfPluginButtonInterfaceButton2ReleasedEventControl, emberAfPluginButtonInterfaceButton2ReleasedEventHandler }, \
  { &emberAfPluginButtonInterfaceButtonTimeoutEventControl, emberAfPluginButtonInterfaceButtonTimeoutEventHandler }, \
  { &emberAfPluginFormAndJoinCleanupEventControl, emberAfPluginFormAndJoinCleanupEventHandler }, \
  { &emberAfPluginNetworkSteeringFinishSteeringEventControl, emberAfPluginNetworkSteeringFinishSteeringEventHandler }, \
  { &emberAfPluginReportingTickEventControl, emberAfPluginReportingTickEventHandler }, \
  { &emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventControl, emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventHandler }, \
  { &emberAfPluginScanDispatchScanNetworkEventControls[0], emberAfPluginScanDispatchScanNetworkEventWrapper0 }, \


#define EMBER_AF_GENERATED_EVENT_STRINGS   \
  "Identify Cluster Server EP 1",  \
  "Identify Cluster Server EP 2",  \
  "Identify Cluster Server EP 3",  \
  "L e d_1_ timer_ event control",  \
  "L e d_2_ timer_ event control",  \
  "L e d_3_ timer_ event control",  \
  "Main_ cycle_ timer_ event control",  \
  "Button Interface Plugin Button0Pressed",  \
  "Button Interface Plugin Button0Released",  \
  "Button Interface Plugin Button1Pressed",  \
  "Button Interface Plugin Button1Released",  \
  "Ember af plugin button interface button2 pressed event control",  \
  "Ember af plugin button interface button2 released event control",  \
  "Button Interface Plugin ButtonTimeout",  \
  "Form and Join Library Plugin Cleanup",  \
  "Network Steering Plugin FinishSteering",  \
  "Reporting Plugin Tick",  \
  "Update TC Link Key Plugin BeginTcLinkKeyUpdate",  \
  "Scan Dispatch Plugin Scan NWK 0", \


// The length of the event context table used to track and retrieve cluster events
#define EMBER_AF_EVENT_CONTEXT_LENGTH 3

// EmberAfEventContext structs used to populate the EmberAfEventContext table
#define EMBER_AF_GENERATED_EVENT_CONTEXT { 0x1, 0x3, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIdentifyClusterServerTickCallbackControl1}, \
{ 0x2, 0x3, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIdentifyClusterServerTickCallbackControl2}, \
{ 0x3, 0x3, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIdentifyClusterServerTickCallbackControl3}


#endif // __AF_GEN_EVENT__
