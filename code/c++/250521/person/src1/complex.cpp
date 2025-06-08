/***************************************************
# File Name:    加法操作符重载.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月21日 星期三 15时51分21秒
****************************************************/

#include "complex.h"

Complex::Complex(){
	m_real = 0;
	m_image = 0;
}

Complex::Complex(double real){
	m_real = real;
	m_image = 0;
}

Complex::Complex(double real, double image){
	m_real = real;
	m_image = image;
}

Complex Complex::operator+(const Complex &A)const{
	Complex B;
	B.m_real = this->m_real + A.m_real;
	B.m_image = this->m_image + A.m_image;

	cout << "internal func" << endl;
	return B;
}
#if 0
Complex operator+(const Complex &A, const Complex &B){
	Complex C;
	C.m_real = B.m_real + A.m_real;
	C.m_image = B.m_image + A.m_image;
	
	cout << "global func" << endl;
	return C;
}
#endif
void Complex::print() const{
	cout << m_real << " + " << m_image << "i" << endl;
}

