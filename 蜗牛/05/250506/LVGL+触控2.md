开发板：维可思 = ESP32（ESP32-S3-N16R8） + 3.5寸电容触摸屏屏幕

ESP32是乐鑫公司出的一款芯片，使用tensa® 32 位 LX7 双核处理器

屏幕：耀元鸿科技集成的屏幕=TFT 显示屏+ 电容触摸

显示屏 使用ST7796U (台湾矽创)芯片

触屏 GT911(深圳汇顶) 芯片

3.5寸电容触摸屏 8bit并口 分辨率320*480 屏幕驱动ST7796 触摸驱动GT911



### 1.触摸屏 

电容触摸屏和电阻触摸屏是两种常见的触摸屏技术，它们在工作原理、应用场景和性能上有一些关键区别。

#### 1.1 电容触摸屏（Capacitive Touchscreen）

工作原理

- **电容触摸屏**使用电容感应技术来检测触摸。屏幕表面覆盖有透明的电容层（通常是由导电材料如氧化铟锡（ITO）制成）。当手指或导电物体触摸屏幕时，它会改变电容层中的电场，这种变化被传感器检测到并转化为触摸位置。

特点

- **高灵敏度**：由于电容触摸屏对轻微的触摸非常敏感，因此能够提供快速和准确的响应。
- **多点触控**：大多数电容触摸屏支持多点触控，即同时识别多个触摸点。
- **耐用性强**：电容触摸屏通常比电阻触摸屏更耐用，因为它们没有物理层的接触，减少了磨损。
- **显示效果优越**：由于触摸传感器位于玻璃表面之下，因此不会影响屏幕的显示效果。
- **适用性**：适合在手指或带电物体触摸下工作，不适用于使用手套或非导电物体的操作。

应用场景

- 智能手机、平板电脑、高端计算机显示器、现代的公共信息触摸屏等。

#### 1.2 电阻触摸屏（Resistive Touchscreen）

工作 原理

- **电阻触摸屏**使用两层导电透明膜（通常是由ITO制成），它们之间有微小的间隔。当屏幕被触摸时，膜层会接触，从而改变电阻值。触摸的位置被检测到并转化为触摸坐标。

特点

- **物理接触**：电阻触摸屏需要物理接触才能工作。它们可以用任何物体（如手指、笔、手套等）进行操作。
- **相对不灵敏**：比电容触摸屏反应略慢，需要更大的压力来触摸屏幕。
- **耐磨性较低**：由于接触面直接接触，电阻触摸屏的表面可能会磨损，影响使用寿命。
- **显示效果略差**：由于有两层膜层，可能会导致一些光学损失，显示效果较电容触摸屏稍差。
- **成本较低**：电阻触摸屏的制造成本通常低于电容触摸屏。

应用场景

- 工业控制面板、旧式的手机、ATM机、医疗设备等。

总结

- **电容触摸屏**：高灵敏度、多点触控、显示效果优越，但要求触摸对象必须是导电的，通常成本较高。
- **电阻触摸屏**：适用性广（可用任何物体操作），成本较低，但响应速度慢，耐用性相对较差，显示效果较差。

### 2.显示屏硬件介绍ST7796U

显示屏驱动芯片ST7796U (台湾矽创)

电容触摸驱动芯片GT911(深圳汇顶)

**原理图**

显示和触摸屏文档/TFT3.5_8BIT电容触摸屏原理图.pdf

![image-20240513101026036](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513101026036.png)

![image-20240513101037030](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513101037030.png)

这两排针接到什么地方？

触摸屏是320*480       

触摸屏分：电容（感应到手上的电流）和电阻触摸屏（不支持多点触控，通过压力）



![image-20240804001841868](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408040018053.png)



![image-20240804002649673](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408040026789.png)



![image-20240804002842896](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408040028009.png)



所以使用8位并口

#### 屏幕图形顺序

TFT3.5_8BIT电容触摸屏原理图的m1 m2 mo（威克斯接好的高低电平）

ST7796S_SPEC_V1.0 42页，高低电平选择什么通信

耀元鸿YT350S006-DCT显示屏+电容触摸产品规格书，

M0=1  M1=1 M2=0，所以连的是8080 8bit interface---DB7:0--->耀元鸿的屏幕图---TFT电容触摸屏原理图

![image-20240907052024453](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202409070520570.png)

![image-20240907052117437](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202409070521566.png)



### 3.TFT_eSPI显示驱动的移植



> TFT_eSPI是一个显示驱动的函数库，提供了很多用于驱动各种显示驱动芯片的代码。

1. 下载TFT_eSPI库

![image-20240513103253898](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513103253898.png)

2. 注释.pio/libdeps/TFT_eSPI/User_Setup.h中的代码

![image-20240513104501140](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513104501140.png)

![image-20240513104630916](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513104630916.png)

![image-20240513104614986](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513104614986.png)

3. 在复制配置文件

   ![image-20240804005813872](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408040058013.png)

   ![image-20240513104951758](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513104951758.png)

4. 配置复制出来的文件

   ```c
   // This setup is for the RP2040 processor only when used with 8-bit parallel displays
   // See SetupX_Template.h for all options available
   //自己随便写一个，建议写成0
   #define USER_SETUP_ID 0
   
   ////////////////////////////////////////////////////////////////////////////////////////////
   // 通信方式： 8位并口
   ////////////////////////////////////////////////////////////////////////////////////////////
   #define TFT_PARALLEL_8_BIT
   
   ////////////////////////////////////////////////////////////////////////////////////////////
   // 选择要通信的显示芯片型号
   ////////////////////////////////////////////////////////////////////////////////////////////
   #define ST7796_DRIVER
   
   
   #define TFT_CS    10  //片选
   #define TFT_DC    9   //数据指令
   #define TFT_RST   14  //重置
   
   #define TFT_WR    15  //写
   #define TFT_RD    6   //读
   
   //以下8个是并口数据线
   #define TFT_D0   1  
   #define TFT_D1   2 
   #define TFT_D2   7
   #define TFT_D3   8
   #define TFT_D4   3
   #define TFT_D5   18
   #define TFT_D6   17
   #define TFT_D7   16
   
   #define TFT_BL   4				// 哪个引脚控制背光
   #define TFT_BACKLIGHT_ON LOW	//低电平点亮
   
   //定义要使用的显示模式
   #define LOAD_GLCD
   #define LOAD_FONT2
   #define LOAD_FONT4
   #define LOAD_FONT6
   #define LOAD_FONT7
   #define LOAD_FONT8
   #define LOAD_GFXFF
   
   #define SMOOTH_FONT
   ```

5. 包含我们写的配置文件

   ![image-20240513111255513](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513111255513.png)

6. 编写代码测试

   ```c
   #include <Arduino.h>
   //引入TFT_eSPI
   #include <TFT_eSPI.h>
   
   TFT_eSPI tft = TFT_eSPI(TFT_WIDTH,TFT_HEIGHT);
   
   void setup() {
       tft.begin();
       tft.fillScreen(TFT_BLUE);
       tft.fillRect(20,40,60,80,TFT_YELLOW);
   }
   
   void loop() {
   
   }
   ```

### 4.TAMC_GT911触摸驱动

> 触摸屏类型：
>
> 1. 电阻式触摸屏（以前的手机常）
>
>    采用电阻感应，使用机工接触的方式感应用户操作。
>
>    缺点：不支持多点触控，按的时候屏幕会产生形变
>
>    优点：随便什么东西都可以实现触控
>
> 2. 电容式触摸屏（现在的手机常用）
>
>    采用电容感应，能过人体的导电性来给电容充放电实现的。
>
>    优点：支持多点触控，屏幕按的时候也不会产生形变
>
>    缺点：只有导体才能触控

1. 下载驱动，搜索TAMC_GT911

   ![image-20240513141615025](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513141615025.png)

2. 添加I2C和屏幕大小的配置

   ![image-20240513141736937](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513141736937.png)

3. 编写代码

   ```c
   #include <Arduino.h>
   //引入TFT_eSPI
   #include <TFT_eSPI.h>
   #include <TAMC_GT911.h>
   
   //显示屏驱动
   TFT_eSPI tft = TFT_eSPI(TFT_WIDTH,TFT_HEIGHT);
   //触摸屏驱动
   TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);
   
   void setup() {
       //初始化串口
       Serial.begin(115200);
       //初始化TFT屏
       tft.begin();
       //初始化触摸屏
       tp.begin();
       tp.setRotation(ROTATION_NORMAL);
   }
   
   void loop() {
       //读取触摸的位置
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
   ```



 最终版本

````c
#include <Arduino.h>
#include "LED_Control.h"
#include "Wifi_Connect.h"
#include "Http_Utils.h"
#include "cJSON.h"
#include "Mqtt_Control.h"
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include <TAMC_GT911.h>
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH,TFT_HEIGHT);       
TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);

void setup() {
  //初始化串口
  Serial.begin(115200);
  //初始化wifi连接
  Wifi_Init();
  //初始化mqtt连接
  mqtt_Init();

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLUE);
  tft.fillRect(20,40,60,80,TFT_YELLOW);

  tp.begin();
  tp.setRotation(ROTATION_LEFT);
}


