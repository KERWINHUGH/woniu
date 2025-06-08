/***************************************************
# File Name:    arr.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Thu 06 Mar 2025 11:19:09 AM CST
****************************************************/


#ifndef LIST_H
#define LIST_H
 
#define INIT_SIZE 2

// 定义自己的列表
typedef struct {
	int *head;    // 数组的首位置指针
	int length;   // 数据长度
	int capacity; // 数组的容量
} List;

// 初始化：
List* initList();

// 增加数据
void add(List *list, int data);
// 删除数据
void delete(List *list, int index);
// 修改数据
void set(List *list, int index, int value);

// 查询数据
int get(List *list, int index);

// 扩容
void increament(List *list);
// 回收内存
void listFree(List *list);
// 显示数据
void toString(List *list);

// 结束

#endif
