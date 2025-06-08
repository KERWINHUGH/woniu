/***************************************************
# File Name:    18-20250224-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 24 Feb 2025 10:03:44 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>

void one(){
	int arr[6] = {11,22,33,44,55,66};
	
	// 通过索引从数组里取值，格式：数组名[索引]
	printf("%d \n", arr[3]);
	
	puts("--------------- 遍历 --------------------");
	// 遍历：把数组的每个位置都访问一遍
	for(int i = 0; i < 6 ;  i++ ){
		printf("%d \n", arr[ i ]);
	}
	
	// 练习：创建一个数组，长度为5 ，里面存的值是：1 , 3,  5,  7,  9
}


void two(){
	// 如果数组没有初始化，可能会有垃圾值
	// 2,4,6,8,10 写到数组里
	int arr[5];
	// 给每一个位置赋值
	for(int i = 0; i < 5; i++){
		arr[i] = (i + 1) * 2 ;
	}
	
	// 遍历：
	for(int i = 0; i < 5 ;  i++ ){
		printf("%d \n", arr[ i ]);
	}
	
}
// 写练习：创建一个长度为10的数组，每个位置都是10的倍数，10， 20， 30， 40 。。。100
// 	使用循环赋值，然后遍历。
void three(){
	int arr[10] = {0};
	for(int i = 0; i < 10; i++){
		arr[i] = (i + 1) * 10;
	}
	puts("-----倒序遍历-----");
	// 因为数组的索引从0开始，所以最大索引是：数组的长度-1 
	for( int i = 10 -1;  i >= 0 ; i-- ){
		printf("%d \n", arr[ i ]);
	}
}

int main(int argc, char *argv[]) {
	// 练习：创建一个数组：里面存数据是： ‘h’, 'e', 'l', 'l', 'o'
	// 倒序遍历输出该数组的数据
	
	
	//char str[5] = {'h', 'e', 'l', 'l', 'o'};
	
	char str[3] = {'a','b','c'};
	
	puts("----正序遍历----");
	for( int i = 0;  i < 5 ; i++ ){
		printf("%c \t", str[ i ]);
	}
	printf("\n");
	
	
	puts("----倒序遍历----");
	
	for(int i = 5 -1; i >= 0; i--){
		printf("%c \t", str[i]);
	}
	printf("\n");
	

    return 0;
}







































