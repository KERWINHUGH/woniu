/***************************************************
# File Name:    hmwk1.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 20 Feb 2025 05:53:39 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	puts("请输入你的成绩");
	
	char score;
   

	scanf("%c",&score);

	switch(score)
	{
	    case 'A':

			puts("优");
			break;

		case 'B':

			puts("良");
			break;

		case 'C':

			puts("一般");
			break;

		case 'D':

			puts("差");
			break;

		case 'E':

			puts("极差");
			break;

		default:
		    puts("输入错误！");
			break;
	}

    return 0;
}
