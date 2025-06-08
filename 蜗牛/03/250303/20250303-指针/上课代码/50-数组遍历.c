/***************************************************
# File Name:    48-指针初识.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 03 Mar 2025 11:35:19 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
	
	int arr[] = {11,22,33,44,55,66,77,88};
	int length = sizeof(arr) / sizeof(arr[0]);

	// 数组名，一般情况下，就代表数组的0号位置的指针
	int *p = arr;
	
	int *pp = &arr[length - 1];
	
	printf("0号位置的地址: %p \n", &arr[0] );
	printf("p指向的地址: %p \n", p );
	printf("数组的头和尾距离：%ld \n", pp - p);
	
	puts("---------------- 通过指针遍历数组 ----------------------");
	// 使用指针，遍历数组 
	for(int i = 0; i < length ; i++ ){
		// 方式一：使用索引 
		printf("%d \n", p[i] );
		
		// 方式二：移动指针
		//printf("%d \n", *p );
		
		// 方式三：指针运算，不改变原指针
		//printf("%d \n", *(p+i) );
		
	}
	printf("p指向的地址: %p \n", p );
	
	
	

    return 0;
}











