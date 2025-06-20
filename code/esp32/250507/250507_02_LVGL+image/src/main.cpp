#include <Arduino.h>
#include "WifiController.h"
#include "MqttController.h"
#include "ScreenControl.h"
#include "ui/userMainPage.h"
#include "image/image1.h"
#include "image/image2.h"
#include "image/image3.h"
// 图片资源数组
const lv_img_dsc_t *images[] = {
    &image1,
    &image2,
    &image3,
};

// 当前显示的图片索引
int current_image_index = 0;

// 定时器回调函数
void timer_callback(lv_timer_t *timer) {
    lv_obj_t *img = (lv_obj_t *)timer->user_data;  // 获取图片对象
    current_image_index = (current_image_index + 1) % (sizeof(images) / sizeof(images[0]));  // 切换到下一张图片
    lv_img_set_src(img, images[current_image_index]);  // 设置新的图片源
}

// 触摸事件回调函数
void event_handler(lv_event_t *e) {
    Serial.printf("Touch event triggered\n");  // 添加调试信息
    //lv_obj_t *img = lv_event_get_target(e);  // 获取触发事件的对象
    //lv_timer_t *timer = (lv_timer_t *)lv_obj_get_user_data(e);  // 获取定时器
    lv_timer_t *timer = (lv_timer_t *)lv_event_get_user_data(e);
    // 停止定时器
    lv_timer_del(timer);

    // 清除当前屏幕上的所有对象
    lv_obj_clean(lv_scr_act());

    //调用首页显示页面（就是有选项卡的页面）
    createMainPage();
}

void setup_screen() {
    // 创建一个图片对象
    lv_obj_t *img = lv_img_create(lv_scr_act());  // 在当前屏幕上创建图片对象
    // 设置初始图片
    lv_img_set_src(img, images[current_image_index]);

    // 设置图片的位置
    lv_obj_set_pos(img, 10, 10);

    // 创建定时器
    lv_timer_t *timer = lv_timer_create(timer_callback, 2000, img);  // 每2秒切换一次图片
    Serial.printf("Timer created\n");  // 添加调试信息

    // 将定时器存储在图片对象的用户数据中
    lv_obj_set_user_data(img, timer);
    Serial.printf("User data set\n");  // 添加调试信息在Se

    // 添加触摸事件回调
    lv_obj_add_event_cb(lv_scr_act(), event_handler, LV_EVENT_CLICKED, timer);
    Serial.printf("Event handler added\n");  // 添加调试信息
}

void setup() {
  Serial.begin(115200);//初始化串口通信
  wifi_Init();//初始化wifi模块
  mqttInit();//初始化mqtt模块
  Scree_Init();//显示模块屏幕初始化

  //createMainPage();//创建首页面
  setup_screen();
}

void loop() {
 mqttLoop();//mqtt模块循环处理
 Scree_Loop();//显示模块屏幕循环
 delay(5);
}
