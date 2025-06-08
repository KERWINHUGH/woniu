/***************************************************
# File Name:    hmwk.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 24 Feb 2025 05:43:29 PM CST
****************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void hmwk1()
{
	int ch=0,ra=0;
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
		{
			if(i+j==15&&2*i+4*j==40)
			{
				printf("鸡有%d只，兔有%d只 \n",i,j);
			}
		}
	}
}

void hmwk2()
{
	puts("请输入底数");
	int x;
	scanf("%d",&x);
	puts("请输入指数");
	int y;
	scanf("%d",&y);
	int n=1;
	for(int i=0;i<y;i++)
	{
		if(x>0&&x!=0)
		{
			n*=x;
		}
	}
	printf("%d的%d次方是%d \n",x,y,n);
}

void hmwk3()
{
	puts("请输入你的数");
	int n;
	scanf("%d",&n);
	
	if(n<=0)
	{
		puts("输入不合法");
	}
	int ispri=1;
	for(int i=2;i<=n/2;i++)
	{
		if(n%i==0)
		{
			ispri=0;
			break
			;
		}
	}
	if(ispri)
	{
		printf("%d是一个质数 \n",n);
	}else
	{
			printf("%d不是一个质数 \n",n);
	}
}

void hmwk4()
{
	double high=100;// 小球高度
	double width=0;//小球路程

	for(int i=0; i<10;i++)
	{
		width+=high;
		if(i<n)
		{
			high/=2;
			width+=high;
		}else
		{
			high/=2;
		}
		
	}
	printf("高度为%lf \n",high);
	printf("总路程为%lf \n",width);
}

void hmwk5()
{
	for(int i=2;i<=100;i++)
	{
	    int ispri=1;
		for(int j=2;j<=i/2;j++)
		{
			if(i%j==0)
			{
				ispri=0;
			}
		}
		if(ispri)
		{
			printf("%d \n" ,i);
		}
	}
}

void hmwk6()
{
	for(int i=9;i>=1;i--)
	{
		for(int j=1;j<=i;j++)
		{
			printf("%d * %d = %d \t",i,j,i*j);
		}
		printf("\n");
	}
}

void hmwk7()
{
	int n;
	
	srand(time(NULL));
	int random = rand()%100;
	int random_number = (rand()%99)+1;
	int count;
	
	while(1)
	{
		puts("请输入你的数");
		scanf("%d",&n);
		count++;
		if(random_number==n)
		{
			puts("恭喜你，猜对啦！游戏结束。");
			break;
		}else if(random_number>n)
		{
			puts("猜小啦，重新猜吧");
		}else
		{
			puts("猜大啦，重新猜吧");
		}
	}
	printf("一共猜了%d次 \n",count);
	
}

void hmwk8()
{
	int count=0;
	int i=20;
	while(i>2)
	{
		i-=3;
	
		count++;

		i++;

	}
	printf("20块钱可以喝%d瓶可乐 \n",count);
}

void hmwk9()
{
	int num;
	puts("请输入行数");
	scanf("%d",&num);
	if(i<3)
	{
		puts("输入非法，请重新输入！");
		continue;
	}
	for(int i=1;i<=num;i++)
	{
		//输出空格
		for(int j=num-i;j>0;j++)
		{
			printf(" ");
		}

	    	//输出星号
		for(int i=1;i<i/2-1;i++)
		{
			puts("*");
		}
		puts("\n");
	}
	//输出倒三角
	for(int i=num-1;i>=1;i--)
	{
	//输出空格
	for(int j=0;j<num-i;j++)
	{
		printf(" ");
	}
	//输出星号
		for(int j=i*2-1;j>=1;j--)
		{
			printf("*");
		}
	}
}

void hmwk10()
{
	int y,n,a;
	int score = 0;
	int count = 0;
	
	
	puts("请输入学生个数");
	scanf("%d",&y);
	a=y;
	
	while(a)
	{
		puts("请输入学生成绩");
		scanf("%d",&n);
		
		if(n<0||n>100)
		{
			puts("输入的成绩不合法，请重新输入！");
			continue;
		}else
		{
			score+=n;
		}

		if(n<60)
		{
			count++;
		}	
		
		a--;
	}
	printf("所有学生总分为%d,平均分为%d,不及格人数为%d \n",score,score/y,count);
	
	
	
}

void hmwk11()
{
	int x,y,a;

	int score = 0;
	int count = 0;
	int i=0;
	
	puts("请输入学生个数");
	scanf("%d",&y);
	a=y;
	int arr[a];
	
	for( int i=0;i<y;i++)
	{
		arr[i]=0;
	}
		for(int i=0;i<a;i++)
		{
			puts("请输入学生成绩");
			scanf("%d",&x);
			
			if(arr[i]<0||arr[i]>100)
			{
				puts("输入的成绩不合法，请重新输入！");
				i--;
				continue;
			}elsea
			{
				arr[i]=x;
				score+=arr[i];
			}
			
			if(arr[i]<60)
			{
				count++;
			}	
		
			a--;
		}
		
	printf("所有学生总分为%d,平均分为%d,不及格人数为%d \n",score,score/y,count);
	puts("-------------------------------------------");
	for(i=0;i<y;i++)
	{		
		printf("%d \t",arr[i]);
	}
	
	
	
	
}

int main(int argc, char *argv[]) {

	puts("------作业一输出结果------");
	//hmwk1();
	puts("------作业二输出结果------");
	//hmwk2();
	puts("------作业三输出结果------");
	//hmwk3();
	puts("------作业四输出结果------");
	//hmwk4();
	puts("------作业五输出结果------");
	//hmwk5();	
	puts("------作业六输出结果------");
	//hmwk6();
	puts("------作业七输出结果------");
	//hmwk7();
	puts("------作业八输出结果------");
	//hmwk8();
	puts("------作业九输出结果------");
	//hmwk9();
	puts("------作业十输出结果------");
	//hmwk10();
	hmwk11();
	
    return 0;
}
