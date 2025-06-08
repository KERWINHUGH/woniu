/***************************************************
# File Name:    10-20250221-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 09:37:00 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>

 
int main(int argc, char *argv[]) {
	
	for( int i = 1; i <= 10  ; i++ ){
		if(i == 5){
			//continue;   // 跳过当次循环，后面继续
			break;        // 结束当前循环，(离break最近的循环)
		}
		printf("跑第 %d 圈 \n", i);
	
	}
	
	
	
	puts("---end---");

    return 0;
}
