/***************************************************
# File Name:    缺省构造函数.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月19日 星期一 15时01分09秒
****************************************************/
#include <iostream>
using namespace std;


class Info{
public:
	//无参构造函数
	Info(){
		m_id = 125;
		cout << "This is INfo's constructor without param" << endl;
	}

	//有参构造函数
	Info(int id){
		m_id = id;
		cout << "This is INfo's constructor without param" << endl;
	}

	//缺省参数的构造函数
//	Info(int id = 0){
//	m_id = id;
//	cout << "This is INfo's constructor without param" << endl;
//	}

	int getId() const{
		return m_id;
	}
private:
	int m_id;
};


int main(int argc, char *argv[]) {
	Info info1(123); //自动调用构造函数
	cout << info1.getId() << endl;

	Info info2;	//自动调用构造函数
	cout << info2.getId() << endl;
    return 0;
}
