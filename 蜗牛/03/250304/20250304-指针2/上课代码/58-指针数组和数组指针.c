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

// 测试指针数组： int *p[3];
void testOne01(){
// 指针数组：一维使用：
	int a = 10, b = 20, c = 30;
	int *p[3];
	p[0] = &a;
	p[1] = &b;
	p[2] = &c;
	
	for(int i = 0 ; i < 3 ; i++){
		printf("%d \n", *p[i]);
	}
}
// 指针数组：二维使用：
void testOne02(){
	int arr[][3] = {11,22,33,44,55,66,77,88};
	// 申明指针数组
	int *p[3];
	p[0] = arr[0];  // 指向二维的第0行
	p[1] = arr[1];
	p[2] = arr[2];
	int oneLength = sizeof(arr) / sizeof(arr[0]);
	int twoLength = sizeof(arr[0]) / sizeof(arr[0][0]);
	for(int i = 0; i < oneLength ; i++){
		for(int j = 0; j < twoLength; j++){
			//printf("[%d][%d]号位置的值是：%d \t", i, j, p[i][j]);
			printf("[%d][%d]号位置的值是：%d \t", i, j,  *(p + i)[j]   );
		}
		printf("\n");
	}
}




// 测试数组指针： int (*p)[3];
void testTwo(){
	// 数组指针：它是一个指针，指向一个数组
	int arr[3] = {11,22,33};
	int (*p)[3] = &arr;
	printf("数组指针：%p \n" , p );

	puts("-------------- 使用数组指针遍历数组 -----------------");

	for(int i = 0; i < 3; i++){
		// 方式一：
		//printf("arr[%d] = %d \n", i,  (*p)[i]  );
		// 方式二：
		printf("arr[%d] = %d \n", i,  p[0][i]  );
	}
		
	int *p2 = arr;
	printf("普通指针：%p \n" , p2 );
	
	puts("----------- 指针向后移一位 ---------------");
	//p++;
	//p2++;
	//printf("数组指针：%p \n" , p );
	//printf("普通指针：%p \n" , p2 );
}


 
int main(int argc, char *argv[]) {
	
	
	//testOne02();
	
	testTwo();




    return 0;
}











