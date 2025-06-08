/***************************************************
# File Name:    61-其它类型指针.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 05 Mar 2025 02:03:56 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
 int* search(int index,  int (*p)[4] );
 
int main(int argc, char *argv[]) {
	
	int score[3][4]={{60,70,80,90},{56,89,67,82},{78,90,66,100}};
	
	puts("请输入学生的序号：");
	int op;
	
	scanf("%d", &op);
	
	// 调用函数：
	int *p = search(op, score );
	for(int i = 0; i < 4; i++){
		printf( "%d \t", p[i] );
	}
	printf("\n");
	
    return 0;
}

int* search(int index,  int (*p)[4] ){
	index--;	
	return  *(p + index);
}























