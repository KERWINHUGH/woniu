/***********************************************************************************
# File Name:    test03.cpp
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Mon May 19 11:44:53 2025
**********************************************************************************/

#include <iostream>
using namespace std;

class Info {
public:
    // Info() {
    //     m_id = 123;
    //     cout << "This is Info's constructor without param" << endl;
    // }

    // 有参构造函数(在这里有缺陷)
    // Info(int id) {
    //     m_id = id;
    //     cout << "This is Info's constructor with param" << endl;
    // }

    Info() = default;       // 指定使用默认构造函数, Info() {}
    Info() = delete;        // 禁用默认构造函数, Info() {}
    
    // 缺省参数的构造函数
    // Info(int id = 0) {
    //     m_id = id;
    //     cout << "This is Info's constructor with default param" << endl;
    // }

    int getId() const {
        return m_id;
    }

private:
    int m_id;
};

int main(int argc, char* argv[]) {
    // Info info1(23);      // 自动调用构造函数
    // cout << info1.getId() << endl;

    Info info2;     // 自动调用构造函数
    cout << info2.getId() << endl;

    return 0;
}