void loop() {
  mqtt_Loop();
  
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


````





### 5.LVGL 嵌入式轻量级图形库

> 常见的嵌入式图形库有： LVGL，emWin
>
> * 丰富且强大的模块化[图形组件](https://docs.lvgl.io/master/widgets/index.html)：按钮 (buttons)、图表 (charts)、列表 (lists)、滑动条 (sliders)、图片 (images) 等
> * 高级的图形引擎：动画、抗锯齿、透明度、平滑滚动、图层混合等效果
> * 支持多种[输入设备](https://docs.lvgl.io/master/overview/indev.html)：触摸屏、 键盘、编码器、按键等
> * 支持[多显示设备](https://docs.lvgl.io/master/overview/display.html)
> * 不依赖特定的硬件平台，可以在任何显示屏上运行
> * 配置可裁剪（最低资源占用：64 kB Flash，16 kB RAM）
> * 基于UTF-8的多语种支持，例如中文、日文、韩文、阿拉伯文等
> * 可以通过[类CSS](https://docs.lvgl.io/master/overview/style.html)的方式来设计、布局图形界面（例如：[Flexbox](https://docs.lvgl.io/master/layouts/flex.html)、[Grid](https://docs.lvgl.io/master/layouts/grid.html)）
> * 支持操作系统/freerots、外置内存、以及硬件加速（LVGL已内建支持STM32 DMA2D、SWM341 DMA2D、NXP PXP和VGLite）
> * 即便仅有[单缓冲区(frame buffer)](https://docs.lvgl.io/master/porting/display.html)的情况下，也可保证渲染如丝般顺滑
> * 全部由C编写完成，并支持C++调用
> * 支持Micropython编程，参见：[LVGL API in Micropython](https://blog.lvgl.io/2019-02-20/micropython-bindings)
> * 支持[模拟器](https://docs.lvgl.io/master/get-started/platforms/pc-simulator.html)仿真，可以无硬件依托进行开发
> * 丰富详实的[例程](https://github.com/lvgl/lvgl/tree/master/examples)
> * 详尽的[文档](http://docs.lvgl.io/)以及API参考手册，可线上查阅或可下载为PDF格式

1. 下载LVGL库

2. 或者https://www.lvgl.io/，右上角github,找到lvgl，releases，找到历史版本，下载8.4的。下载完成后，解压，放到src中就可以。

   ![image-20240513144552777](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513144552777.png)

3. 复制配置文件

   参考官方文档 Porting移植部分

   ![image-20240513145459535](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513145459535.png)

   ![image-20240804233057124](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408042330247.png)

4. 修改配置

   ![image-20240513145617965](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513145617965.png)

   ![image-20240804033650754](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/zhangge/202408040336983.png)

5. 参考代码如下

   ![image-20241119234639100](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202411192346265.png)
   
6. 编写代码

   ```c
   #include <Arduino.h>
   //引入TFT_eSPI
   #include <TFT_eSPI.h>
   #include <TAMC_GT911.h>
   #include <lvgl.h>
   
   static const uint16_t screenWidth  = TOUCH_WIDTH;
   static const uint16_t screenHeight = TOUCH_HEIGHT;
   
   //显示屏驱动
   TFT_eSPI tft = TFT_eSPI(TFT_WIDTH,TFT_HEIGHT);
   //触摸屏驱动
   TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TOUCH_WIDTH, TOUCH_HEIGHT);
   
   static lv_disp_draw_buf_t draw_buf;
   static lv_color_t buf[ screenWidth * screenHeight / 10 ];
   
   
   /* 显示缓冲区 */
   void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
   {
       uint32_t w = ( area->x2 - area->x1 + 1 );
       uint32_t h = ( area->y2 - area->y1 + 1 );
   
       tft.startWrite();
       tft.setAddrWindow( area->x1, area->y1, w, h );
       tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
       tft.endWrite();
   
       lv_disp_flush_ready( disp_drv );
   }
   
   /*触摸屏的绑定函数*/
   void my_touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data )
   {
       
   }
   
   void setup() {
       //初始化串口
       Serial.begin(115200);
       //初始lvgl
       lv_init();
       //初始化TFT屏
       tft.begin();
       tft.setRotation( 3 );
       //初始化触摸屏
       tp.begin();
       tp.setRotation(ROTATION_NORMAL);
   
       lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );
   
       /*Initialize the display*/
       static lv_disp_drv_t disp_drv;
       lv_disp_drv_init( &disp_drv );
       /*Change the following line to your display resolution*/
       disp_drv.hor_res = screenWidth;
       disp_drv.ver_res = screenHeight;
       disp_drv.flush_cb = my_disp_flush;
       disp_drv.draw_buf = &draw_buf;
       lv_disp_drv_register( &disp_drv );
   
       /*Initialize the (dummy) input device driver*/
       static lv_indev_drv_t indev_drv;
       lv_indev_drv_init( &indev_drv );
       indev_drv.type = LV_INDEV_TYPE_POINTER;
       indev_drv.read_cb = my_touchpad_read;
       lv_indev_drv_register( &indev_drv );
     
       /* 在屏幕上创建一个简单的标签 */
       lv_obj_t *label = lv_label_create( lv_scr_act() );
       lv_label_set_text( label, "Hello woniu and LVGL!");
       lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );
   }
   
   void loop() {
       lv_timer_handler(); //让lvgl开始工作
       delay( 5 );
   }
   
   ```

### 6.LVGL官方示例组件

> 复制examples\widgets\\....c，这里以textarea为例

![image-20240513162402044](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513162402044.png)

### 7.LVGL关联触摸屏数据

1. 改写my_touchpad_read函数

```c
/*触摸屏的绑定函数*/
void my_touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data )
{
    //获取触摸的数据
    tp.read();
    //如果用户触摸了屏幕
    if (tp.isTouched){
        data->state = LV_INDEV_STATE_PR;
        for (int i=0; i<tp.touches; i++){
            Serial.print("Touch ");Serial.print(i+1);Serial.print(": ");;
            Serial.print("  x: ");Serial.print(tp.points[i].x);
            Serial.print("  y: ");Serial.print(tp.points[i].y);
            Serial.print("  size: ");Serial.println(tp.points[i].size);
            Serial.println(' ');
            //把获取的触摸我数据交给lvgl
            data->point.x = tp.points[i].x;
            data->point.y = tp.points[i].y;
        }
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}
```

2. 修改配置文件

![image-20240513163527295](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/luozhaoyong/image-20240513163527295.png)

https://lvgl.io/tools/fontconverter

### 名词

#### CPT

> CPT 触摸屏中的 "CPT" 通常指的是 **Capacitive Touch Panel**，也就是电容式触摸屏。相比于传统的电阻式触摸屏，电容式触摸屏更为灵敏，能够多点触控，并且常用于智能手机、平板电脑等现代电子设备中。
>
> 电容式触摸屏通过监测人体手指或其他导体（例如触控笔）与屏幕表面的电容变化来检测触摸位置。

#### TFT

> TFT 代表 **Thin Film Transistor**（薄膜晶体管）。它是一种用于驱动显示器像素的技术，广泛应用于 **TFT-LCD**（薄膜晶体管液晶显示屏）中。
>
> TFT 技术的特点是每个像素都由一个独立的晶体管控制，这提高了显示的响应速度和图像质量。相比传统的 LCD，TFT 显示屏拥有更快的刷新率、更加生动的色彩和更高的分辨率，因此常用于智能手机、计算机显示器和电视屏幕等设备中。
>
> TFT-LCD 显示屏在许多嵌入式项目中也非常常见，尤其是涉及图形界面的应用。

## 备注

### 1、使用tft的begin还是init

>在使用 `TFT_eSPI` 库控制 TFT 屏幕时，`tft.init()` 和 `tft.begin()` 都是初始化屏幕的方法，但它们有些不同，具体的区别如下：
>
>### `tft.init()`
>
>- 这个方法通常用于某些硬件平台，它会自动根据屏幕的硬件配置进行初始化。
>- 一般来说，`tft.init()` 适用于某些特定的屏幕驱动，尤其是基于 SPI 接口的显示屏。在许多标准的 ESP32 屏幕配置中，`init()` 方法会自动处理所有必要的屏幕初始化步骤。
>- `init()` 方法本质上是对硬件进行初始化，设置屏幕尺寸和其他基础设置，适用于某些 ESP32 硬件配置和屏幕型号。
>
>### `tft.begin()`
>
>- `tft.begin()` 是 `TFT_eSPI` 库的另一种初始化方法。它也用于初始化显示屏，特别是在与 ESP32 等硬件连接时。
>- `begin()` 方法通常是更常见和标准的初始化方法，它会配置 SPI 接口，设置屏幕的尺寸、颜色模式、SPI 时钟频率等参数，并开始对屏幕进行控制。
>
>### 区别：
>
>- **`init()`** 方法是 `TFT_eSPI` 库的简化版初始化函数，适用于一些硬件平台的特定配置。
>- **`begin()`** 方法通常会提供更多的底层配置选项，并且是推荐使用的初始化函数。
>
>### 结论：
>
>如果你没有特别的需求或定制化配置，建议使用 `tft.begin()`，它是更加标准的初始化方式。如果你确认你的硬件配置要求使用 `tft.init()`，也可以使用它，但在大多数情况下，`begin()` 会更加通用。
>
>所以，在你的代码中，`tft.init()` 和 `tft.begin()` 都可以正常工作，但根据 `TFT_eSPI` 的文档和最佳实践，推荐使用 `begin()`。

### 2、屏幕完整代码

````c
#ifndef __TFTDISPLAY_H
#define __TFTDISPLAY_H
#include <Arduino.h>
#include <TFT_eSPI.h>//连接和驱动屏幕的头文件
#include "TAMC_GT911.h"//导入触摸屏的头文件
#include <lvgl.h>

void Screen_Init();
void Screen_Timer();

#endif
````



LVGl

````c
#include "TFT_Display.h"

// 配置系统的宽高
static const uint16_t screenWidth  = 480;   // 定义屏幕宽度为480像素
static const uint16_t screenHeight = 320;   // 定义屏幕高度为320像素

// LVGL的配置
static lv_disp_draw_buf_t draw_buf;         // 定义LVGL显示缓冲区结构体，用于管理屏幕刷新数据
static lv_color_t buf[screenWidth * screenHeight / 10];  // 定义颜色缓冲区，存储屏幕部分像素数据，大小为屏幕总像素的1/10以优化性能

// 显示屏的配置
TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);  // 创建TFT_eSPI对象，初始化TFT显示屏并设置分辨率

// 配置触摸屏
TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, screenWidth, screenHeight);  // 创建TAMC_GT911对象，初始化触摸屏并指定引脚和分辨率

/* 显示刷新函数 */
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    // 计算需要刷新的区域的宽度和高度
    uint32_t w = (area->x2 - area->x1 + 1);  // 宽度 = 结束x坐标 - 起始x坐标 + 1
    uint32_t h = (area->y2 - area->y1 + 1);  // 高度 = 结束y坐标 - 起始y坐标 + 1
    
    // 开始向TFT屏幕写入数据
    tft.startWrite();                       // 启动TFT的写入操作
    tft.setAddrWindow(area->x1, area->y1, w, h);  // 设置屏幕刷新的窗口区域（起始x, 起始y, 宽, 高）
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);  // 将LVGL的颜色数据推送至屏幕，转换为16位颜色格式
    tft.endWrite();                         // 结束TFT的写入操作
    
    // 通知LVGL刷新操作已完成
    lv_disp_flush_ready(disp_drv);          // 告诉LVGL当前刷新任务已完成，可以进行下一帧渲染
}

/* 读取触摸屏输入函数 */
void my_touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    tp.read();  // 读取触摸屏的当前状态和数据
    
    // 如果检测到触摸屏被按下
    if (tp.isTouched)
    {
        data->state = LV_INDEV_STATE_PR;    // 设置输入设备状态为“按下”
        for (int i = 0; i < tp.touches; i++)  // 遍历所有触摸点（支持多点触摸）
        {
            data->point.x = tp.points[i].x;  // 获取触摸点的x坐标并传递给LVGL
            data->point.y = tp.points[i].y;  // 获取触摸点的y坐标并传递给LVGL
        }
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;    // 如果没有触摸，设置状态为“释放”
    }
}

/* 屏幕初始化函数 */
void Screen_Init()
{
    // 初始化TFT显示屏
    tft.begin();            // 启动TFT显示屏
    tft.setRotation(3);     // 设置屏幕旋转方向为270度（3表示顺时针旋转270度）

    // 初始化触摸屏
    tp.begin();             // 启动触摸屏
    tp.setRotation(ROTATION_LEFT);  // 设置触摸屏旋转方向为向左旋转

    // 初始化LVGL图形库
    lv_init();              // 初始化LVGL核心功能
    
    // 初始化显示缓冲区
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 10);  // 配置显示缓冲区，使用buf作为主缓冲区，无辅助缓冲区

    /* 初始化显示驱动 */
    static lv_disp_drv_t disp_drv;      // 定义显示驱动结构体
    lv_disp_drv_init(&disp_drv);        // 初始化显示驱动
    disp_drv.hor_res = screenWidth;     // 设置水平分辨率为480像素
    disp_drv.ver_res = screenHeight;    // 设置垂直分辨率为320像素
    disp_drv.flush_cb = my_disp_flush;  // 指定显示刷新回调函数为my_disp_flush
    disp_drv.draw_buf = &draw_buf;      // 将缓冲区绑定到显示驱动
    lv_disp_drv_register(&disp_drv);    // 向LVGL注册显示驱动

    /* 初始化输入设备驱动 */
    static lv_indev_drv_t indev_drv;    // 定义输入设备驱动结构体
    lv_indev_drv_init(&indev_drv);      // 初始化输入设备驱动
    indev_drv.type = LV_INDEV_TYPE_POINTER;  // 设置输入设备类型为指针（适用于触摸屏）
    indev_drv.read_cb = my_touchpad_read;    // 指定触摸屏读取回调函数为my_touchpad_read
    lv_indev_drv_register(&indev_drv);       // 向LVGL注册输入设备驱动
}

/* 屏幕定时器函数 */
void Screen_Timer()
{
    lv_timer_handler();  // 调用LVGL的定时器处理函数，确保GUI持续刷新并响应事件
}
````

### 3、按钮效果解析

````c
#include "../../lv_examples.h"
// 只有在LV_USE_BTN（表示启用按钮功能）被定义且LV_BUILD_EXAMPLES（表示构建示例相关）被定义的情况下，以下代码才会参与编译
#if LV_USE_BTN && LV_BUILD_EXAMPLES

// 事件处理函数，用于处理按钮相关的事件
// 参数e是一个指向lv_event_t类型的指针，它包含了事件相关的各种信息
static void event_handler(lv_event_t * e)
{
    // 获取当前事件的具体代码（类型），通过lv_event_get_code函数从传入的事件结构体指针e中提取事件代码
    lv_event_code_t code = lv_event_get_code(e);

    // 判断事件代码是否为LV_EVENT_CLICKED，即按钮被点击事件
    if (code == LV_EVENT_CLICKED) {
        // 使用LV_LOG_USER宏记录一条用户级别的日志信息，提示按钮被点击了
        LV_LOG_USER("Clicked");
    }
    // 判断事件代码是否为LV_EVENT_VALUE_CHANGED，对于可切换状态的按钮（如复选框样式按钮），状态改变时会触发此事件
    else if (code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}

// 这是一个用于展示按钮示例的函数，创建并配置两个按钮
void lv_example_btn_1(void)
{
    lv_obj_t * label;

    // 创建第一个按钮对象，参数lv_scr_act()获取当前活动的屏幕对象作为父对象，创建的按钮将会显示在这个屏幕上
    lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
    // 为按钮btn1添加事件回调函数，当按钮有任何类型（LV_EVENT_ALL表示所有类型事件）的事件发生时，都会调用event_handler函数进行处理，最后一个参数NULL表示没有传递额外的数据给回调函数
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    // 将按钮btn1在父对象（这里是当前活动屏幕）中进行对齐，LV_ALIGN_CENTER表示居中对齐，后面的0和 -40分别表示在水平方向上无偏移，在垂直方向上向上偏移40像素（以屏幕的中心为参考点）
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);

    // 在按钮btn1上创建一个标签对象，这个标签将用于显示按钮上的文字等内容
    label = lv_label_create(btn1);
    // 设置标签的文本内容为"Button"
    lv_label_set_text(label, "Button");
    // 将标签在其父对象（也就是按钮btn1）中居中显示
    lv_obj_center(label);

    // 创建第二个按钮对象，同样以当前活动屏幕作为父对象
    lv_obj_t * btn2 = lv_btn_create(lv_scr_act());
    // 为按钮btn2添加事件回调函数，处理所有类型的事件，和第一个按钮类似
    lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
    // 将按钮btn2在父对象（当前活动屏幕）中进行对齐，LV_ALIGN_CENTER表示居中对齐，0和40分别表示水平方向无偏移，垂直方向向下偏移40像素（以屏幕中心为参考点）
    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
    // 为按钮btn2添加一个标志位LV_OBJ_FLAG_CHECKABLE，表示这个按钮是可切换状态的（类似复选框的功能）
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    // 设置按钮btn2的高度为根据其内容自动适配（LV_SIZE_CONTENT表示根据内容自动确定尺寸）
    lv_obj_set_height(btn2, LV_SIZE_CONTENT);

    // 在按钮btn2上创建一个标签对象
    label = lv_label_create(btn2);
    // 设置标签的文本内容为"Toggle"
    lv_label_set_text(label, "Toggle");
    // 将标签在其父对象（也就是按钮btn2）中居中显示
    lv_obj_center(label);
}
#endif
````

1. **引入头文件**：`#include "../../lv_examples.h"` 是引入LVGL示例代码的相关头文件，通常用来包含所需的基本库和函数。
2. **事件处理函数**：`event_handler` 是按钮事件的回调函数，它会根据按钮触发的事件类型输出相应的日志：
   - `LV_EVENT_CLICKED` 事件会在按钮被点击时触发。
   - `LV_EVENT_VALUE_CHANGED` 事件会在按钮的选中状态发生变化时触发（例如切换按钮的状态）。
3. **按钮创建与布局**：
   - `lv_btn_create`：创建一个按钮对象并将其添加到当前屏幕。
   - `lv_obj_align`：调整按钮的位置，这里按钮被定位到屏幕中央，并且第一个按钮向上偏移40像素，第二个按钮向下偏移40像素。
   - `lv_label_create`：为按钮创建一个标签，并通过 `lv_label_set_text` 设置标签的文本。
   - `lv_obj_center`：将标签居中显示在按钮上。
4. **按钮状态设置**：
   - 第二个按钮被设置为“可切换”（`LV_OBJ_FLAG_CHECKABLE`），这意味着它在被点击时可以在选中与未选中状态之间切换。
   - `lv_obj_set_height` 设置按钮的高度为内容的高度，确保按钮高度适应标签的大小。

这段代码实现了在LVGL屏幕上显示两个按钮，第一个是普通的点击按钮，第二个是具有切换功能的按钮。当按钮被点击时，控制台会输出日志，分别显示为 "Clicked" 和 "Toggled"。

### 4、判断哪个按钮被点了

```c
#include <Arduino.h>
#include "lvgl.h"

// 声明全局变量保存按钮对象
lv_obj_t *btn1;
lv_obj_t *btn2;

// 按钮事件回调函数
static void event_handler(lv_event_t * e)
{
    lv_obj_t * btn = lv_event_get_target(e); // 获取触发事件的按钮对象
    lv_event_code_t code = lv_event_get_code(e); // 获取事件类型

    if(code == LV_EVENT_CLICKED) { // 如果是按钮点击事件
        if(btn == btn1) { // 判断是否是第一个按钮
            Serial.println("第一个按钮被点击了");
        } 
        else if(btn == btn2) { // 判断是否是第二个按钮
            Serial.println("第二个按钮被点击了");
        }
    }
}

// 示例函数：创建两个按钮
void lv_example_btn_1(void)
{
    lv_obj_t * label;

    // 创建第一个按钮
    btn1 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);

    label = lv_label_create(btn1);
    lv_label_set_text(label, "Button");
    lv_obj_center(label);

    // 创建第二个按钮
    btn2 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);

    label = lv_label_create(btn2);
    lv_label_set_text(label, "Toggle");
    lv_obj_center(label);
}

void setup() {
    Serial.begin(115200);
    lv_init();

    // 初始化屏幕等配置
    // Screen_Init();

    lv_example_btn_1();
}

void loop() {
    // 屏幕更新逻辑
    // Screen_Timer();
    lv_timer_handler();
    delay(5);
}

```

或者

````c
// 按钮事件回调函数
static void event_handler(lv_event_t * e)
{
    lv_obj_t * btn = lv_event_get_target(e); // 获取触发事件的按钮对象
    lv_event_code_t code = lv_event_get_code(e); // 获取事件类型

    if(code == LV_EVENT_CLICKED) { // 如果是按钮点击事件
        // 获取按钮上的标签对象
        lv_obj_t * label = lv_obj_get_child(btn, 0); // 获取按钮的第一个子对象（标签）
        const char * label_text = lv_label_get_text(label); // 获取标签的文本内容

        // 判断标签的内容
        if(strcmp(label_text, "Button") == 0) {
            Serial.println("Button 按钮被点击了");
        } 
        else if(strcmp(label_text, "Toggle") == 0) {
            Serial.println("Toggle 按钮被点击了");
        }
    }
}
````

### 5、user_main.cpp

````c
#include "user_main.h"
#include "user_get_package.h"
#include "put_package.h"

// 函数功能：创建主页面，该主页面包含一个选项卡视图（Tab view），有“取件”和“寄件”两个选项卡，
// 并且对选项卡视图及其内部的各个元素进行样式设置，同时在相应的选项卡页面内调用其他函数来进一步构建页面内容
void create_main_page()
{
    /*Create a Tab view object*/
    lv_obj_t * tabview;
    // 使用lv_tabview_create函数创建一个选项卡视图（Tab view）对象。
    // lv_scr_act()获取当前活动的屏幕对象作为其父组件，也就是这个选项卡视图会显示在整个屏幕上。
    // LV_DIR_LEFT表示选项卡按钮的排列方向是从左到右（水平方向且居左排列），80表示选项卡按钮区域预估的宽度（单位通常由LVGL库的相关设置决定，可能是像素等）
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_LEFT, 80);

    // 使用lv_obj_set_style_bg_color函数设置选项卡视图（tabview）的背景颜色。
    // lv_palette_lighten(LV_PALETTE_RED, 2) 表示通过LVGL的调色板功能获取一种变浅的红色（变浅程度为2个等级，具体变浅规则由LVGL内部定义），
    // 最后一个参数0表示应用该样式到所有状态（LVGL支持不同状态下设置不同样式，例如默认、按下、选中等等，0表示通用设置）
    lv_obj_set_style_bg_color(tabview, lv_palette_lighten(LV_PALETTE_RED, 2), 0);

    // 使用lv_tabview_get_tab_btns函数获取选项卡视图（tabview）中用于放置选项卡按钮的区域对象，后续可以针对这个区域进行样式等相关设置
    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);

    // 使用lv_obj_set_style_bg_color函数设置选项卡按钮区域（tab_btns）的背景颜色为深灰色。
    // lv_palette_darken(LV_PALETTE_GREY, 3) 表示通过LVGL的调色板功能获取一种加深的灰色（加深程度为3个等级），同样最后参数0表示应用到所有状态
    lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
    // 使用lv_obj_set_style_text_color函数设置选项卡按钮区域（tab_btns）内文字的颜色为浅灰色。
    // lv_palette_lighten(LV_PALETTE_GREY, 5) 表示通过LVGL的调色板功能获取一种变浅的灰色（变浅程度为5个等级），最后参数0表示应用到所有状态
    lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
    // 使用lv_obj_set_style_border_side函数设置选项卡按钮区域（tab_btns）在特定状态下的边框显示样式。
    // LV_BORDER_SIDE_RIGHT表示只在右侧显示边框，LV_PART_ITEMS | LV_STATE_CHECKED表示仅当某个选项卡按钮处于选中（被点击激活）状态时应用该边框样式
    lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);

    // 使用lv_tabview_add_tab函数向选项卡视图（tabview）中添加一个名为“取\n件”的选项卡，返回值是对应选项卡页面的对象指针，后续可以基于该页面对象添加更多内容。
    // 这里的“\n”用于在显示文本时实现换行效果，让文字排版更美观（如果LVGL支持文本换行显示的话）
    lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "取\n件");
    // 使用lv_tabview_add_tab函数向选项卡视图（tabview）中添加一个名为“寄\n件”的选项卡，同样返回对应选项卡页面的对象指针
    lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "寄\n件");

    // 使用lv_obj_set_style_bg_color函数设置第二个选项卡页面（tab2）的背景颜色为变浅的琥珀色（变浅程度为3个等级），最后参数0表示应用到所有状态
    lv_obj_set_style_bg_color(tab2, lv_palette_lighten(LV_PALETTE_AMBER, 3), 0);
    // 使用lv_obj_set_style_bg_opa函数设置第二个选项卡页面（tab2）的背景透明度，LV_OPA_COVER表示完全不透明（取值范围通常是0 - 255或者0 - 1等表示透明度程度，LV_OPA_COVER对应的是不透明的固定值，具体依LVGL设定），最后参数0表示应用到所有状态
    lv_obj_set_style_bg_opa(tab2, LV_OPA_COVER, 0);

    // 调用create_get_package_page函数，以第一个选项卡页面（tab1）为父页面（意味着在这个选项卡页面内部构建相关内容），去创建“取件”相关的具体页面内容，具体创建逻辑应该在create_get_package_page函数的实现中定义
    create_get_package_page(tab1);
    // 调用put_package_page函数，以第二个选项卡页面（tab2）为父页面，去创建“寄件”相关的具体页面内容，具体创建逻辑应该在put_package_page函数的实现中定义
    put_package_page(tab2);

    // 这里是一个待办事项的注释，提示后续可能需要继续完善“寄包裹的页面”相关功能，比如添加更多控件、布局设置等等，目前功能可能并不完整
    //TODO:等会下寄包裹的页面

    // 使用lv_obj_clear_flag函数清除选项卡视图内容区域（通过lv_tabview_get_content函数获取）的可滚动标志位，
    // 目的是让这个屏幕（准确说是选项卡视图对应的内容显示区域）不能进行滚动操作，也就是内容如果超出显示区域不会出现滚动条等滚动交互效果
    lv_obj_clear_flag(lv_tabview_get_content(tabview), LV_OBJ_FLAG_SCROLLABLE);
}
````

