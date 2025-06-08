/***************************************************
# File Name:    shapeFamily.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月25日 星期日 16时20分11秒
****************************************************/

#include <iostream>
#include <cstring>
#include "shapeFamily.h"
#include "platformFactory.h"
using namespace std;


Circle* WindowsFactory::createCircle() const{
	Circle * c = new WindowsCircle;
	return c;
}
Rectangle* WindowsFactory::createRectangle() const {
	Rectangle * r = new WindowsRectangle;
	return r;
}

Circle * LinuxFactory::createCircle() const {
	Circle * c = new LinuxCircle;
	return c;
}
Rectangle * LinuxFactory::createRectangle() const {
	Rectangle * r = new LinuxRectangle;
	return r;
}


