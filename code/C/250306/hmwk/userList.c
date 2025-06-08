/***************************************************
# File Name:    arr.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Thu 06 Mar 2025 11:19:09 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"



// 初始化：
List* initList(){
	List *list = malloc(sizeof(List));	
	list->head = malloc(sizeof(UserData) * INIT_SIZE );
	list->length = 0;
	list->capacity = INIT_SIZE;
	return list;
}

// 增加数据
void add_list(List *list, UserData data){
	// 先判断是否需要扩容
	if(list->length == list->capacity){
		// 调用扩容函数
		increament(list);
	}
	list->head[list->length] = data; // 新的数据总是添加到最后一个位置
	list->length++;
}

// 删除数据
void delete_list(List *list, int index){
	// 1: 先判断索引是否有效
	if(index < 0 || index >= list->length){
		fprintf(stderr, "索引无效!");
		//exit(EXIT_FAILURE);  //  退出程序
		return ;
	}
	// 删除操作：
	list->head[index] = 0;
	// 后面的数据前移
	for(int i = index; i < list->length-1; i++){
		list->head[i] = list->head[i+1];
	}
	// 最后一个位置置0：
	list->head[list->length-1] = 0;
	list->length--;
}

// 修改数据
void set_list(List *list, int index, UserData value){

// 1: 先判断索引是否有效
	if(index < 0 || index >= list->length){
		fprintf(stderr, "索引无效!");
		//exit(EXIT_FAILURE);  //  退出程序
	}
	
	list->head[index]=value;
}

// 查询数据
int get_list(List *list, int index){
	// 1: 先判断索引是否有效
	if(index < 0 || index >= list->length){
		fprintf(stderr, "索引无效!");
		//exit(EXIT_FAILURE);  //  退出程序
		return 1;
	}
	
	return list->head[index];
}

// 扩容
void increament_list(List *list){
	int newSize = list->capacity*2;
	int *temp = realloc(list->head , newSize * sizeof(UserData));
	//对新分配的内存进行初始化 
	memset( temp + list->length, 0 , sizeof(UserData) * newSize / 2 );
	// 更新容量
	list->capacity = newSize;
	// 重新给head赋值：
	list->head = temp;
}


// 回收内存
void listFree(List *list){
	// 先回收成员，再回收结构体：（先小->大）
	free(list->head);
	free(list);
	
	list->head = NULL;
	list = NULL;
	puts("----内存回收完成----");
}


// 显示数据
void toString_list(List *list){
	printf("list:容量：%d [", list->capacity);
	
	for(int i = 0; i < list->length; i++){
		if( i != list->length -1){
			printf("%d , ", list->head[i]);
		}else {
			printf("%d ", list->head[i]);
		}
	}
	printf("]\n");
}
