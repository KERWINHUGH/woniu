/***********************************************************************************
# File Name:    test02.cpp
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Thu May 15 10:31:18 2025
 **********************************************************************************/

#include <iostream>
using namespace std;

void swap1(int x, int y) {
    int tmp = x;
    x = y;
    y = tmp;
}

void swap2(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void swap3(int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}

int main(int argc, char *argv[]) {
    int a = 10;
    int b = 20;
	cout << "a = " << a << "b = " << b << endl;
	swap2(&a, &b);
	cout << "a = " << a << "b = " << b << endl;
    
	cout << "a = " << a << "b = " << b << endl;
	swap3(a, b);
	cout << "a = " << a << "b = " << b << endl;

	return 0; 
}

