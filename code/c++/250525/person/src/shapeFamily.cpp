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
using namespace std;


void Rectangle::draw() const {
	cout << "Drawing a Rectangle" << endl;	
}

void Circle::draw() const {
	cout << "Drawing a Circle" << endl;		
}

void ModernCircle::draw() const {
	cout << "Drawing a Modern Circle" << endl;	
}

void ModernRectangle::draw() const {
	cout << "Drawing a Modern Rectangle" << endl;	
}

void ClassicCircle::draw() const {
	cout << "Drawing a Classic Circle" << endl;	
}

void ClassicRectangle::draw() const {
	cout << "Drawing a Classic Rectangle" << endl;	
}

void RetroCircle::draw() const {
	cout << "Drawing a Retro Circle" << endl;	
}

void RetroRectangle::draw() const {
	cout << "Drawing a Retro Rectangle" << endl;	
}

void WindowsCircle::draw() const {
	cout << "Drawing a Windows Circle" << endl;	
}

void WindowsRectangle::draw() const {
	cout << "Drawing a Windows Rectangle" << endl;	
}

void LinuxCircle::draw() const {
	cout << "Drawing a Linux Circle" << endl;	
}

void LinuxRectangle::draw() const {
	cout << "Drawing a Linux Rectangle" << endl;	
}



