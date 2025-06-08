/***************************************************
# File Name:    shapeFamily.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月25日 星期日 16时20分11秒
****************************************************/

#include <iostream>
#include <cstring>
using namespace std;

class shape{
public:
	//纯虚方法 void draw() const ：定义绘制行为
	virtual void draw() const = 0;
	virtual ~shape(){}
};

class Rectangle : public shape{
public:
		void draw() const override{
		cout << "Drawing a Rectangle" << endl;	
	}
};

class Circle : public shape{
public:
	void draw() const override{
		cout << "Drawing a Circle" << endl;	
	}
};

class GUIFactory {
public:
	virtual Circle* createCircle() const = 0;
	virtual Rectangle* createRectangle() const = 0;
	virtual ~GUIFactory(){}
};

class ModernCircle : public Circle{	
public:
	void draw() const override{
		cout << "Drawing a Modern Circle" << endl;	
	}
};

class ModernRectangle : public Rectangle{	
public:
	void draw() const override{
		cout << "Drawing a Modern Rectangle" << endl;	
	}
};

class ClassicCircle : public Circle{	
public:
	void draw() const override{
		cout << "Drawing a Classic Circle" << endl;	
	}
};

class ClassicRectangle : public Rectangle{	
public:
	void draw() const override{
		cout << "Drawing a Classic Rectangle" << endl;	
	}
};

class RetroCircle : public Circle{	
public:
	void draw() const override{
		cout << "Drawing a Retro Circle" << endl;	
	}
};

class RetroRectangle : public Rectangle{	
public:
	void draw() const override{
		cout << "Drawing a Retro Rectangle" << endl;	
	}
};

class ModernFactory : public GUIFactory{
public:
#if 0
	void draw() const{	
		cout << "Drawing Modern shape" << endl;
	}
#endif
	Circle* createCircle() const override{
		Circle * c = new ModernCircle;
		//cout << "Drawing Modern Circle" << endl;
		return c;
	}
	Rectangle* createRectangle() const override{
		Rectangle * r = new ModernRectangle;
		//cout << "Drawing Modern Rectangle" << endl;
		return r;
	}
};

class ClassicFactory : public GUIFactory{
public:
#if 0
	void draw() const{	
		cout << "Drawing Classic shape" << endl;
	}
#endif
	Circle * createCircle() const override{
		Circle * c = new ClassicCircle;
		//cout << "Drawing Classic Circle" << endl;
		return c;
	}
	Rectangle * createRectangle() const override{
		Rectangle * r = new ClassicRectangle;
		//cout << "Drawing Classic Rectangle" << endl;
		return r;
	}
}; 

class RetroFactory : public GUIFactory{
public:
	Circle * createCircle() const override{
		Circle * c = new RetroCircle;
		//cout << "Drawing Classic Circle" << endl;
		return c;
	}
	Rectangle * createRectangle() const override{
		Rectangle * r = new RetroRectangle;
		//cout << "Drawing Classic Rectangle" << endl;
		return r;
	}
};

#if 0
void test() {
	GUIFactory* factory = new ModernFactory();
	Circle* circle = factory->createCircle();
	assert(strcmp(circle->draw() , "Drawing Modern Circle") == 0);
	delete circle;
	delete factory;
}
#endif


int main(int argc, char *argv[]) {

//	test();
	
	GUIFactory* factory = new RetroFactory();
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
