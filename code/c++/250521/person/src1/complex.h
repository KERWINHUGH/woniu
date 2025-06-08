/***************************************************
# File Name:    加法操作符重载.h
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月21日 星期三 15时56分53秒
****************************************************/
#ifndef _COMPLEX_H
#define _COMPLEX_H

#include <iostream>
using namespace std;


class Complex{
public:
//	friend Complex operator+(const Complex &A, const Complex &B);
	
	Complex();
	Complex(double real);
	Complex(double real,double image);

	Complex operator+(const Complex &A) const;

	void print() const;
	~Complex() = default;
private:
	double m_real;
	double m_image;
};

//Complex operator+(const Complex &A, const Complex &B);


#endif
