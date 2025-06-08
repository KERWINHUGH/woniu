/***************************************************
# File Name:    使用类的静态成员变量.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月21日 星期三 11时11分54秒
****************************************************/

#include <iostream>
using namespace std;

class point{
public:
	point(){
		m_count++;
	}
	~point(){
		m_count++;
	}
	static void output(){
		cout << "m_count =" << m_count << endl;
	}
private:
	static int m_count;

};

//类外定义类中的静态成员变量，不用带static关键字
int point::m_count = 0;

int main(int argc, char *argv[]) {
	point pt;

	//直接使用静态成员变量会报错，必须在类外初始化
	pt.output();
    return 0;
}
