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


 
int main(int argc, char *argv[]) {

	// 1: 分配1个int内存
/*
	// void* ptr = calloc(num_elements, element_size);
	int *num = calloc( 1 ,  sizeof(int) ) ;
	*num = 100;
	printf("%d \n", *num );
	
	// 2: 回收内存
	free(num);
*/
	int length = 6;
	int *arr = calloc( length , sizeof(int) );
	for(int i = 0; i < length; i ++){
		printf("%d\n", arr[i]);
	}
	free(arr);

	
	//*num = 200;
	//printf("%d \n", *num );
	
	

    return 0;
}











