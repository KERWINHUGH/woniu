/***************************************************
# File Name:    71-使用自定义头文件.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 06 Mar 2025 11:55:25 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// 引入自己写的头文件：
#include "List.h"
 
int main(int argc, char *argv[]) {

	List *list = initList();
	add(list, 11);
	add(list, 22);
	add(list, 33);
	add(list, 44);

	toString(list);

    return 0;
}
