/***************************************************
# File Name:    函数重载.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月15日 星期四 17时28分51秒
****************************************************/

#include <iostream>
using namespace std;

/*************************************************
编写多个 calculate 函数，支持两个整数、两个浮点数、
一个整数和一个浮点数的加法操作（函数需要重载）。
**************************************************/

int calculate(int a ,int b){
	return a+b;
}

double calculate(double a ,double b){
	return a+b;
}

int calculate(int a ,double b){
	return a+b;
}

int main(int argc, char *argv[]) {
	int c = calculate(1,1);
	cout<<c<<endl;

	double d = calculate(1.5,3.6);
	cout<<d<<endl;
	
	double e = calculate(1,1.5);
	cout<<e<<endl;
    return 0;
}
