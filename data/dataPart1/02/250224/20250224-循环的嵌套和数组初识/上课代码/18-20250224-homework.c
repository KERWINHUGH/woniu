/***************************************************
# File Name:    18-20250224-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 24 Feb 2025 10:03:44 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>

void one(){
	puts("请输入一个数：");
 	int n ;
 	scanf("%d", &n);
 	
 	int result;
 	
 	if(n == 1 || n == 2){
 		result = 1;
 	}else if(n >= 3){
 		// 算出第n位的值
 		for( int i = 3 , a = 1, b = 1 ; i <= n ; i++ ){
 			result = a + b;
 			a = b;
 			b = result;
 		}
 	}
 	printf("第%d位的值是：%d \n", n, result);

}

void two(){
	int count = 0; 
	for(int i = 1; i <= 80; i++){
		if(i % 2== 0){
		    count++; // count += ?
		}
	}
	printf("100以内的偶数的个数是：%d \n",count);
}


void three(){
	
	
	for(int n = 100; n <= 999; n++){
		
		int ge = n % 10 /1;
		int shi = n % 100 / 10;
		int bai = n % 1000 / 100;
		
		if( ge*ge*ge + shi*shi*shi + bai*bai*bai == n){
			printf("%d,是水仙花数。\n",n);
		}
	}

}

void four(){
	for(int n = 100; n <= 999; n++){
		int ge = n % 10 /1;
		int shi = n % 100 / 10;
		int bai = n % 1000 / 100;
		if(ge == shi && shi == bai){
			printf("%d,是三位相同的数。\n",n);
		}
	}
}

void five(){
	for(int i = 1; i <= 9; i++){
		printf("%d\n", i*111);
	}
}


 
int main(int argc, char *argv[]) {

	//four();
	five();


    return 0;
}
















