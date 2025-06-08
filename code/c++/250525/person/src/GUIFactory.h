/***************************************************
# File Name:    shapeFamily.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月25日 星期日 16时20分11秒
****************************************************/
#ifndef _GUIFACTORY_H
#define _GUIFACTORY_H

#include "shapeFamily.h"

class GUIFactory {
public:
	virtual Circle* createCircle() const = 0;
	virtual Rectangle* createRectangle() const = 0;
	virtual ~GUIFactory(){}
};


class ModernFactory : public GUIFactory{
public:
	Circle* createCircle() const override;
	Rectangle* createRectangle() const override;
};

class ClassicFactory : public GUIFactory{
public:
	Circle * createCircle() const override;
	Rectangle * createRectangle() const override;
}; 

class RetroFactory : public GUIFactory{
public:
	Circle * createCircle() const override;
	Rectangle * createRectangle() const override;
};

#endif
