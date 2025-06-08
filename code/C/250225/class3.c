/***************************************************
# File Name:    class3.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 25 Feb 2025 03:08:27 PM CST
****************************************************/

#include <stdio.h>

void find()
{
	//二分查找
	int a[]={11,22,33,44,55,66,77,88,99};
	int length=sizeof(a)/sizeof(a[0]);
	
	int index=-1;//要查的数的索引
	int count=0;//查的次数
	int num=11;//要查的数
	
	int begin =0;//要查的数的开始的索引
	int last =length-1;//要查的数的结束的索引
	int middle;//要查的数的中位数的索引
	
	while(last>=begin)//当last索引一直大于begin索引时 ，进行查询，当查到last<begin时停止查询
	{

			count++;
			middle=(begin+last)/2;//先求出中位数
		
			if(num>a[middle])
			{
				//要查的数在后半段
				begin=middle+1;
			}else if(num<a[middle])
			{
				//要查的数在前半段
				last=middle-1;
			}else
			{
				//查到数
				index=middle;
				break;
			}
	}

	printf("数值%d,在数组的%d位置，一共查询：%d次 \n",num,index,count);
}

void find1()
{
	//二分查找
	int a[]={11,22,33,44,55,66,77,88,99};
	int length=sizeof(a)/sizeof(a[0]);
	
	int index=-1;//要查的数的索引
	int count=0;//查的次数
	int num;//要查的数
	int isarr=1;//判断输入的数是否在数组中  0:在数组中，1:不在数组中
	
	int begin =0;//要查的数的开始的索引
	int last =length-1;//要查的数的结束的索引
	int middle;//要查的数的中位数的索引
	
	while(isarr)//当last索引一直大于begin索引时 ，进行查询，当查到last<begin时停止查询
	{
		if(last>=begin)
		{
			puts("请输入你的数");
			scanf("%d",&num);
		
			for(int i=0;i<length;i++)
			{
				if(num==a[i])
				{
					isarr=0;
					puts("--");
				}else
				{
					puts("输入的数不在数组中，请重新输入！");
					index++;
					break;
				}
			}
		

		
			count++;
			middle=(begin+last)/2;//先求出中位数
		
			if(num>a[middle])
			{
				//要查的数在后半段
				begin=middle+1;
			}else if(num<a[middle])
			{
				//要查的数在前半段
				last=middle-1;
			}else
			{
				//查到数
				index=middle;
				break;
			}
			}else if(last<begin)
			{
				puts("数组中未查到该元素");
			}
	}

	printf("数值%d,在数组的%d位置，一共查询：%d次 \n",num,index,count);
}

 
int main(int argc, char *argv[]) {

	find1();
    return 0;
}
