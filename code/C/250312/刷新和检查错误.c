/***************************************************
# File Name:    IO.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Wed 12 Mar 2025 09:29:46 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>


#include <string.h>
#include <stdlib.h>
 
int main(int argc, char *argv[]) {
	FILE *fp = fopen("student.txt","a");
	if(fp == NULL){
		perror("打开文件失败");
		return -1;
	}
	printf("打开文件成功\n");
	fclose(fp);

    return 0;
}
