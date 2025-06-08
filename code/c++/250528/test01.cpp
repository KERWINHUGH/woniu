/***************************************************
# File Name:    test01.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月28日 星期三 20时05分00秒
****************************************************/

#include <iostream>
#include <exception>
using namespace std;
struct MyException : public exception {
public:
    const char *what () const throw() {
        return "C++ Exception";
    }
};
int main() {
    try {
        throw MyException();
    }
    catch(MyException &e) {
        std::cout << "MyException caught" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch(std::exception &e) {
        // 其他的错误
    }
    return 0;
}
