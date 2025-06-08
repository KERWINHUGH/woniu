#ifndef _SCREEN_CONTROLLER_H
#define _SCREEN_CONTROLLER_H
#include <Arduino.h>
#include <TFT_eSPI.h> //TFT
#include "TAMC_GT911.h"//触摸屏的驱动库
#include <lvgl.h>//lvgl图形库

void Screen_Init();
void Screen_Loop();
#endif 
