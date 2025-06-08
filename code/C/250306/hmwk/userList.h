/***************************************************
# File Name:    arr.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Thu 06 Mar 2025 11:19:09 AM CST
****************************************************/


#ifndef LIST_H
#define LIST_H

#include "system.h"
 
#define INIT_SIZE 6


// 定义自己的列表
typedef struct {
	UserData *head;    // 数组的首位置指针
	UserData length;   // 数据长度
	UserData capacity; // 数组的容量
} List;

// 初始化：
List* initList();

// 增加数据
void add_list(List *list, int data);
// 删除数据
void delete_list(List *list, int index);
// 修改数据
void set_list(List *list, int index, int value);

// 查询数据
int get_list(List *list, int index);

// 扩容
void increament_list(List *list);
// 回收内存
void listFree(List *list);
// 显示数据
void toString_list(List *list);

// 结束

#endif
