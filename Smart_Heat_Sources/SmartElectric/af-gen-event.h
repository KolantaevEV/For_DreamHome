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
  extern EmberEventControl Main_Cycle_Timer_EventControl; \
  extern EmberEventControl emberAfPluginButtonInterfaceButton0PressedEventControl; \
  extern EmberEventControl emberAfPluginButtonInterfaceButton0ReleasedEventControl; \
  extern EmberEventControl emberAfPluginButtonInterfaceButton1PressedEventControl; \
  extern EmberEventControl emberAfPluginButtonInterfaceButton1ReleasedEventControl; \
  extern EmberEventControl emberAfPluginButtonInterfaceButtonTimeoutEventControl; \
  extern EmberEventControl emberAfPluginFindAndBindInitiatorCheckTargetResponsesEventControl; \
  extern EmberEventControl emberAfPluginFormAndJoinCleanupEventControl; \
  extern EmberEventControl emberAfPluginNetworkSteeringFinishSteeringEventControl; \
  extern EmberEventControl emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventControl; \
  extern void Main_Cycle_Timer_EventHandler(void); \
  extern void emberAfPluginButtonInterfaceButton0PressedEventHandler(void); \
  extern void emberAfPluginButtonInterfaceButton0ReleasedEventHandler(void); \
  extern void emberAfPluginButtonInterfaceButton1PressedEventHandler(void); \
  extern void emberAfPluginButtonInterfaceButton1ReleasedEventHandler(void); \
  extern void emberAfPluginButtonInterfaceButtonTimeoutEventHandler(void); \
  extern void emberAfPluginFindAndBindInitiatorCheckTargetResponsesEventHandler(void); \
  extern void emberAfPluginFormAndJoinCleanupEventHandler(void); \
  extern void emberAfPluginNetworkSteeringFinishSteeringEventHandler(void); \
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


// EmberEventData structs used to populate the EmberEventData table
#define EMBER_AF_GENERATED_EVENTS   \
  { &emberAfIdentifyClusterServerTickCallbackControl1, emberAfIdentifyClusterServerTickCallbackWrapperFunction1 }, \
  { &emberAfIdentifyClusterServerTickCallbackControl2, emberAfIdentifyClusterServerTickCallbackWrapperFunction2 }, \
  { &Main_Cycle_Timer_EventControl, Main_Cycle_Timer_EventHandler }, \
  { &emberAfPluginButtonInterfaceButton0PressedEventControl, emberAfPluginButtonInterfaceButton0PressedEventHandler }, \
  { &emberAfPluginButtonInterfaceButton0ReleasedEventControl, emberAfPluginButtonInterfaceButton0ReleasedEventHandler }, \
  { &emberAfPluginButtonInterfaceButton1PressedEventControl, emberAfPluginButtonInterfaceButton1PressedEventHandler }, \
  { &emberAfPluginButtonInterfaceButton1ReleasedEventControl, emberAfPluginButtonInterfaceButton1ReleasedEventHandler }, \
  { &emberAfPluginButtonInterfaceButtonTimeoutEventControl, emberAfPluginButtonInterfaceButtonTimeoutEventHandler }, \
  { &emberAfPluginFindAndBindInitiatorCheckTargetResponsesEventControl, emberAfPluginFindAndBindInitiatorCheckTargetResponsesEventHandler }, \
  { &emberAfPluginFormAndJoinCleanupEventControl, emberAfPluginFormAndJoinCleanupEventHandler }, \
  { &emberAfPluginNetworkSteeringFinishSteeringEventControl, emberAfPluginNetworkSteeringFinishSteeringEventHandler }, \
  { &emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventControl, emberAfPluginUpdateTcLinkKeyBeginTcLinkKeyUpdateEventHandler }, \
  { &emberAfPluginScanDispatchScanNetworkEventControls[0], emberAfPluginScanDispatchScanNetworkEventWrapper0 }, \


#define EMBER_AF_GENERATED_EVENT_STRINGS   \
  "Identify Cluster Server EP 1",  \
  "Identify Cluster Server EP 2",  \
  "Main_ cycle_ timer_ event control",  \
  "Button Interface Plugin Button0Pressed",  \
  "Button Interface Plugin Button0Released",  \
  "Button Interface Plugin Button1Pressed",  \
  "Button Interface Plugin Button1Released",  \
  "Button Interface Plugin ButtonTimeout",  \
  "Find and Bind Initiator Plugin CheckTargetResponses",  \
  "Form and Join Library Plugin Cleanup",  \
  "Network Steering Plugin FinishSteering",  \
  "Update TC Link Key Plugin BeginTcLinkKeyUpdate",  \
  "Scan Dispatch Plugin Scan NWK 0", \


// The length of the event context table used to track and retrieve cluster events
#define EMBER_AF_EVENT_CONTEXT_LENGTH 2

// EmberAfEventContext structs used to populate the EmberAfEventContext table
#define EMBER_AF_GENERATED_EVENT_CONTEXT { 0x1, 0x3, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIdentifyClusterServerTickCallbackControl1}, \
{ 0x2, 0x3, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIdentifyClusterServerTickCallbackControl2}


#endif // __AF_GEN_EVENT__