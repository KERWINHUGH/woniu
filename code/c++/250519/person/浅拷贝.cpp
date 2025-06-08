/***************************************************
# File Name:    浅拷贝.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月19日 星期一 17时47分05秒
****************************************************/

#include <iostream>
using namespace std;

class Info{
public:
	Info(){
		cout << "This is Info's constructor without param" << endl;
	}

	~Info(){
		cout << "This is Info's destructor" << endl;	
	}
};

int main(int argc, char *argv[]) {
	//Info info;	//会调用构造函数和析构函数
	Info *pInfo = new Info;	//会调用构造函数，不会调用析构函数
	delete pInfo;
    return 0;
}
