#include "getPackagePage.h"
#include "MqttController.h"
#include "cJSON.h"
#include "HttpController.h"
#include <Arduino.h>

//让按键矩阵处理函数
static void btnm1_event_handler(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);//获取这个时间的来源对象，也就是按键矩阵控件
    lv_obj_t * ta = (lv_obj_t *)lv_event_get_user_data(e);//获取用户数据，也就是文本区域控件
    
    //从矩形矩阵上获取用户点击到的字符
    const char * txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));
    
    if(strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) 
    {
        lv_textarea_del_char(ta);//如果点击删除键，从文本区域中删除最后一个字符
    }
    else if(strcmp(txt, LV_SYMBOL_NEW_LINE) == 0) 
    {
        //
        const char * yzm = lv_textarea_get_text(ta);
        //清除文本框中用户输入的验证码      
        lv_textarea_set_text(ta,"");
        //
        String responseString = httpGet("http://120.26.64.89:8080/box/getPackage/zhudongdong/"+String(yzm));
        Serial.println(responseString);

    //     //获取MQTT响应信息，并解析响应的JSON
       cJSON *root = cJSON_Parse(responseString.c_str());
       cJSON *boxId = cJSON_GetObjectItem(root,"boxId");
       if(boxId->valueint < 0)
       {
            Serial.println("验证码错误");
       }else
       {
             Serial.println("验证码正确");
       }
       cJSON *boxName = cJSON_GetObjectItem(root,"boxName");
       cJSON *phone = cJSON_GetObjectItem(root,"phone");
       cJSON *putDate = cJSON_GetObjectItem(root,"putDate");

    }
    else 
    {
        lv_textarea_add_text(ta, txt);
    }

}

void createGetPackagePage(lv_obj_t *parent)
{
    //创建一个提示标签，用于提示输入电话号码
    lv_obj_t * label = lv_label_create(parent);
    lv_label_set_text(label,"输入验证码");
    lv_obj_align(label,LV_ALIGN_TOP_MID , 0 , 5);

    //创建一个手机号的输入框
    lv_obj_t * ta = lv_textarea_create(parent);//创建一个文本输入区域
    lv_textarea_set_one_line(ta, true);//让输入的内容在一行上，不换行
    lv_obj_align(ta, LV_ALIGN_TOP_MID, 0, 50);//位置距离顶部55个像素
    //给这个输入框，注册了一个事件，如果LV_ENWENT_READY事件发声，就回去调用textarea_event_handler处理函数
    // lv_obj_add_event_cb(ta, textarea_event_handler, LV_EVENT_READY, ta);
    //
    lv_obj_add_state(ta, LV_STATE_FOCUSED); /*保证光标能够被看到*/
    lv_textarea_set_placeholder_text(ta,"请输入取件码");


    static const char * btnm_map[] = {"1", "2", "3", "\n",
                                      "4", "5", "6", "\n",
                                      "7", "8", "9", "\n",
                                      LV_SYMBOL_BACKSPACE, "0", LV_SYMBOL_NEW_LINE, ""
                                     };
    //创建一个矩形矩阵
    lv_obj_t * btnm = lv_btnmatrix_create(parent);
    //把键盘矩阵的字体设置为原生字体
    lv_obj_set_style_text_font(btnm, &lv_font_montserrat_14,0);
    //设置矩阵大小
    lv_obj_set_size(btnm, 300, 160);
    //设置矩阵位置
    lv_obj_align(btnm, LV_ALIGN_BOTTOM_MID, 0, -5);
    //设置矩阵触发时机，以及要处理的事件
    //参数分别是：控件对象，处理函数，
    lv_obj_add_event_cb(btnm, btnm1_event_handler, LV_EVENT_VALUE_CHANGED, ta);
    //点击输入数字的时候，让光标一直在输入框里面
    lv_obj_clear_flag(btnm, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
    lv_btnmatrix_set_map(btnm, btnm_map);//让矩形矩阵，使用上面的数组
}