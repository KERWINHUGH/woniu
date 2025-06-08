/***********************************************************************************
# File Name:    test08.cpp
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Mon May 19 16:22:50 2025
 **********************************************************************************/

#include <iostream>
using namespace std;

class Info {
public:
    Info() {
        cout << "This is Info's constructor without param" << endl;
    }    
    ~Info() {
        cout << "This is Info's destructor" << endl;
    }
};

int main(int argc, char *argv[]) {
    // Info info;   // 会调用构造函数和析构函数
    Info *pInfo = new Info;   // 不会调用构造函数和析构函数
    delete pInfo;
    return 0;
}
