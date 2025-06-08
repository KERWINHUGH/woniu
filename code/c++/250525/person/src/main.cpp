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
#include "platformFactory.h"
#include "assert.h"
using namespace std;

#if 1
void test() {
	GUIFactory* factory = new ModernFactory();
	Circle* circle = factory->createCircle();
//	assert(circle->draw() == "Drawing Modern Circle");
	delete circle;
	delete factory;
}
#endif

int main(int argc, char *argv[]) {

	test();
	
	PlatformFactory* factory = new WindowsFactory();
	Circle* circle = factory->createCircle();
	Rectangle* rect = factory->createRectangle();
	circle->draw(); 	// 输出 "Drawing Modern Circle"
	rect->draw(); 	// 输出 "Drawing Modern Circle"
	// 必须手动释放资源
	delete circle;
	delete rect;
	delete factory;
    return 0;
}
