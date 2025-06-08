/***************************************************
# File Name:    str.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 02:39:58 PM CST
****************************************************/

#include <stdio.h>
#include <string.h>
 
 void test1()
 {
 	puts("请输入杨辉三角的行数");
 	int length;
 	scanf("%d",&length);
 	int str[length][length];
 	//int onelength=sizeof(str)/sizeof(str[0]);
 	
 	//左右两条边都设置成1
 	for(int i=0;i<length;i++)
 	{
 		
 		str[i][0]=1;
 		str[i][i]=1;
 	}
 	
 	//填充剩余位置的值
 	for(int i=0;i<length;i++)
 	{
 		for(int j=1;j<i;j++)
 		{
 				str[i][j]=str[i-1][j-1]+str[i-1][j];
 		}
 		
 	}
	 
	for(int i=0;i<length;i++)
 	{
 		//输出空格
 	 	for(int k= 0; k<length-i-1; k++ )
 	 	{
			printf(" ");
		}
		//输出数字
 		for(int j=0;j<=i;j++)
 		{
 			printf("%d \t",str[i][j]);
 		}
 		 printf("\n");
 	}
	
 }

int main(int argc, char *argv[]) {

	test1();
	
    return 0;
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

















































