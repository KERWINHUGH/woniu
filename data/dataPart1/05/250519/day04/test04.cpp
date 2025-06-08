/***********************************************************************************
# File Name:    test04.cpp
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Mon May 19 14:10:47 2025
 **********************************************************************************/

#include <iostream>
using namespace std;

class Info {
public:
    // 1. 赋值初始化
    // Info() {
    //     m_id = 10020;
    //     m_age = 20;
    //     // rx = m_age;
    //     // x = 33;
    // }

    // 2. 成员初始化列表(参数列表初始化) ----- 效率最高,功能最强大
    Info() 
    : m_id(10011)
    , m_age(22)
    , x(33)
    , rx(m_age) {
        
    }

    int getId() const {
        return m_id;
    }

    int getAge() const {
        return m_age;
    }

private:
    int m_id;
    int m_age;
    const int x;
    int &rx;
    // 3. 直接初始化
    //int m_id = 10010;
    //int m_age = 21;
};

int main(int argc, char *argv[]) {
    Info info;
    cout << "Id = " << info.getId() << endl;
    cout << "Age = " << info.getAge() << endl;
    return 0;
}