````c
#include "user_main.h"
#include "user_get_package.h"
#include "put_package.h"

// 创建主页面函数
void create_main_page()
{
    // 创建一个 Tabview 对象，它用于管理多个选项卡页面
    // lv_scr_act() 是当前活动屏幕，LV_DIR_LEFT 表示选项卡按钮位于屏幕左侧，宽度为 80 像素
    lv_obj_t * tabview;
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_LEFT, 80);

    // 设置 Tabview 的背景颜色为浅红色
    lv_obj_set_style_bg_color(tabview, lv_palette_lighten(LV_PALETTE_RED, 2), 0);

    // 获取左侧（选项卡按钮）区域
    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);

    // 设置选项卡按钮的背景色为深灰色
    lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 3), 0);

    // 设置选项卡按钮文字的颜色为浅灰色
    lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);

    // 设置选中的选项卡按钮（`LV_STATE_CHECKED`）的边框样式，仅右侧显示边框
    lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);

    // 添加第一个选项卡 "取件"，并返回选项卡的内容页面对象
    lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "取\n件");

    // 添加第二个选项卡 "寄件"，并返回选项卡的内容页面对象
    lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "寄\n件");

    // 设置第二个选项卡的背景颜色为浅琥珀色
    lv_obj_set_style_bg_color(tab2, lv_palette_lighten(LV_PALETTE_AMBER, 3), 0);

    // 设置第二个选项卡背景的透明度为完全不透明
    lv_obj_set_style_bg_opa(tab2, LV_OPA_COVER, 0);

    // 创建取件页面，以 tab1（第一个选项卡的内容页面）为父页面
    create_get_package_page(tab1);

    // 创建寄件页面，以 tab2（第二个选项卡的内容页面）为父页面
    put_package_page(tab2);

    // TODO: 如果需要额外的页面功能，可以在这里添加

    // 禁用 Tabview 的内容区域滚动功能，确保页面内容固定不滚动
    lv_obj_clear_flag(lv_tabview_get_content(tabview), LV_OBJ_FLAG_SCROLLABLE);
}

