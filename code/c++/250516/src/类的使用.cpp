/***************************************************
# File Name:    类的使用.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月16日 星期五 12时09分20秒
****************************************************/

#include <iostream>
using namespace std;


struct Test1{
public:
	int a;
protected:
	int b;
private:
	int c;
};


struct Test{
public:
	int a;
	int b;
	int c;
};

class B{
public:
	int m;
	void func();
	//函数在类内声明并实现，就是一个内联函数
	void func(int x){
		m = x;
		cout << "m = "<< m << endl;
	}
protected:
	int y;
private:
	int z;
};

void B::func(){
	cout << "This is classB`s member function , m = "<< m << endl;
	y = 30;
	z = 22;
}

int main(int argc, char *argv[]) {
	//存在private,protected时，不能使用{0}初始化结构体成员
	Test t = {0};
	t.a = 10;
	/*
	//第一种结构体/类的指针使用方式,使用栈内存空间
	B b ;
	B *bp = &b;

	B *bp1 = nullptr;
	bp1 = &b;

	//第二种结构体/类的指针使用方式，使用的是堆内存空间
	B *p = new B;
	p->func(100);
	p->func();
	delete p;
	p = nullptr;;
*/
    return 0;
}
