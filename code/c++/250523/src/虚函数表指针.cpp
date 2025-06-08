/***************************************************
# File Name:    虚函数表指针.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月23日 星期五 11时51分03秒
****************************************************/

#include <iostream>
using namespace std;

class Base{
public:
	virtual void func(){
		cout << "Hello Base without param " << endl;
	}	
	virtual void func(int a){
		cout << "Hello Base with sigle param " << endl;
	}	
private:
	int m_num;
};

class Derived : public Base{
public:
	void func() override{
		cout << "Hello Deriver" << endl;
	}
};

#if 0
int main(int argc, char *argv[]) {
	Derived d;
	cout << "sizeof(Derived) = " << sizeof(Derived) << endl;
    return 0;
}
#endif