````

### 6、user_get_package.cpp

```c
#include "user_get_package.h"
#include "HttpUtils.h"

// 按钮矩阵事件处理函数
static void btnm_event_handler(lv_event_t * e)
{
    // 获取触发事件的源对象，即数字矩阵（按钮矩阵）
    lv_obj_t * obj = lv_event_get_target(e);

    // 获取传递过来的用户数据，这里是文本域对象，用于更新显示的文字
    lv_obj_t * ta = (lv_obj_t *)lv_event_get_user_data(e);

    // 获取被选中按钮的文本内容（例如 "1", "2", "3", LV_SYMBOL_BACKSPACE, LV_SYMBOL_NEW_LINE）
    const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));

    // 如果按下的是退格键（BACKSPACE），删除文本域中的一个字符
    if (strcmp(txt, LV_SYMBOL_BACKSPACE) == 0)
    {
        lv_textarea_del_char(ta);
    }
    // 如果按下的是换行符（ENTER），则触发相关事件
    else if (strcmp(txt, LV_SYMBOL_NEW_LINE) == 0)
    {
        // 在这里，你可以触发事件来提交文本数据（例如发送到服务器）
        // 例如，构建一个包含输入文本的 URL 进行 HTTP 请求
        String url = "http://139.9.65.174:82/box/getPackage/zhangge/" + String(lv_textarea_get_text(ta));
        
        // 通过 URL 发起 HTTP 请求，并获取响应（json 格式）
        String json = requestStrByUrl(url);
        // 打印响应结果到串口
        Serial.println(json);
    }
    // 如果按下的是普通数字键（例如 "1", "2", "3"），将其添加到文本域中
    else
    {
        lv_textarea_add_text(ta, txt);
    }
}

// 创建取件页面
void create_get_package_page(lv_obj_t * parent)
{
    // 第一块区域：创建并显示文字标签
    lv_obj_t * label = lv_label_create(parent);
    lv_label_set_text(label, "请输入取件码:"); // 设置标签内容为 "请输入取件码:"
    // 将标签置于父对象的顶部中央，并设置距离顶部5个像素
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 5);

    // 第二块区域：创建文本域（textarea），用户输入取件码
    lv_obj_t * ta = lv_textarea_create(parent); // 创建一个文本域
    lv_textarea_set_one_line(ta, true); // 设置为单行输入（不允许换行）
    // 将文本域置于父对象的上方中央，距离顶部55个像素，宽度和高度已适当设置
    lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 55);

    // 绑定事件：当文本域发生 LV_EVENT_READY 事件时，执行 textarea_event_handler 函数
    // 目前这个事件被注释掉了，如果需要，可以启用
    // lv_obj_add_event_cb(ta, textarea_event_handler, LV_EVENT_READY, ta);

    // 设置光标默认处于文本域内，确保用户输入时光标是可见的
    lv_obj_add_state(ta, LV_STATE_FOCUSED); 

    // 第三块区域：创建数字按钮矩阵（数字键盘）
    static const char * btnm_map[] = {
        "1", "2", "3", "\n",
        "4", "5", "6", "\n",
        "7", "8", "9", "\n",
        LV_SYMBOL_BACKSPACE, "0", LV_SYMBOL_NEW_LINE, ""
    };

    // 创建按钮矩阵（数字键盘），父对象为当前页面
    lv_obj_t * btnm = lv_btnmatrix_create(parent);
    // 设置按钮矩阵使用默认字体（Montserrat 14）
    lv_obj_set_style_text_font(btnm, &lv_font_montserrat_14, 0);
    // 设置按钮矩阵的大小，宽度 300 像素，高度 160 像素
    lv_obj_set_size(btnm, 300, 160);
    // 将按钮矩阵对齐至父对象底部中央，距离底部 5 个像素
    lv_obj_align(btnm, LV_ALIGN_BOTTOM_MID, 0, -5);

    // 注册按钮矩阵的事件回调函数：当按钮值发生变化时，触发 btnm_event_handler 函数
    // ta：将文本域对象作为用户数据传递，事件处理时可以操作该文本域
    lv_obj_add_event_cb(btnm, btnm_event_handler, LV_EVENT_VALUE_CHANGED, ta);

    // 禁用按钮矩阵的点击聚焦功能，这样点击按钮不会自动将焦点转移到按钮上，保持文本域处于聚焦状态
    lv_obj_clear_flag(btnm, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    // 设置按钮矩阵的按钮映射（即按钮的内容）
    lv_btnmatrix_set_map(btnm, btnm_map);
}

```



