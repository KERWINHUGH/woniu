/***************************************************
# File Name:    ExceptionHandler.h
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月29日 星期四 19时16分17秒
****************************************************/
#ifndef _EXCEPTIONHANDLE_H
#define _EXCEPTIONHANDLE_H
#include <exception>

class ExceptionHandler {
public:
static void handleException(const std::exception& e);
static void logException(const std::exception& e);
};

#endif
