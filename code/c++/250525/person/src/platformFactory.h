/***************************************************
# File Name:    shapeFamily.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月25日 星期日 16时20分11秒
****************************************************/
#ifndef _PLATFORMFACTORY_H
#define _PLATFORMFACTORY_H

#include "shapeFamily.h"

class PlatformFactory {
public:
	virtual Circle* createCircle() const = 0;
	virtual Rectangle* createRectangle() const = 0;
	virtual ~PlatformFactory(){}
};


class WindowsFactory : public PlatformFactory{
public:
	Circle* createCircle() const override;
	Rectangle* createRectangle() const override;
};

class LinuxFactory : public PlatformFactory{
public:
	Circle * createCircle() const override;
	Rectangle * createRectangle() const override;
}; 

#endif
