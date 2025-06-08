/***************************************************
# File Name:    成员变量初始化方式.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月19日 星期一 15时57分39秒
****************************************************/

#include <iostream>
using namespace std;

class Info{
public:
	//1.赋值初始化
//	Info() {
//		m_id = 100;
//		m_age = 20;
		//不能用这种方式初始化const常量或引用
		//rx = m_age;
		//x =33;
//	}

	//2.参数列表初始化（成员初始化列表）
	//一般使用这种方式初始化const和引用
	Info()
	:x(33)
	,rx(m_id)
	,m_id(100)
	,m_age(22)
	
	{
	}

	int getId() const{
		return m_id;
	}

	int getAge() const{
		return m_age;
	}

	int getX() const{
		return x;
	}

	int getRx() const{
		return rx;
	}

private:
	int m_id;
	int m_age;
	const int x;
	int &rx;
	
	//3.直接初始化
	//int m_id;
	//int m_age;
	//const int x;
	
};

int main(int argc, char *argv[]) {
	Info info;
	cout << "id =" << info.getId() << endl;
	cout << "age = " << info.getAge() << endl;
	cout << "x =" << info.getX() << endl;
	cout << "rx = " << info.getRx() << endl;
    return 0;
}
