/***************************************************
# File Name:    hmwk1.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 20 Feb 2025 05:53:39 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	puts("欢迎使用蜗牛门禁系统");
	
	puts("请选择：1：登录    2：注册    3：退出系统");
	
	int num;
    
	scanf("%d",&num);

	switch(num)
	{
	    case 1:

			puts("登录流程");
			break;

		case 2:

			puts("注册流程");
			break;

		case 3:

			puts("欢迎下次使用！");
			break;

		default:
		    puts("输入错误！");
			break;
	}

    return 0;
}
