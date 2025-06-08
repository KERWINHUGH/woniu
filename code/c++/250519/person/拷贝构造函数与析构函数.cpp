/***************************************************
# File Name:    拷贝构造函数与析构函数.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月19日 星期一 17时09分32秒
****************************************************/

#include <iostream>
#include <cstring>
using namespace std;

class Info{
public:
	//构造函数
	Info(){
		p = new char(32);
		cout << "This is Info's constructor without param" << endl;
	}

	//拷贝构造函数（自定义），深拷贝
	Info(const Info &info){
		cout << "This is Info's copy constructor" << endl;
		p = new char(32);
		memcpy(p, info.p, strlen(info.p));
	}

	//析构函数
	~Info(){
		cout << "This is INfo's destructor" << endl;
		delete p;
		p = nullptr;
	}

private:
	int m_id;
	char *p;
};

int main(int argc, char *argv[]) {
	
	Info info1;	//为info1创建一个指针，指向info1的内存空间地址
	//使用类的对象初始化另一个对象，当类中没有声明拷贝构造函数时，编译器会自动调用默认的拷贝构造函数
	//在拷贝对象时，会为info2创建另一个指针也指向要拷贝对象的内存（即info1的内存）
	//此时可能会导致析构函数重复释放对象资源，叫做浅拷贝。
	//对应的深拷贝，就是自定义一个拷贝构造函数，在函数中为对象指针分配另一块空间，并将要拷贝的对象赋值到分配的内存中去
	Info info2(info1);

    return 0;
}
