#include <Arduino.h>
#include <WiFiControl.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include "TAMC_GT911.h"
#include "MQTTControl.h"
#include "lvgl.h"


//建立一个显示屏对象
TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);
//建立一个触摸屏对象
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

#define TFT_GREY 0x5AEB // New colour

void setup() {
  Serial.begin(115200);
  delay(5000);
  wifi_Init();
  mqttInit();
  //显示屏
  tft.begin();
  tft.setRotation(3);
  //触摸屏
  tp.begin();
  tp.setRotation(ROTATION_LEFT);
}


void loop() {
  
  //mqttLoop();//mqtt循环模块处理
  tp.read();
  if (tp.isTouched){
    for (int i=0; i<tp.touches; i++){
      Serial.print("Touch ");Serial.print(i+1);Serial.print(": ");;
      Serial.print("  x: ");Serial.print(tp.points[i].x);
      Serial.print("  y: ");Serial.print(tp.points[i].y);
      Serial.print("  size: ");Serial.println(tp.points[i].size);
      Serial.println(' ');
    }
  }
  delay(5);
}

