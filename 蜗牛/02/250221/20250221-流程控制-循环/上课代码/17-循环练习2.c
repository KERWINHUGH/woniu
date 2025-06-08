/***************************************************
# File Name:    10-20250221-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 09:37:00 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// 1.用户多次输入数字，每次输入一个，直到输入0为止，求用户输入数字里偶数之和
void one(){
	
	int enevSum = 0;
	int num;
	do{
		puts("请输入一个数字：");
		scanf("%d", &num);
		if(num == 0){
			break;
		}
		// 先判断，是偶数才加上
		if(num % 2 == 0){
			enevSum += num;
		}

	}while(true);
	
	printf("你输入的所有数字里，偶数之和是：%d \n", enevSum);
}
// 2.用户输入多次的字符，每次输入一个字符，直到用户输入'0'为止。最终输出用户输入了多少个数字、字母、其他字符。  ch >='0' && ch <='9'
void two(){
	// 准备三个变量，分别存，数字，字母其它符字的个数：
	int numberCount = 0;
	int zCount = 0;
	int otherCount = 0;
	
	char ch;
	do{
		puts("请输入一个字符：");
		scanf(" %c", &ch);
		
		printf("你输入的是：---%c===\n", ch);
		
		if(ch >= '0' && ch <='9'){
			numberCount++;
		
		}else if( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
			zCount++;
		}else {
			otherCount++;
		}
		
		if(ch == '0'){
			break;
		}

	}while(true);
	
	printf("数字：%d , 字母：%d , 其它：%d \n", numberCount, zCount, otherCount);
}


int main(int argc, char *argv[]) {
	//one();

	two();
	
	
	puts("---end---");
    return 0;
}
















