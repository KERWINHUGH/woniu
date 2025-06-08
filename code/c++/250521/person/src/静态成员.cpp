/***************************************************
# File Name:    静态成员.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月21日 星期三 10时51分02秒
:****************************************************/

#include <iostream>
using namespace std;

class point {
public:
	//void init(){}
	//static void output(){}
	
	//在类的静态成员函数中使用类的非静态成员
	//void init(){}
	//static void output(){
	//静态成员函数属于整个类，在类实例化对象之前就已经分配空间类，而类的非静态成员必须在类实例化对象后才会分配空间。使用就会出错，就好比没有声明一个变量却提前使用它一样。
		//cout << "m_x =" << m_x << endl;	//定义时使用就会报错
	//}
	
	//在类的非静态成员函数中使用类的静态成员
	void init(){
		output();
	}
	static void output(){}
private:
	int m_x;
};


int main(int argc, char *argv[]) {
	//通过类名调用静态成员函数和非静态成员函数
	//	point::init();	//编译出错
	point::output();

	//通过类的对象调用静态成员函数和非静态成员函数
	point pt;
	pt.init();
	pt.output();

	//在类的静态成员函数中使用类的非静态成员，静态成员函数体中使用时报错
	point pt1;
	pt.output();

	//在类的非静态成员函数中使用类的静态成员
	point pt2;
	pt.output();

    return 0;
}
