/***************************************************
# File Name:    10-20250221-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 09:37:00 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void one(){

	for(  int i = 1; i < 10; i++ ){
		// 循环的代码。。。
	}
	
	int j = 1;
	while(j <= 10){
		// 循环的代码。。。
	}

	do{
		// 循环的代码。。。
	
	}while( true | false);


}



int main(int argc, char *argv[]) {
	int i = 100;
	while(i < 10){
		i++;
		
		//if(i == 5){
			//continue; // 注意：不能跳过自增！
			//break;
		//}
	
		printf("%d \n",i);
	}
	
	puts("------------------------");
	int j = 100;
	do{
		printf("do...while(): %d \n", j);
		j++;
	}while(j<=10);
	
	
	
	
	puts("---end---");
    return 0;
}
