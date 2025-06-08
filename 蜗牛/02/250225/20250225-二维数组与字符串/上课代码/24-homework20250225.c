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

// 用户输入一个数，判断是否是质数(质数：只能被1和本身整除)
void one(){
	puts("请输入一个数：");
	int num;
	scanf("%d", &num);
	
	bool f = false;
	for(int i = 2; i <= num / 2; i++){
		if(num % i == 0){
			f = true;
			break;
		}
	}
	
	if(f){
		printf("%d这个数，不是质数\n",num );
	}else {
		printf("----%d这个数，是质数----\n", num);
	}
}
// 输出100内的所有质数 
void two(){
	for(int num = 2; num <= 100; num++){
		bool f = false;
		for(int i = 2; i <= num / 2; i++){
			if(num % i == 0){
				f = true;
				break;
			}
		}
		
		if(!f){
			printf("----%d这个数，是质数----\n", num);
		}
	}
}
// 一个小球从距离地面100米的空中落下，每次落地后升空落地前一半的高度，
// 求小球第4次弹起的高度，以及到第四次落地为止小球的总路程
void three(){
	double init_height = 100;  // 初始高度100米
	int n = 4;
	double total_distance = 0; // 总路程
	double height = init_height ; // 当前的高度：
	
	for(int i = 1; i <= n; i++){
		// 累记落下的路程
		total_distance += height;  
		// 累记弹起来的路（是落下的一半）, i < n 代表最后一次不加
		if(i < n){
			height /= 2;
			total_distance += height;
		}else {
			// 第10次，落下再弹起的高度：
			height /= 2;
		}
	}
	
	printf("到第%d次，落地为止，小球的总路程是：%.2f米, 第十次弹起的高度是：%.2f \n",n, total_distance, height);
}
/*
	7. 猜数字游戏：系统随机生成一个100内的随机数，用户输入数字进行猜测，如果大了则提示大了，小了则提示小了。直到相等则游戏结束。
	结束后输出游戏的猜测次数  while
	
   书写以下代码可以得到一个100内的随机正整数:
   srand(time(NULL));
   int random  = rand() %100;//该数字就是随机数 0 ~ 99
   int random_number = (rand() % 99) + 1; // 生成1到99之间的随机数

*/

void four(){
	srand(time(NULL));
	int num = (rand() % 99) + 1; // 生成1到99之间的随机数
	printf("100以内的随机数已经生成完成：%d \n", num );
	int count = 0;
	int x;
	while(true){
		puts("请输入你猜的数字：");
		scanf(" %d", &x);
		
		count++;
		
		if(x > num){
			puts("---猜大了---");
		}else if(x < num){
			puts("---猜小了---");
		}else {
			printf("---恭喜，猜对了！---共猜了：%d 次\n",count);
			break;
		}
	}
}
// 打印一个菱形
void five(){
	int num;
	puts("请输入菱形的行数：");
	scanf("%d", &num);
	
	// 输出正三角形
	for(int i = 1; i <= num; i++){
		// 输出空格，把星号挤到中间
		for(int j= num - i; j > 0; j-- ){
			printf(" ");
		}
	
		// 输出星号
		for(int j  = 1; j <= i * 2 -1 ; j++){
			printf("*");
		}
		printf("\n");
	}
	// 输出倒三角型
	
	for(int i = num - 1; i >= 1; i--){
		// 输出空格：
		for(int j= 0; j < num - i; j++ ){
			printf(" ");
		}
		
		// 输出星号：
		for(int j = i*2-1; j >=1; j--){
			printf("*");
		}
		printf("\n");
	}

}

 
int main(int argc, char *argv[]) {
	//two();
	// three();
	//four();
	five();
    return 0;
}
















































