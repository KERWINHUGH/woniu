#include "ScreenControl.h"


/******************************************************
 * 硬件初始化（显示屏、触摸屏的对象）
 * 定义显示屏的宽度、高度
 ******************************************************/
/*Change to your screen resolution*/
static const uint16_t screenWidth  = 480;// 定义显示屏的宽度
static const uint16_t screenHeight = 320;// 定义显示屏的高度

//建立一个显示屏对象
TFT_eSPI tft = TFT_eSPI(screenWidth,screenHeight);       // Invoke custom library
//建立一个触摸屏的对象
TAMC_GT911 tp = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, screenWidth, screenHeight);

/***********************************
 * LVGL的初始化(定义一个绘图缓冲区)
 **********************************/
static lv_disp_draw_buf_t draw_buf;//定义一个缓冲区结构体
static lv_color_t buf[ screenWidth * screenHeight / 10 ];//定义一个



/* Display flushing显示时的回调函数 */
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

/*Read the touchpad触摸屏的回调函数*/
void my_touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data )
{
    tp.read();
    if( !tp.isTouched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        for (int i=0; i<tp.touches; i++){
            data->point.x = tp.points[i].x;
            data->point.y = tp.points[i].y; 
        }
    }
}


void Scree_Init(void)
{
  //显示屏的初始化
  tft.begin();
  tft.setRotation(3);

  //触摸屏的初始化
  tp.begin();
  tp.setRotation(ROTATION_LEFT);

  //LVGL的初始化
  lv_init();

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
}

void Scree_Loop(void)
{
  //维持LVGL刷新，flush冲刷
  lv_timer_handler();
}