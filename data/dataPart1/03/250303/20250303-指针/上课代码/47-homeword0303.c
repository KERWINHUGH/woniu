/***************************************************
# File Name:    47-homeword0303.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 03 Mar 2025 11:03:30 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	char name[32];
	int count;
}Candidate;

int findIndexByName(Candidate arr[], int length, char name[]){
	for(int i = 0; i < length; i++){
		if(strcmp( arr[i].name, name ) == 0){
			return i;
		}
	}
	return -1;
}


int main(int argc, char *argv[]) {
	Candidate arr[3] = {
		"jack",0,
		"mike",0,
		"jerry",0
	};
	
	int length = sizeof(arr) / sizeof(arr[0]);

	// 1: 投票
	char temp[32];
	for(int i = 0; i < 10; i ++){
		printf("第%d个选民，请输入候选人姓名：", i+1 );
		scanf("%s", temp );
		int index = findIndexByName(arr, length, temp);
		if(index >= 0){
			arr[index].count ++;
		}else {
			puts("对不起，没有该候选人！请重输！");
			i--;
		}
	}
	// 2: 显示信息
	for(int i = 0; i < length; i ++){
		printf("候选人:[姓名：%s, 选票：%d ]\n", arr[i].name, arr[i].count);
	}


    return 0;
}

















