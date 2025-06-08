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



int main(int argc, char *argv[]) {

	List *list = initList();
	add(list, 11);
	add(list, 22);
	add(list, 33);
	add(list, 44);

	toString(list);
	
	set(list, 2, 55);
	
	toString(list);

    return 0;
}
