/***********************************************************************************
# File Name:    test05.c
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Thu May 15 14:02:27 2025
 **********************************************************************************/

#include <iostream>
using namespace std;

namespace A {
	void func() {
		printf("This is func\n");
	}
}

void func() {
	printf("This is func\n");
}

#if 0
// 这里这么写，程序就会报错
int func() {
	printf("This is func with return value!\n");
	return 100;
}
#endif

void func(int x) {
	printf("This is func, x = %d\n", x);
}

// 如果这么写，可能与一个参数的重载函数在调用的时候产生歧义
void func(int x, int y = 22) {
	printf("This is func with 2 params, x = %d, y = %d\n", x, y);
}

void func(double x) {
	printf("This is func, param x is float = %lf\n", x);
}

int main(int argc, char *argv[]) {
	//func();
	func(10, 20);
	func(201);
	//func(1.9);
    return 0;
}
