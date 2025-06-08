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

void testRealloc(){
	int length = 4;
	int *p = malloc( sizeof(int) * length );
	memset( p , 0 , sizeof(int) * length );
	for(int i = 0; i < length; i++){
		*(p+i) = (i+1)*10;
	}
	
	// 1: 使用realloc 扩容数组
	length = length + 3;

	// 语法：void* realloc(void *ptr , int newSize);
	int *pp = (int *)realloc(p, sizeof(int) * length );
	if(pp == NULL){
		fprintf( stderr , "内存分配失败!\n" );
		free(p);  // 记住，对原内存回收。
		return;
	}
	
	// 2:对新分配的内存进行初始化操作：
	memset( pp+4 , 0 , sizeof(int )* 3 ); 
	
	
	for(int i = 0; i < length; i++){
		printf("%d\t" , pp[i]);
	}
	printf("\n");
	
	// 3: 回收内存
	free(pp);
}

char* my_strcat(char *one, char *two){
	// 分配内存存每一个字符串
	int length = strlen(one);
	
	char *p1 = malloc( length );
	memset( p1, 0 , length );

	for(int i = 0; i < length ; i++){
		*(p1+i) =  *(one+i);
	}
	
	// 第二个字符串处理：
	int newLength = length + strlen(two) + 1;
	char *temp = realloc( p1, newLength);
	
	// 对新分配的内存进行初始化操作：  （ 这里加了1，我们后面就不用手动补 '\0' ）
	memset( temp + length  , 0 , strlen(two) + 1 );
	
	// 把第二个字符串的值，给到新的内存里：
	for(int i = 0; i < strlen(two); i++){
	  *(temp + length + i) = *(two + i );
	}
	// 最后，补上结束符(前面处理过了，就不用手动补)：
	return temp;
}

void myFree(void *p){
	free(p);
}

 
int main(int argc, char *argv[]) {
	char a[] = "hello,";
	char b[] = "world!";
	char *p = my_strcat(a,b);
	printf("%s \n", p);
	
	myFree(p);

    return 0;
}