````c
#include "user_get_package.h"
#include "HttpUtils.h"

// 以下是一个事件处理函数的定义（目前被注释掉了），原本它应该是用于处理文本域（textarea）相关事件的，
// 当文本域中按下回车键（Enter）时，会在日志中记录当前文本域中的文本内容。
// 虽然当前未使用，但可能是代码开发过程中的一种备用逻辑或者后续有启用的计划。
// static void textarea_event_handler(lv_event_t * e)
// {
//     lv_obj_t * ta = lv_event_get_target(e);
//     LV_LOG_USER("Enter was pressed. The current text is: %s", lv_textarea_get_text(ta));
// }

// 定义数字矩阵（button matrix，类似键盘布局的按钮组）的事件处理函数，用于处理数字矩阵按钮点击等相关事件
// 该函数根据用户点击数字矩阵按钮的不同情况，对与之关联的文本域进行相应操作，比如添加字符、删除字符或者发起网络请求等
static void btnm_event_handler(lv_event_t * e)
{
    // 获取事件发生的源头对象，在这里就是数字矩阵（button matrix）本身，
    // 通过lv_event_get_target函数从事件结构体指针e中获取触发事件的目标对象指针
    lv_obj_t * obj = lv_event_get_target(e);
    // 获取传递过来的用户数据，在这里预先设置为指向文本域（textarea）的指针，
    // 这样在事件处理函数中就能获取到与之关联的文本域对象，进而操作文本域中的文本内容。
    // 数据是在注册事件时通过lv_event_get_user_data函数传递进来的
    lv_obj_t * ta = (lv_obj_t *)lv_event_get_user_data(e);

    // 获取数字矩阵（button matrix）中当前被选中按钮对应的文本内容，
    // lv_btnmatrix_get_selected_btn函数用于获取当前选中按钮的索引，
    // 然后通过lv_btnmatrix_get_btn_text函数根据索引获取对应的文本内容，
    // 文本内容可能是数字（如 "1"、"2" 等）、功能键符号（如退格键符号、回车键符号等）
    const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));

    // 判断获取到的按钮文本内容是否为退格键对应的符号（LV_SYMBOL_BACKSPACE），
    // 如果是，表示用户点击了退格键，需要在关联的文本域中删除一个字符
    if (strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) 
    {
        lv_textarea_del_char(ta);
    }
    else if (strcmp(txt, LV_SYMBOL_NEW_LINE) == 0) 
    {
        // 判断获取到的按钮文本内容是否为回车键对应的符号（LV_SYMBOL_NEW_LINE），
        // 如果是，表示用户点击了回车键，这里原本可能计划触发一个LV_EVENT_READY事件（目前代码中已注释掉该触发逻辑），
        // 现在的逻辑是通过HTTP请求，将文本域中的文字发送到指定的服务器地址，
        // 以下是构建请求的URL，将取件相关信息（这里硬编码了用户名 "zhangge" 和文本域中的取件码文本）拼接到URL中，
        // 用于向服务器请求获取包裹相关操作（具体的服务器接口功能由服务器端定义）
        String url = "http://139.9.65.174:82/box/getPackage/zhangge/"+String(lv_textarea_get_text(ta));
        
        // 调用requestStrByUrl函数（应该是在HttpUtils.h中定义的函数，用于发起HTTP请求并获取服务器返回的字符串响应），
        // 获取服务器返回的JSON格式数据（假设服务器响应数据是JSON格式），然后将其打印输出，可能后续会根据该JSON数据进行进一步处理
        String json = requestStrByUrl(url);
        Serial.println(json);
    }
    else // 如果点击的按钮既不是退格键也不是回车键对应的符号，也就是点击了数字按钮（如 "1"、"2"、"3" 等），
    {
        // 将点击的数字按钮对应的文本内容添加到关联的文本域中，实现类似在文本域中输入数字的效果
        lv_textarea_add_text(ta, txt);
    }
}

