#include <Arduino.h>
#include <LEDControl.h>  //点亮三色LED
#include <WiFi.h>

const char* ssid     = "jk";
const char* password = "woniu@jiankong.com";



void setup() {
  // pinMode(1,OUTPUT);//初始化GPIO
  // digitalWrite(1,1);//设置GPIO值

  // Serial.begin(115200);//初始化串口通信
  // Serial.printf("%s","Hello,World!");
  // LED_Init();
  Serial.begin(115200);
  delay(5000);

  // 连接wifi

  Serial.println();
  Serial.print("[WiFi] Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // 尝试10s连接wifi，每500ms尝试一次
  int tryDelay = 500;
  int numberOfTries = 20;

  // Wait for the WiFi event
  while (true) {
      
      switch(WiFi.status()) {
        case WL_NO_SSID_AVAIL:
          Serial.println("[WiFi] SSID not found");
          break;
        case WL_CONNECT_FAILED:
          Serial.print("[WiFi] Failed - WiFi not connected! Reason: ");
          return;
          break;
        case WL_CONNECTION_LOST:
          Serial.println("[WiFi] Connection was lost");
          break;
        case WL_SCAN_COMPLETED:
          Serial.println("[WiFi] Scan is completed");
          break;
        case WL_DISCONNECTED:
          Serial.println("[WiFi] WiFi is disconnected");
          break;
        case WL_CONNECTED:
          Serial.println("[WiFi] WiFi is connected!");
          Serial.print("[WiFi] IP address: ");
          Serial.println(WiFi.localIP());
          return;
          break;
        default:
          Serial.print("[WiFi] WiFi Status: ");
          Serial.println(WiFi.status());
          break;
      }
      delay(tryDelay);
      
      if(numberOfTries <= 0){
        Serial.print("[WiFi] Failed to connect to WiFi!");
        // Use disconnect function to force stop trying to connect
        WiFi.disconnect();
        return;
      } else {
        numberOfTries--;
      }
  }
}

void loop() {

  // LED_Blink();
  // while(Serial.available())
  // String str = Serial.readString();
  // // String s = "aaaaaaa";
  // Serial.print("receive:");//print，printf没有换行
  // Serial.println(str);//println自动换行
  //delay(1000);
}

void serialEvent()
{
  // while(Serial.available())//判断是否数据接收
  // {
  //   char inchar = (char) Serial.read();
  //   Serial.print("receive:");
  //   Serial.println(inchar);
  // }
}
