#ifndef _MQTTCONTROL_H
#define _MQTTCONTROL_H

#include <PubSubClient.h>

void mqttInit(void);

void mqttPublish(String topic,String payload);

void mqttLoop(void);

#endif