// 函数功能：创建“取件”页面相关的UI元素及设置相应的事件处理逻辑，
// 在传入的父对象（parent，应该是代表某个选项卡页面或者其他容器对象）上构建包含提示标签、文本域和数字矩阵按钮组的布局，并关联相应的事件处理函数
void create_get_package_page(lv_obj_t * parent)
{
    // 第一块区域：创建一个标签（label）对象，用于在页面上显示提示文字，
    // 该标签的父对象是通过参数传入的parent，意味着它会显示在parent所代表的页面区域内
    lv_obj_t *label = lv_label_create(parent);
    // 设置标签显示的文本内容为 "请输入取件码:"，用于提示用户操作
    lv_label_set_text(label,"请输入取件码:");
    // 将标签在父对象内进行对齐，LV_ALIGN_TOP_MID表示垂直方向顶部居中对齐，
    // 后面的0和5表示在水平方向无偏移，垂直方向距离顶部边界有5个像素的偏移量，以达到合适的显示位置
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 5);

    // 第二块区域：创建一个文本域（textarea）对象，作为用户输入取件码的输入框，
    // 它的父对象同样是传入的parent，即会显示在对应的页面区域内
    lv_obj_t * ta = lv_textarea_create(parent); // textarea
    // 设置文本域为单行模式，意味着用户输入的文本只能在一行内显示，通常用于输入简短的内容，比如取件码这种情况
    lv_textarea_set_one_line(ta, true);
    // 将文本域在父对象内进行对齐，LV_ALIGN_TOP_MID表示垂直方向顶部居中对齐，
    // 后面的0和55表示在水平方向无偏移，垂直方向距离顶部边界有55个像素的偏移量，以确定其在页面上的合适显示位置
    lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 55);

    // （以下代码目前被注释掉了）原本计划是给文本域添加一个事件回调函数，当文本域触发LV_EVENT_READY事件时（可能是输入完成等情况触发），
    // 会调用textarea_event_handler函数进行相应处理，但目前暂时未启用该逻辑，可能后续会根据需求重新启用或修改此处逻辑
    // lv_obj_add_event_cb(ta, textarea_event_handler, LV_EVENT_READY, ta);

    // 给文本域添加LV_STATE_FOCUSED状态，确保文本域获取焦点，这样光标会显示在文本域内，方便用户直接输入内容，
    // 提升用户交互的直观性和便捷性
    lv_obj_add_state(ta, LV_STATE_FOCUSED); /*To be sure the cursor is visible*/

    // 第三块区域：创建一个数字矩阵（button matrix）对象，用于模拟数字键盘布局，方便用户输入取件码，
    // 它的父对象也是传入的parent，会显示在对应的页面区域内
    static const char * btnm_map[] = {"1", "2", "3", "\n",
                                      "4", "5", "6", "\n",
                                      "7", "8", "9", "\n",
                                      LV_SYMBOL_BACKSPACE, "0", LV_SYMBOL_NEW_LINE, ""
                                     };
    lv_obj_t * btnm = lv_btnmatrix_create(parent);
    // 设置数字矩阵中按钮文本显示所使用的字体为lv_font_montserrat_14，通过指定字体来控制按钮上文字的外观样式，
    // 使其符合整体UI设计风格，最后一个参数0表示应用该字体样式到所有状态（LVGL支持不同状态下设置不同样式）
    lv_obj_set_style_text_font(btnm,&lv_font_montserrat_14,0);
    // 设置数字矩阵对象的大小，这里将其宽度设置为300（单位由LVGL库相关设置决定，可能是像素等），高度设置为160，
    // 以确定其在页面上的显示尺寸，使其布局更加合理、美观
    lv_obj_set_size(btnm, 300, 160);
    // 将数字矩阵在父对象内进行对齐，LV_ALIGN_BOTTOM_MID表示垂直方向底部居中对齐，
    // 后面的0和 -5表示在水平方向无偏移，垂直方向距离底部边界有 -5个像素的偏移量（也就是向上偏移5个像素），以达到合适的显示位置
    lv_obj_align(btnm, LV_ALIGN_BOTTOM_MID, 0, -5);
    // 给数字矩阵添加事件回调函数，当数字矩阵中的按钮发生值改变事件（LV_EVENT_VALUE_CHANGED，即按钮被点击等操作导致值改变时），
    // 会调用btnm_event_handler函数进行处理，并且将文本域对象指针（ta）作为用户数据传递给事件处理函数，
    // 方便在事件处理函数中操作与之关联的文本域内容
    lv_obj_add_event_cb(btnm, btnm_event_handler, LV_EVENT_VALUE_CHANGED, ta);

    // 清除数字矩阵的LV_OBJ_FLAG_CLICK_FOCUSABLE标志位，这样在点击数字矩阵按钮时，不会使文本域失去焦点，
    // 保证用户可以连续输入取件码，无需重复点击文本域获取焦点，提升用户输入体验
    lv_obj_clear_flag(btnm, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
    // 设置数字矩阵的按钮映射关系，通过传入预先定义好的btnm_map数组，确定每个按钮位置对应的文本内容，
    // 从而构建出符合要求的数字键盘布局（包含数字按钮和功能键按钮等）
    lv_btnmatrix_set_map(btnm, btnm_map);
}
````



### 7、put_package.cpp

````c
#include "put_package.h"
#include "MQTTControl.h"

// 数字矩阵按钮事件处理函数
static void btnm_event_handler(lv_event_t * e)
{
    // 获取事件源对象，这里是按钮矩阵对象
    lv_obj_t * obj = lv_event_get_target(e);

    // 获取用户数据，这里传递的是文本域对象（用于输入手机号）
    lv_obj_t * ta = (lv_obj_t *)lv_event_get_user_data(e);

    // 获取被选中按钮的文本内容
    const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));

    // 如果按下的是退格键（BACKSPACE）
    if(strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) 
    {
        lv_textarea_del_char(ta); // 删除文本域中的最后一个字符
    }
    else if(strcmp(txt, LV_SYMBOL_NEW_LINE) == 0) 
    {
        // 如果按下的是回车键（ENTER），触发事件准备提交输入的手机号
        lv_event_send(ta, LV_EVENT_READY, NULL);

        // 获取文本域中的手机号
        const char * phone = lv_textarea_get_text(ta);

        // 检查手机号长度是否符合要求（这里假定4位为最小长度）
        if(strlen(phone) < 4)
        {
            // 创建一个消息框提示错误信息
            static const char * btns[] = {"OK", ""}; // 消息框的按钮
            lv_obj_t * mbox = lv_msgbox_create(NULL, "Error", "号码过短", btns, false); // 创建消息框
            lv_obj_center(mbox); // 将消息框置于屏幕中央

            // 为"OK"按钮注册事件回调，点击时关闭消息框
            lv_obj_t * ok_btn = lv_msgbox_get_btns(mbox); // 获取消息框的按钮对象
            lv_obj_add_event_cb(ok_btn, [](lv_event_t * e) 
            {
                // 获取消息框对象并关闭
                lv_obj_t * mbox = (lv_obj_t *)lv_event_get_user_data(e);
                lv_msgbox_close(mbox); // 关闭消息框
            }, LV_EVENT_CLICKED, mbox); // 使用 LV_EVENT_CLICKED 处理点击事件
        }
        else
        {
            // 如果手机号长度符合要求，创建并发送 JSON 格式数据到 MQTT 主题
            const char * phone = lv_textarea_get_text(ta);
            
            // 创建 JSON 对象，包含 boxName 和 phone 字段
            cJSON *root = cJSON_CreateObject();
            cJSON_AddStringToObject(root, "boxName", "zhangge");
            cJSON_AddStringToObject(root, "phone", phone);
            char * jsonString = cJSON_Print(root);

            // 发送 JSON 数据到 MQTT 主题 "woniuSms"
            mqttSendMessage("woniuSms", jsonString);

            // 释放 JSON 对象和字符串的内存
            cJSON_Delete(root);
            free(jsonString);
        }
    }
    else 
    {
        // 如果按下的是普通数字按钮，将其内容添加到文本域中
        lv_textarea_add_text(ta, txt);
    }
}

