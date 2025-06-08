/***************************************************
# File Name:    hmwk4.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Thu 20 Feb 2025 07:18:51 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {

	float a,b,c,temp;

	puts("请输入第一个数！");
	scanf("%f",&a);

	puts("请输入第二个数！");
	scanf("%f",&b);

	puts("请输入第三个数！");
	scanf("%f",&c);

	if(a>b)
	{
		temp = a;
		a = b;
		b = temp;
		 if(b>c)
			{				
				temp = b;
				b = c;
				c = temp;
			}
	}else if(b>c)
		{				
			temp = b;
			b = c;
			c = temp;
			}
	printf("%.2f,%.2f,%.2f三个数中最大值为%5.2f \n",a,b,c,c);

    return 0;
}
