/***************************************************
# File Name:    main.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月21日 星期三 15时56分40秒
****************************************************/

#include <iostream>
#include "complex.h"
using namespace std;

int main(int argc, char *argv[]) {
	Complex c1;
	Complex c2(1);
	Complex c3(1.4,2.1);
	Complex c4(9.8,6.6);
	//使用类内成员函数重载操作符
	Complex c5 = c3 + c4;
	c5.print();
	
	//使用全局函数重载操作符
	//	Complex c6 = operator+(c3,c4);
	//	c6.print();
    return 0;
}
