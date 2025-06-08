#include <Arduino.h>
#include "HttpController.h"
#include "cJSON.h"
//通过 url 获取网页内容
String httpGet(String url)
{
    HTTPClient http;//声明一个http客户端对象
    //输入了网址
    http.begin(url); //HTTP

    //发送请求
    int httpCode = http.GET();
    String payload = "";
    if(httpCode > 0) {
        // file found at server
        if(httpCode == HTTP_CODE_OK) {
            payload = http.getString();
        }
    } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();

    return payload;;
}

void getWeather(String cityName)
{
    String url = "https://api.seniverse.com/v3/weather/now.json?key=Sw3IohTeKvAGUbz1r&location="+cityName+"&language=zh-Hans&unit=c";
    //获取的天气的内容
    String content = httpGet(url);
    //解析内容,String转换成char* 使用content.c_str()方法就可以了
    cJSON *root= cJSON_Parse(content.c_str());
    if(root==NULL){
        Serial.println("Error");//解析失败
    }else{
        cJSON *results = cJSON_GetObjectItem(root,"results");
        cJSON *result = cJSON_GetArrayItem(results,0);
        cJSON *location = cJSON_GetObjectItem(result,"location");
        cJSON *name = cJSON_GetObjectItem(location,"name");
        cJSON *now = cJSON_GetObjectItem(result,"now");
        cJSON *text = cJSON_GetObjectItem(now,"text");
        cJSON *temperature = cJSON_GetObjectItem(now,"temperature");
        cJSON *last_update = cJSON_GetObjectItem(result,"last_update");

        Serial.printf("城市：%s\r\n",name->valuestring);
        Serial.printf("天气：%s\r\n",text->valuestring);
        Serial.printf("温度：%s\r\n",temperature->valuestring);
        Serial.printf("最近更新时间：%s\r\n",last_update->valuestring);
    }

}

