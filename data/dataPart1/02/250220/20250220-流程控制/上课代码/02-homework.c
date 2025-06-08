/***************************************************
# File Name:    02-homework.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 05:44:24 PM PST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {
	int a = 10;

	int b = 5;
	//printf("%d, %d ", --a, a-- );

	printf("%d \n", a+++b);
	printf("a=%d , b=%d \n",a,b);

	puts("--------------------------------------");

	int score;
	puts("请输入分数：");
	scanf("%d", &score);

	if(score <= 100 && score >= 0){
		if(score >= 90){
			puts("优秀");
		}else if(score >= 80){
			puts("良好");
		}else if(score >= 70){
			puts("一般");
		}else if(score >= 60){
			puts("及格");
		}else {
			puts("挨打！");
		}
	}else {
		puts("对不起，不是正常的分数值！");
	}

	puts("-------------------------------------------");
		if(score >= 90 && score <= 100 ){
			puts("优秀");
		}else if(score >= 80 && score < 90){
			puts("良好");
		}else if(score >= 70 && score < 80){
			puts("一般");
		}else if(score >= 60 && score < 70){
			puts("及格");
		}else if(score >=0 && score < 60){
			puts("挨打！");
		}else {
			puts("分数有误！");
		}



    return 0;
}
