/***********************************************************************************
# File Name:    test05.cpp
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Mon May 19 15:32:19 2025
***********************************************************************************/

#include <iostream>
using namespace std;

class Info {
public:
    explicit Info(int id) {
		cout << "This is Info's constructor without param" << endl;
        m_id = id;
    }
	
    bool isEqual(const Info &info) {
        return m_id == info.m_id;
    }

private:
	int m_id;
};

int main(int argc, char *argv[]) {
    Info info(1);
    bool bEq = info.isEqual(1);    // 参数为1,实现从int型到A的隐式转换
    return 0;
}
