/***********************************************************************************
# File Name:    test07.cpp
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Mon May 19 16:12:57 2025
 **********************************************************************************/

#include <iostream>
using namespace std;

class Info {
public: 
    // 拷贝构造函数(自定义)
    explicit Info(const Info &info) {
        cout << "This is Info's copy constructor" << endl;
    }
};

// Info Func(Info b) {...}

int main(int argc, char *argv[]) {
    Info info1;
    Info info2(info1);      // 使用类的对象初始化另一个对象
    return 0;
}
