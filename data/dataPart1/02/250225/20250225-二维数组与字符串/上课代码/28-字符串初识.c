/***************************************************
# File Name:    24-homework20250225.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 25 Feb 2025 09:44:27 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>  // 包含这个头文件以使用 rand() 和 srand()
#include <string.h> 

void one(){
	// 字符串：
	char name[] = "jack"; // 字符串的最后，有一个结束符 '\0'
	char name2[4] = "jack";  // 这样写，字符串没有结束符，因为结束符没有地方存放。（不应该出现这样的问题）
	
	printf("name:%s\n",name);
	printf("name2:%s\n",name2);
	
	
	puts("---------------------------------");
	
	int length = sizeof(name) / sizeof(name[0]);
	
	printf("length=%d \n",length);
	for(int i = 0; i < length; i++){
		printf("---%c===\n", name[i]);
	}	
}

int main(int argc, char *argv[]) {
	// 能存多个字符串的数组是一个二维数组（因为字符串本身也是一个数组）
	char names[][32] = {"jack","rose","张三","lili"};
	
	// 遍历输出姓名：
	int length = sizeof(names) / sizeof(names[0]);
	for(int i = 0; i < length; i++){
		printf("%s \n", names[i]);
	}
	puts("----------------------------");
	printf("%s \n",names[2]);	


	puts("------------serach----------------");
	
	char username[] = "张三";
	bool f = false;
	for(int i = 0; i < length; i++){
		if(strcmp(username, names[i]) == 0){
			f = true;
			break;
		}
	}
	if(f){
		printf("数组里找到了数据。\n");
	}else {
		puts("--no--");
	}
	
	
	
	
    return 0;
}


























































