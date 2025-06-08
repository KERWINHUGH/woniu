/***************************************************
# File Name:    继承后子类大小.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月22日 星期四 12时14分15秒
****************************************************/

#include <iostream>
using namespace std;

class A{
public:
	int m_x;
};

class B : public A{
public:
	int m_y;
};

class C : public B{
public:
	int m_z;
};

int main(int argc, char *argv[]) {
	cout << "A size = " << sizeof(A) << endl;
	cout << "B size = " << sizeof(B) << endl;
	cout << "C size = " << sizeof(C) << endl;
    return 0;
}
