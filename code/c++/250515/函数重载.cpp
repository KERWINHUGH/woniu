/***************************************************
# File Name:    函数重载.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月15日 星期四 14时27分19秒
****************************************************/

#include <iostream>
using namespace std;

namespace A{
	void func(){
		cout << "This is func" <<endl;
	}
}

void func(){
	cout<< "This is func\n"<< endl;    
}

#if 0
//这里这么写会报错
int func(){
	cout << "This is func with return value!\n" << endl;
}
#endif


void func(int x){
	cout << "This is func ,x="<< x << endl;
}

//如果这么写，可以另一个参数的重载函数在调用的时候产生歧义
void func(int x ,int y = 22){
	cout << "This is func with 2 params x ="<< x << endl;
	cout << "This is func with 2 params y ="<< y << endl;
}

void func(double x){
	cout << "This is func with double value!" <<x << endl;
}

int main(int argc, char *argv[]) {
    func();
	func(10,20);
//	func(201);
	func(1.9);
    return 0;
}
