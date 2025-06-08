#include <Arduino.h>
#include "httpControl.h"
#include "cJSON.h"

//通过url获取网页内容
String httpGet(String url)
{
  HTTPClient http;      //初始化http客户端（浏览器）

  //输入网址
  http.begin(url);//HTTP

  //发送请求
  int httpCode = http.GET();
  String payload = "";
  if(httpCode > 0) {
      if(httpCode == HTTP_CODE_OK) {
          payload = http.getString();
      }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();

  return payload;
}

void getWeather(String cityName)
{
  //String payload = httpGet("https://api.seniverse.com/v3/weather/now.json?key=SF0xkKxvs0SrlFT-t&location=beijing&language=zh-Hans&unit=c");
  String url ="https://api.seniverse.com/v3/weather/now.json?key=SF0xkKxvs0SrlFT-t&location="+cityName+"&language=zh-Hans&unit=c";
  //获取天气内容
  String content = httpGet(url);
  //解析获得的天气内容，String转换成char *,使用content.c_str()方法就可以转换
  cJSON *root = cJSON_Parse(content.c_str());
  if(root == NULL){
    Serial.printf("root Error");//解析失败
  }
  cJSON *results = cJSON_GetObjectItem(root,"results");
  cJSON *result = cJSON_GetArrayItem(results,0);
  cJSON *location = cJSON_GetObjectItem(result,"location");
  cJSON *name = cJSON_GetObjectItem(location,"name");
  cJSON *now = cJSON_GetObjectItem(result,"now");
  cJSON *text = cJSON_GetObjectItem(now,"text");
  cJSON *temperature = cJSON_GetObjectItem(now,"temperature");
  cJSON *last_update = cJSON_GetObjectItem(result,"last_update");

  Serial.printf("城市：%s",name->valuestring);
  Serial.printf("天气：%s",text->valuestring);
  Serial.printf("温度：%s",temperature->valuestring);
  Serial.printf("最近更新时间：%s",last_update->valuestring);
}


