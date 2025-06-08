#include <Arduino.h>
//#include <LEDControl.h>  //点亮三色LED
#include "WifiControl.h"
#include <HTTPClient.h>     //http请求



void setup() {
  // pinMode(1,OUTPUT);//初始化GPIO
  // digitalWrite(1,1);//设置GPIO值

  // Serial.begin(115200);//初始化串口通信
  // Serial.printf("%s","Hello,World!");
  // LED_Init();
  Serial.begin(115200);
  delay(5000);
  wifi_Init();
}

void loop() {

  // LED_Blink();
  // while(Serial.available())
  // String str = Serial.readString();
  // // String s = "aaaaaaa";
  // Serial.print("receive:");//print，printf没有换行
  // Serial.println(str);//println自动换行
  //delay(1000);
   // wait for WiFi connection
    HTTPClient http;      //初始化http客户端（浏览器）

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
    http.begin("https://api.seniverse.com/v3/weather/now.json?key=SF0xkKxvs0SrlFT-t&location=beijing&language=zh-Hans&unit=c"); //HTTP要访问的网址

    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if(httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      
        // file found at server
        //httpCode：访问状态码，等于200就是成功，404或403就是失败
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
        }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();


  delay(10000);
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
