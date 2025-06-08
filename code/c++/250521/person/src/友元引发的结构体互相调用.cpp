/***************************************************
# File Name:    友元引发的结构体互相调用.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月21日 星期三 14时28分29秒
****************************************************/

#include <iostream>
using namespace std;

class Tset;

class Test2{
public:
	void func3();
};

class Test{
public:
	friend void func1();
	friend void Test2::func3();
private:
	int m_x;
	int m_y;
};

void Test2::func3(){
	cout << "func3" << endl;
	
	Test t;
	t.m_x = 10;
	t.m_y = 20;

	cout << t.m_x << endl;
	cout << t.m_y << endl;
}

void func(){

		cout << "func" << endl;
		
		Test t;
}

void func1(){

		cout << "func1" << endl;
		
		Test t;
		t.m_x = 10;
		t.m_y = 20;

		cout << t.m_x << endl;
		cout << t.m_y << endl;
}

int main(int argc, char *argv[]) {
	func1();
    return 0;
}
