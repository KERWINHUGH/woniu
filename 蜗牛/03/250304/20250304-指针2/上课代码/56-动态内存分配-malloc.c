/***************************************************
# File Name:    56-动态内存分配.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 04 Mar 2025 11:29:03 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


 
int main(int argc, char *argv[]) {
	
	int arr[6] = {123,123123,5455,6677,222,6666};
	
	char str[][32] = {"jack","lili", "jerry"};
	
	
	int length = 8;
	// 完整写法：
	// 1: 分配内存
//	char *p = (char * )malloc( sizeof(char) * length );
	int *p = malloc( sizeof(int) * length );

	// 2: 初始化刚分配的内存空间
	memset( p , 0 , sizeof(int) * length );

//	memset( p , 97 , sizeof(char) * length );

	for(int i = 0; i < length; i++){
		printf("---%c=== \n", p[i]);
	}
	
	
	// 3: 回收内存
	free(p);

    return 0;
}











