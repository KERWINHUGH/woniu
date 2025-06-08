/***************************************************
# File Name:    shapeFamily.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月25日 星期日 16时20分11秒
****************************************************/

#include <iostream>
#include <cstring>
#include "shapeFamily.h"
#include "GUIFactory.h"
using namespace std;


Circle* ModernFactory::createCircle() const{
	Circle * c = new ModernCircle;
	return c;
}
Rectangle* ModernFactory::createRectangle() const {
	Rectangle * r = new ModernRectangle;
	return r;
}

Circle * ClassicFactory::createCircle() const {
	Circle * c = new ClassicCircle;
	return c;
}
Rectangle * ClassicFactory::createRectangle() const {
	Rectangle * r = new ClassicRectangle;
	return r;
}

Circle * RetroFactory::createCircle() const {
	Circle * c = new RetroCircle;
	return c;
}
Rectangle * RetroFactory::createRectangle() const {
	Rectangle * r = new RetroRectangle;
	return r;
}



