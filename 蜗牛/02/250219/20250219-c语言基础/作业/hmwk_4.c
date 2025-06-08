/***************************************************
# File Name:    hmwk_4.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 19 Feb 2025 09:05:39 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	int num;
	
	puts("请输入你的分数（0-100）：");
	
	scanf("%d",&num);
    
    if(num>100 || num<0)
	{
	  puts("输入非法");
	}else if(90<=num && num<=100)
	{
	  puts("优秀");
	}else if(80<=num && num<90)
	      {
		    puts("良好");
		  }else if(70<=num && num<80)
			    {
				  puts("一般");
				}else if(60<=num && num<70)
					  {
					  puts("及格");
					  }else {
							  puts("挨打");
							}

	
    return 0;
}
