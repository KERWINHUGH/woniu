/***************************************************
# File Name:    shapeFamily.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月25日 星期日 16时20分11秒
****************************************************/
#ifndef _SHAPEFAMILY_H
#define _SHAPEFAMILY_H

class shape{
public:
	//纯虚方法 void draw() const ：定义绘制行为
	virtual void draw() const = 0;
	virtual ~shape(){}
};

class Rectangle : public shape{
public:
	void draw() const override;
};

class Circle : public shape{
public:
	void draw() const override;
};

class ModernCircle : public Circle{	
public:
	void draw() const override;
};

class ModernRectangle : public Rectangle{	
public:
	void draw() const override;
};

class ClassicCircle : public Circle{	
public:
	void draw() const override;
};

class ClassicRectangle : public Rectangle{	
public:
	void draw() const override;
};

class RetroCircle : public Circle{	
public:
	void draw() const override;
};

class RetroRectangle : public Rectangle{	
public:
	void draw() const override;
};

class WindowsCircle : public Circle{	
public:
	void draw() const override;
};

class WindowsRectangle : public Rectangle{	
public:
	void draw() const override;
};

class LinuxCircle : public Circle{	
public:
	void draw() const override;
};

class LinuxRectangle : public Rectangle{	
public:
	void draw() const override;
};

#endif
