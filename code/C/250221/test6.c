/***************************************************
# File Name:    test5.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 03:52:54 PM CST
****************************************************/

#include <stdio.h>
 
int main(int argc, char *argv[]) {
	
	char num;
	int addNum = 0;
	int addChar = 0;
	int addOther = 0;
	
	do
	{
		scanf(" %c",&num);
		if(num>='1'&& num<='9')
		{
			addNum++;
		}else if((num>='A'&& num<='Z')||( num>='a'&& num<='z'))
		{
			addChar++;	
		}else
		{
			addOther++;
		}
	}while(num != '0');
	printf("输入的数字有%d个，字母有%d个，其他字符有%d个 \n",addNum,addChar,addOther);
    return 0;
}