// 创建寄件页面
void put_package_page(lv_obj_t * parent)
{
    // 第一部分：创建顶部文字标签
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, "请输入手机号:"); // 设置标签内容
    // 标签对齐方式：顶部居中，距离顶部5像素
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 5);

    // 第二部分：创建文本域，用于输入手机号
    lv_obj_t * ta = lv_textarea_create(parent); // 创建文本域
    lv_textarea_set_one_line(ta, true); // 设置为单行模式
    // 文本域对齐方式：顶部居中，距离顶部55像素
    lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 55);

    // 设置文本域默认处于焦点状态，确保光标可见
    lv_obj_add_state(ta, LV_STATE_FOCUSED);

    // 第三部分：创建数字矩阵（数字键盘）
    static const char * btnm_map[] = {
        "1", "2", "3", "\n",
        "4", "5", "6", "\n",
        "7", "8", "9", "\n",
        LV_SYMBOL_BACKSPACE, "0", LV_SYMBOL_NEW_LINE, ""
    };

    lv_obj_t * btnm = lv_btnmatrix_create(parent); // 创建按钮矩阵
    // 设置按钮矩阵的字体
    lv_obj_set_style_text_font(btnm, &lv_font_montserrat_14, 0);
    // 设置按钮矩阵的大小为 300x160
    lv_obj_set_size(btnm, 300, 160);
    // 按钮矩阵对齐方式：底部居中，距离底部5像素
    lv_obj_align(btnm, LV_ALIGN_BOTTOM_MID, 0, -5);

    // 为按钮矩阵注册事件回调函数
    // 当按钮值改变时，触发 btnm_event_handler 函数
    // ta 作为用户数据传递，用于操作文本域
    lv_obj_add_event_cb(btnm, btnm_event_handler, LV_EVENT_VALUE_CHANGED, ta);

    // 禁用按钮矩阵的点击聚焦功能，确保文本域焦点不会因为按钮点击而丢失
    lv_obj_clear_flag(btnm, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    // 设置按钮矩阵的按钮内容映射（数字键、退格键、换行键）
    lv_btnmatrix_set_map(btnm, btnm_map);
}

````

````c
#include "put_package.h"
#include "MQTTControl.h"

// 定义数字矩阵（button matrix，类似键盘布局的按钮组）的事件处理函数，用于处理数字矩阵按钮点击等相关事件
// 该函数根据用户点击数字矩阵按钮的不同情况，对与之关联的文本域进行相应操作，比如添加字符、删除字符，
// 并且在用户按下回车键且输入内容满足一定条件时，进行相应的业务逻辑处理，如发送MQTT消息等
static void btnm_event_handler(lv_event_t * e)
{
    // 获取事件发生的源头对象，在这里就是数字矩阵（button matrix）本身，
    // 通过lv_event_get_target函数从事件结构体指针e中获取触发事件的目标对象指针
    lv_obj_t * obj = lv_event_get_target(e);
    // 获取传递过来的用户数据，在这里预先设置为指向文本域（textarea）的指针，
    // 这样在事件处理函数中就能获取到与之关联的文本域对象，进而操作文本域中的文本内容。
    // 数据是在注册事件时通过lv_event_get_user_data函数传递进来的
    lv_obj_t * ta = (lv_obj_t *)lv_event_get_user_data(e);

    // 获取数字矩阵（button matrix）中当前被选中按钮对应的文本内容，
    // lv_btnmatrix_get_selected_btn函数用于获取当前选中按钮的索引，
    // 然后通过lv_btnmatrix_get_btn_text函数根据索引获取对应的文本内容，
    // 文本内容可能是数字（如 "1"、"2" 等）、功能键符号（如退格键符号、回车键符号等）
    const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));

    // 判断获取到的按钮文本内容是否为退格键对应的符号（LV_SYMBOL_BACKSPACE），
    // 如果是，表示用户点击了退格键，需要在关联的文本域中删除一个字符
    if (strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) 
    {
        lv_textarea_del_char(ta);
    }
    else if (strcmp(txt, LV_SYMBOL_NEW_LINE) == 0) 
    {
        // 判断获取到的按钮文本内容是否为回车键对应的符号（LV_SYMBOL_NEW_LINE），
        // 如果是，表示用户点击了回车键，此时先触发一个LV_EVENT_READY事件（可能用于告知相关逻辑文本输入已完成等），
        // 然后获取文本域中的文本内容，将其视为手机号进行后续的合法性判断及相关业务处理
        lv_event_send(ta, LV_EVENT_READY, NULL);
        const char * phone = lv_textarea_get_text(ta);
        if (strlen(phone) < 4)
        {
            // 如果获取到的手机号文本长度小于4位，认为手机号格式不符合要求，创建一个消息框来提示用户输入的号码过短错误信息
            // 首先定义消息框上显示的按钮文本内容数组，这里只定义了一个 "OK" 按钮，用于用户确认关闭消息框
            static const char * btns[] = {"OK", ""}; // 消息框上的按钮
            // 使用lv_msgbox_create函数创建一个消息框对象，第一个参数为NULL表示消息框的父对象采用默认设置（通常会根据LVGL的默认布局规则显示），
            // 第二个参数 "Error" 是消息框的标题，用于提示用户这是一个错误提示框，第三个参数 "号码过短" 是消息框内显示的具体错误提示内容，
            // 第四个参数 btns 传入按钮文本内容数组，用于设置消息框上显示的按钮，最后一个参数 false 表示消息框不是模态的（即可以在不关闭它的情况下与其他界面元素交互，若为true则为模态，会阻塞其他操作直到关闭消息框）
            lv_obj_t * mbox = lv_msgbox_create(NULL, "Error", "号码过短", btns, false); // 创建消息框
            // 将创建好的消息框在屏幕上居中显示，使其处于比较显眼的位置，方便用户操作
            lv_obj_center(mbox); // 将消息框居中显示

            // 为消息框中的 "OK" 按钮添加事件回调函数，当用户点击 "OK" 按钮时，执行相应的关闭消息框操作
            lv_obj_t * ok_btn = lv_msgbox_get_btns(mbox); // 获取消息框的按钮，这里获取到的应该就是之前定义的 "OK" 按钮对象
            lv_obj_add_event_cb(ok_btn, [](lv_event_t * e) 
            {
                // 在事件回调函数内部，首先从事件结构体中获取传递过来的消息框对象指针（通过lv_event_get_user_data函数获取，在注册事件时传入的消息框对象）
                lv_obj_t * mbox = (lv_obj_t *)lv_event_get_user_data(e); // 获取消息框对象
                // 调用lv_msgbox_close函数关闭消息框，使消息框从屏幕上消失，完成提示用户后关闭的操作流程
                lv_msgbox_close(mbox); 
            }, LV_EVENT_CLICKED, mbox); // 使用 LV_EVENT_CLICKED 处理点击事件，并且将消息框对象指针 mbox 作为用户数据传递给事件回调函数，方便在回调函数中操作消息框
        }
        else
        {
            // 如果手机号文本长度大于等于4位，认为手机号格式在长度方面初步符合要求，接下来要发送JSON格式的数据给名为 "woniuSms" 的接收端（可能是MQTT主题对应的接收者等，具体取决于业务逻辑）
            const char* phone = lv_textarea_get_text(ta);

            // 使用cJSON库创建一个JSON对象，用于构建要发送的JSON数据结构，后续会向该对象中添加相应的键值对来表示具体的数据内容
            cJSON *root = cJSON_CreateObject();
            // 使用cJSON_AddStringToObject函数向JSON对象中添加一个字符串类型的键值对，键为 "boxName"，值为 "zhangge"，
            // 这里 "boxName" 可能代表包裹所属的名称等业务相关含义，具体由业务规则定义
            cJSON_AddStringToObject(root, "boxName", "zhangge");
            // 使用cJSON_AddStringToObject函数向JSON对象中添加一个字符串类型的键值对，键为 "phone"，值为从文本域获取到的手机号文本内容，
            // 这样就构建好了符合要求的JSON数据结构，包含了包裹相关信息和手机号信息
            cJSON_AddStringToObject(root, "phone", phone);
            // 使用cJSON_Print函数将构建好的JSON对象转换为字符串形式，以便能够通过网络等方式进行发送，
            // 转换后的字符串就是符合JSON格式规范的文本内容，例如 {"boxName":"zhangge","phone":"13260959680"}
            char* jsonString = cJSON_Print(root);
            // （以下代码目前被注释掉了，可能用于调试目的）先通过串口输出要发送的JSON字符串内容，方便查看发送的数据是否正确，在实际应用中可能会根据具体情况决定是否保留这一操作或者添加更多的日志记录功能
            // Serial.println(jsonString);
            // 调用mqttSendMessage函数（应该是在MQTTControl.h中定义的函数，用于发送MQTT消息），将JSON字符串发送到 "woniuSms" 对应的接收端，
            // 完成向服务器或其他接收者传递手机号及包裹相关信息的业务操作
            mqttSendMessage("woniuSms", jsonString);

            // 使用cJSON_Delete函数释放之前创建的JSON对象所占用的内存资源，避免内存泄漏，这是使用cJSON库时的良好编程习惯
            cJSON_Delete(root);
            // 使用free函数释放通过cJSON_Print函数转换JSON对象为字符串时动态分配的内存空间，确保内存的正确管理
            free(jsonString);
        }
    }
    else // 如果点击的按钮既不是退格键也不是回车键对应的符号，也就是点击了数字按钮（如 "1"、"2"、"3" 等），
    {
        // 将点击的数字按钮对应的文本内容添加到关联的文本域中，实现类似在文本域中输入数字的效果
        lv_textarea_add_text(ta, txt);
    }
}

