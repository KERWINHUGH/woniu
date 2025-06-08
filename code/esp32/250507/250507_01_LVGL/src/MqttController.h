#ifndef _MQTT_CONTROLLER_H
#define _MQTT_CONTROLLER_H
#include <PubSubClient.h>

void mqttInit(void);

void mqttPublish(String topic, String payload);

void mqttLoop(void);


#endif 
