#ifndef _HTTP_CONTROLLER_H
#define _HTTP_CONTROLLER_H
#include <HTTPClient.h>

//通过 url 获取网页内容
String httpGet(String url);
void getWeather(String cityName);

#endif