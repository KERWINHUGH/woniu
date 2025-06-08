#include <Arduino.h>
#include <WiFiControl.h>
#include <HTTPClient.h>
#include "httpControl.h"
#include "mqtt_client.h"
#include <PubSubClient.h>


const char* mqtt_server = "120.26.64.89";
const int mqtt_port = 1883;
const char* mqtt_username = "zg";
const char* mqtt_password = "12345678";

WiFiClient espClient;
PubSubClient client(espClient);

//收到订阅的消息后回调函数
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
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
      if (mqttClient.connect(clientId.c_str()),mqtt_username,mqtt_password) {
        Serial.println("connected");
        // 一旦连接成功，就订阅zhangge这个主题
        client.subscribe("zhangge");
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }

void mqttInit(void)
{
  //mqtt客户端服务器设置
  client.setServer(mqtt_server, 1883);
  //如果收到了订阅的信息，就调用callback函数处理信息
  client.setCallback(callback);
}

void mqttPublish(String topic,String payload)
{
    mqttClient_publish(topic.c_str(),payload.c_str());
}

void mqttLoop(void)
{
  //如果连接断开，就重新连接MQTT服务器
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    mqttClient.loop();
}
