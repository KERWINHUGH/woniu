#include <Arduino.h>
#include "MqttController.h"
#include <WiFi.h>
#include "cJSON.h"
#include <Arduino.h>

//基本mqtt的链接信息
const char* mqtt_server = "120.26.64.89";
const int mqtt_port = 1883;
const char* mqtt_username = "zg";
const char* mqtt_password = "12345678";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

//收到订阅的信息后的回调函数
//会接收主题为zhudongdong ,内容是{"boxId":4,"boxName":"zhudongdong","phone":1589,"putData":"2025-05-08 10:17:28"}
void callback(char* topic, byte* payload, unsigned int length) {
  //接收MQTT的信息  
  String message = "";
    for (int i = 0; i < length; i++) {
      message += (char)payload[i];
    }
    //解析接收到的json
    Serial.println(message);
    cJSON *root = cJSON_Parse(message.c_str());
    if(root != NULL)
    {
      cJSON *boxId = cJSON_GetObjectItem(root,"boxId");
      if(boxId ->valueint < 0){
        Serial.printf("箱子满了，请稍后再试！");
      }else
      {
        Serial.printf("开柜门。柜门编号：%d\n",boxId->valueint);
      }
    }

    Serial.println(message);
  }

  //连接MQTT服务器
void reconnect() {
    // Loop until we're reconnected
    while (!mqttClient.connected()) {
      Serial.print("Attempting MQTT connection...");
      // Create a random client ID
      String clientId = "ESP8266Client-";
      clientId += String(random(0xffff), HEX);
      // Attempt to connect
      if (mqttClient.connect(clientId.c_str(),mqtt_username,mqtt_password)) {
        Serial.println("connected");
        //一旦连接成功，就订阅zhangge这个主题
        mqttClient.subscribe("zhudongdong");
      } else {
        Serial.print("failed, rc=");
        Serial.print(mqttClient.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }

void mqttInit(void)
{
    //mqtt客户端连接服务器设置
    mqttClient.setServer(mqtt_server, mqtt_port);
    //如果收到了订阅的信息，就调用callback函数处理信息
    mqttClient.setCallback(callback);
}

void mqttPublish(String topic, String payload)
{
    mqttClient.publish(topic.c_str(), payload.c_str());
}

void mqttLoop(void)
{
    //如果断开连接，就重新连接MQTT服务器
    if (!mqttClient.connected()) {
        reconnect();
    }
    //mqtt用来维持心跳，和监视是否有订阅的消息到来
    mqttClient.loop();
}