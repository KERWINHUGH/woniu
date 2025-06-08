/***********************************************************************************
# File Name:    test04.c
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Thu May 15 11:50:25 2025
 **********************************************************************************/

#include <iostream>
using namespace std;

void func(int x) {
	printf("This is Func, x = %d!\n", x);
}

#if 0
// 缺省参数
void func1(int x = 99) {
	printf("This is Func, x = %d!\n", x);
}

//
void func2(int x = 99, int y) {
    cout << "This is Func, x = " << x << endl;
    cout << "This is Func, y = " << y << endl;
}
#endif
void func1(int x = 99, int y = 188) {
        cout << "This is Func, x = " << x << endl;
        cout << "This is Func, y = " << y << endl;
}


int main(int argc, char *argv[]) {
    func1();       
    // 输出：This is Func, x = 99
    // 输出：This is Func, y = 188
    func1(100);    
    // 输出：This is Func, x = 100
    // 输出：This is Func, y = 188
    func1(100, 200);    
    // 输出：This is Func, x = 100
    // 输出：This is Func, y = 200
    return 0;
}
