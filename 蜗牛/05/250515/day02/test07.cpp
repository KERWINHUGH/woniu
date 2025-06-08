/***********************************************************************************
# File Name:    test07.cpp
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Thu May 15 15:28:24 2025
 **********************************************************************************/

#include <iostream>
using namespace std;

int main() {
    int a = 10;
	auto f = [=](int x) {
		//a = 20;
		cout << "inside a = " << a+x << endl;
	};
	f(10);
    cout << " outside a = " << a << endl;
    return 0;
}
