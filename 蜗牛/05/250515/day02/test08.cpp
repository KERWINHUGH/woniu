/***********************************************************************************
# File Name:    test08.cpp
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Thu May 15 15:45:47 2025
 **********************************************************************************/

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	auto isEven = [](int n) { return n % 2 == 0; }; // 判断一个数是否为偶数
	int num = 6;
	if (isEven(num)) {
		cout << num << " is even" << endl;
	} 
	else {
		cout << num << " is odd" << endl;
	}
    return 0;
}
