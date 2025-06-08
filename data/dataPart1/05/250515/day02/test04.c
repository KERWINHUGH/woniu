/***********************************************************************************
# File Name:    test04.c
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Thu May 15 11:50:25 2025
 **********************************************************************************/

#include <stdio.h>

void func(int x) {
	printf("This is Func, x = %d!\n", x);
}

void func1(int x = 99) {
	printf("This is Func, x = %d!\n", x);
}

int main(int argc, char *argv[]) {
	func(10);
    return 0;
}
