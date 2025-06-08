/***********************************************************************************
# File Name:    test09.cpp
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Mon May 19 16:30:25 2025
 **********************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

class Info {
public:
    // 构造函数
    Info() {
        p = new char(32);
        cout << "This is Info's constructor without param" << endl;
    }

    // 拷贝构造函数(自定义), 深拷贝
    Info(const Info &info) {
        cout << "This is Info's copy constructor" << endl;
        p = new char(32);
        memcpy(p, info.p, strlen(info.p));
    }    

    // 析构函数
    ~Info() {
        cout << "This is Info's destructor" << endl;
        delete p;
        p = nullptr;
    }

private:
    int m_id;
    char *p;
};

int main(int argc, char *argv[]) {
    Info info1;
    Info info2(info1);      // 使用类的对象初始化另一个对象
    return 0;
}
