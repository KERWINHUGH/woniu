#include <Arduino.h>
#include "WifiController.h"
#include "MqttController.h"
#include "ScreenControl.h"
#include "ui/userMainPage.h"

void setup() {
  Serial.begin(115200);//初始化串口通信
  wifi_Init();//初始化wifi模块
  mqttInit();//初始化mqtt模块
  Scree_Init();//显示模块屏幕初始化

  createMainPage();//创建首页面
}

void loop() {
 mqttLoop();//mqtt模块循环处理
 Scree_Loop();//显示模块屏幕循环
 delay(5);
}
