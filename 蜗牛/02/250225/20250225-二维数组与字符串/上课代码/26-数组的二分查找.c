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

				
 
int main(int argc, char *argv[]) {
	// 二分查找的前提：数组是有序的
	int arr[] = {11,22,33,44,55,66,77,88,99};
	int length = sizeof(arr) / sizeof(arr[0]);
	int num;       // 要查的数
	puts("请输入要查找的数据：");
	scanf("%d", &num);
	
	int index = -1;     // 要查的数的索引
	int count = 0;
	
	int begin = 0;
	int last = length -1;
	int middle;
	
	while(last >= begin){
		count++;
		middle = (begin + last) / 2;
		
		if(num > arr[middle]){
			// 说明数据在后半段
			begin = middle + 1;

		}else if(num < arr[middle]){
			// 说明数据在前半段
			last = middle - 1;
		}else {
			// 找到了数据
			index = middle;
			break;
		}
	}
	printf("数值%d,在数组的 %d 位置,一共查询：%d 次 \n", num, index , count );
	
    return 0;
}


























































