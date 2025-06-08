/***********************************************************************************
# File Name:    test05.c
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Thu May 15 14:02:27 2025
 **********************************************************************************/

#include <stdio.h>

void func() {
	printf("This is func\n");
}

void func(int x) {
	printf("This is func, x = %d\n", x);
}

int main(int argc, char *argv[]) {
	func();
	func(10);
    return 0;
}
