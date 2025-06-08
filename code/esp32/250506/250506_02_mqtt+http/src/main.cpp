#include <Arduino.h>
#include "WifiController.h"
#include "MqttController.h"
#include <TFT_eSPI.h> // Hardware-specific library
#include "TAMC_GT911.h"
#include <lvgl.h>

//建立一个显示屏对象
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
//建立一个触摸屏的对象
TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);

void setup() {
  Serial.begin(115200);//初始化串口通信
  wifi_Init();//初始化wifi模块
  mqttInit();//初始化mqtt模块

  //显示屏的初始化
  tft.init();
  tft.setRotation(3);

  //触摸屏的初始化
  tp.begin();
  tp.setRotation(ROTATION_LEFT);
}

void loop() {
 // mqttLoop();//mqtt模块循环处理

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
