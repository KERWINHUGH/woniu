/***************************************************
# File Name:    继承中的析构函数.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月22日 星期四 12时09分15秒
****************************************************/

#include <iostream>
using namespace std;

class A{
public:
	A(){
		cout << "A " <<endl;
	}
	~A(){
		cout << "~A"  <<endl;
	}
};

class B : public A{
public:
	B(){
		cout << "B " <<endl;
	}
	~B(){
		cout << "~B"  <<endl;
	}
};

int main(int argc, char *argv[]) {
	B b;
    return 0;
}
