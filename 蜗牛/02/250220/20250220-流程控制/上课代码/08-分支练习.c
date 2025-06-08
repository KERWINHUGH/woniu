/***************************************************
# File Name:    03-逻辑运算符.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 06:33:57 PM PST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
 
int main(int argc, char *argv[]) {
	int num = 60;
	
	if( num >= 0 && num <=100 ){
		printf("%d是100以内的数 \n", num );
	}else{
		printf("%d不是100以内的数 \n", num );
	}
	
	// -----------------------------
	int number;
	puts("请输入一个三位数：");
	scanf("%d", &number);
	
	int ge, shi, bai;
	ge = number % 10 / 1;
	shi = number % 100 / 10;
	bai = number % 1000 / 100;
	
	if( ge*ge*ge + shi*shi*shi + bai*bai*bai == number ){
		printf("%d 这个数，是水仙花数。\n", number);
	}else {
		puts("---不是水仙花数---");
	}
	
	puts("------end-------");
    return 0;
}