// 函数功能：创建“寄件”页面相关的UI元素及设置相应的事件处理逻辑，
// 在传入的父对象（parent，应该是代表某个选项卡页面或者其他容器对象）上构建包含提示标签、文本域和数字矩阵按钮组的布局，并关联相应的事件处理函数
void put_package_page(lv_obj_t * parent)
{
    // 第一块区域：创建一个标签（label）对象，用于在页面上显示提示文字，
    // 该标签的父对象是通过参数传入的parent，意味着它会显示在parent所代表的页面区域内
    lv_obj_t *label = lv_label_create(parent);
    // 设置标签显示的文本内容为 "请输入手机号:"，用于提示用户操作，告知用户在此处需要输入手机号信息
    lv_label_set_text(label,"请输入手机号:");
    // 将标签在父对象内进行对齐，LV_ALIGN_TOP_MID表示垂直方向顶部居中对齐，
    // 后面的0和5表示在水平方向无偏移，垂直方向距离顶部边界有5个像素的偏移量，以达到合适的显示位置
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 5);

    // 第二块区域：创建一个文本域（textarea）对象，作为用户输入手机号的输入框，
    // 它的父对象同样是传入的parent，即会显示在对应的页面区域内
    lv_obj_t * ta = lv_textarea_create(parent); // textarea
    // 设置文本域为单行模式，意味着用户输入的文本只能在一行内显示，通常用于输入简短的内容，比如手机号这种情况，方便格式统一和后续处理
    lv_textarea_set_one_line(ta, true);
    // 将文本域在父对象内进行对齐，LV_ALIGN_TOP_MID表示垂直方向顶部居中对齐，
    // 后面的0和55表示在水平方向无偏移，垂直方向距离顶部边界有55个像素的偏移量，以确定其在页面上的合适显示位置
    lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 55);

    // （以下代码目前被注释掉了）原本计划是给文本域添加一个事件回调函数，当文本域触发LV_EVENT_READY事件时（可能是输入完成等情况触发），
    // 会调用textarea_event_handler函数进行相应处理，但目前暂时未启用该逻辑，可能后续会根据需求重新启用或修改此处逻辑
    // lv_obj_add_event_cb(ta, textarea_event_handler, LV_EVENT_READY, ta);

    // 给文本域添加LV_STATE_FOCUSED状态，确保文本域获取焦点，这样光标会显示在文本域内，方便用户直接输入内容，
    // 提升用户交互的直观性和便捷性
    lv_obj_add_state(ta, LV_STATE_FOCUSED); /*To be sure the cursor is visible*/

    // 第三块区域：创建一个数字矩阵（button matrix）对象，用于模拟数字键盘布局，方便用户输入手机号，
    // 它的父对象也是传入的parent，会显示在对应的页面区域内
    static const char * btnm_map[] = {"1", "2", "3", "\n",
                                      "4", "5", "6", "\n",
                                      "7", "8", "9", "\n",
                                      LV_SYMBOL_BACKSPACE, "0", LV_SYMBOL_NEW_LINE, ""
                                     };
    lv_obj_t * btnm = lv_btnmatrix_create(parent);
    // 设置数字矩阵中按钮文本显示所使用的字体为lv_font_montserrat_14，通过指定字体来控制按钮上文字的外观样式，
    // 使其符合整体UI设计风格，最后一个参数0表示应用该字体样式到所有状态（LVGL支持不同状态下设置不同样式）
    lv_obj_set_style_text_font(btnm,&lv_font_montserrat_14,0);
    // 设置数字矩阵对象的大小，这里将其宽度设置为300（单位由LVGL库相关设置决定，可能是像素等），高度设置为160，
    // 以确定其在页面上的显示尺寸，使其布局更加合理、美观
    lv_obj_set_size(btnm, 300, 160);
    // 将数字矩阵在父对象内进行对齐，LV_ALIGN_BOTTOM_MID表示垂直方向底部居中对齐，
    // 后面的0和 -5表示在水平方向无偏移，垂直方向距离底部边界有 -5个像素的偏移量（也就是向上偏移5个像素），以达到合适的显示位置
    lv_obj_align(btnm, LV_ALIGN_BOTTOM_MID, 0, -5);
    // 给数字矩阵添加事件回调函数，当数字矩阵中的按钮发生值改变事件（LV_EVENT_VALUE_CHANGED，即按钮被点击等操作导致值改变时），
    // 会调用btnm_event_handler函数进行处理，并且将文本域对象指针（ta）作为用户数据传递给事件处理函数，
    // 方便在事件处理函数中操作与之关联的文本域内容
    lv_obj_add_event_cb(btnm, btnm_event_handler, LV_EVENT_VALUE_CHANGED, ta);

    // 清除数字矩阵的LV_OBJ_FLAG_CLICK_FOCUSABLE标志位，这样在点击数字矩阵按钮时，不会使文本域失去焦点，
    // 保证用户可以连续输入手机号，无需重复点击文本域获取焦点，提升用户输入体验
    lv_obj_clear_flag(btnm, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
    // 设置数字矩阵的按钮映射关系，通过传入预先定义好的btnm_map数组，确定每个按钮位置对应的文本内容，
    // 从而构建出符合要求的数字键盘布局（包含数字按钮和功能键按钮等）
    lv_btnmatrix_set_map(btnm, btnm_map);
}
````

### 弹框

````c
#include "lvgl/lvgl.h"

lv_obj_t * mbox = NULL; // 全局变量用于保存消息框对象

// 弹出提示框的函数
void create_msgbox(const char * title, const char * message) {
    // 检查是否已有消息框，若有则关闭
    if (mbox != NULL) {
        lv_msgbox_close(mbox); // 关闭当前消息框
    }

    // 按钮文本
    static const char * btns[] = {"OK", ""}; 

    // 创建新的消息框
    mbox = lv_msgbox_create(NULL, title, message, btns, false);
    lv_obj_center(mbox); // 将消息框居中显示

    // 为"OK"按钮添加事件回调，点击时关闭消息框
    lv_obj_t * ok_btn = lv_msgbox_get_btns(mbox); // 获取消息框的按钮对象
    lv_obj_add_event_cb(ok_btn, [](lv_event_t * e) {
        lv_obj_t * mbox = (lv_obj_t *)lv_event_get_user_data(e); // 获取消息框对象
        lv_msgbox_close(mbox); // 关闭消息框
    }, LV_EVENT_CLICKED, mbox); // 使用 LV_EVENT_CLICKED 事件处理
}

// 模拟一个条件函数，根据条件弹出提示框
void check_condition_and_show_msgbox() {
    // 假设这里有一个条件，满足时显示提示框
    bool condition_met = true; // 可以根据实际条件修改

    if (condition_met) {
        create_msgbox("Error", "Something went wrong!"); // 弹出提示框
    }
}

int main(void) {
    // 初始化 LVGL
    lv_init();

    // 假设已经初始化了显示缓冲区和显示驱动（如 LVGL 驱动配置等）

    // 检查条件并弹出提示框
    check_condition_and_show_msgbox();

    // 进入 LVGL 的任务处理循环
    while (1) {
        lv_task_handler();
        usleep(5000); // 或其他延时函数，确保LVGL任务循环能够执行
    }

    return 0;
}

````



````c
#include "lvgl/lvgl.h"
#include <stdio.h>

// 用于模拟满足条件的变量，你可以根据实际情况替换成真正的判断条件
static bool should_show_box = false; 

// 消息框上的按钮文本
static const char * btns[] = {"OK", ""}; 

// 消息框事件回调函数，用于处理按钮点击关闭消息框
static void msgbox_event_cb(lv_event_t * e)
{
    lv_obj_t * mbox = (lv_obj_t *)lv_event_get_target(e);
    lv_res_t res = lv_msgbox_get_active_btn(mbox);
    if (res == 0) {  // 0对应第一个按钮，也就是"OK"按钮
        lv_msgbox_close(mbox);
    }
}

int main(void)
{
    // 初始化LVGL，这里省略具体的初始化硬件相关代码，不同平台初始化方式不同
    lv_init();

    // 创建一个屏幕对象（假设这是基础的显示区域）
    lv_obj_t * scr = lv_obj_create(NULL);
    lv_disp_load_scr(scr);

    // 模拟业务逻辑，这里简单地通过改变should_show_box的值来决定是否弹出提示框
    // 实际应用中可以替换成真实的判断条件，比如输入数据不符合要求等情况
    should_show_box = true; 

    if (should_show_box) {
        // 创建消息框
        lv_obj_t * mbox = lv_msgbox_create(scr, "提示", "这是一个提示信息示例，点击OK关闭。", btns, false);
        lv_obj_center(mbox);

        // 为消息框添加事件回调，处理按钮点击事件
        lv_obj_add_event_cb(mbox, msgbox_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    }

    // LVGL主循环，用于持续更新显示等操作
    while(1) {
        lv_task_handler();
        // 可以在这里添加其他业务逻辑代码，比如根据实际情况更新should_show_box的值等
    }

    return 0;
}
````



## 编译src下的其他文件

在platfromio.ini下面

```
build_flags = -I src -I src/ui
```























