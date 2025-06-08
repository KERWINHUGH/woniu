/***************************************************
# File Name:    多态.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月23日 星期五 14时40分23秒
****************************************************/

#include <iostream>
using namespace std;

#define PI 3.14

class shape{
public:
	virtual double getarea() = 0;	//抽象基类
};

class rectangle : public shape{
private:
	double len;
	double wide;
public:
	rectangle(double length , double width){
		len = length;
		wide = width;
	}
	double getarea(){
		cout << "rectangle area = " << endl;
		return len*wide;
	}
};

class circle : public shape{
private:
	double r;
public:
	circle(double ri){
		r = ri;
	}
	double getarea () override{
		cout << "circle area = " << endl;
		return PI * r *r;
	}
};

