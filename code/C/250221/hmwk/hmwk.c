/***************************************************
# File Name:    hmwk.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Feb 2025 05:46:12 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


void hmwk1()
{
	for(int i=1;i<=500;i++)
	{
		printf("%d \n",i);
	}
}

void hmwk2()
{
	int sum=0;
	for(int i=1;i<=10;i++)
	{
		sum+=i;
	}
		printf("%d \n",sum);
}


void hmwk3()
{
	int sum=0;
	for(int i=100;i<=500;i++)
	{
		sum+=i;
	}
		printf("%d \n",sum);
}

void hmwk4()
{
	int sum=1;
	for(int i=1;i<=10;i++)
	{
		sum*=i;
	}
		printf("%d \n",sum);
}

void hmwk5()
{
	int sum=0;
	for(int i=1;i<=100;i++)
	{
		if(i%2==0)
		{
			sum+=i;
		}
	}
		printf("%d \n",sum);
}
void hmwk6()
{
	int sum=0;
	for(int i=1;i<=100;i++)
	{ 
		if(i%5==0)
		{
			printf("%d \n",i);
			sum++;
		}
	}
		printf("%d \n",sum);
}

void hmwk7()
{
	int ge,shi,bai;

//	puts("请输入一个三位数");
 
//	scanf("%d",&num);
	
	
	for( int i = 100 ; i<=999 ;i++)
	{
		ge = i % 10/1;
		shi = i % 100/10;
		bai = i % 1000/100;
		
		if(ge*ge*ge+shi*shi*shi+bai*bai*bai == i)
		{
			printf("%d \n",i);
		}
	}
}

void hmwk8()
{
	int ge,shi,bai;

//	puts("请输入一个三位数");
 
//	scanf("%d",&num);
	
	
	for( int i = 100 ; i<=999 ;i++)
	{
		ge = i % 10/1;
		shi = i % 100/10;
		bai = i % 1000/100;
		
		if(ge == shi && shi == bai)
		{
			printf("%d \n",i);
		}
	}

}

void hmwk9()
{
	int num;
	char name[32];
	char password[32];

	char loginName[32];
	char loginPassword[32];

	int n_t,p_t;
	
	puts("欢迎使用蜗牛门禁系统！");
	
	while(1)
	{

	puts("请选择需要的操作：1：注册    2：登录    3：退出");

	scanf("%d",&num);

	switch(num)
	{
		case 1:
			puts("请输入新用户名");
			scanf("%s",name);
			puts("请输入新用户密码");
			scanf("%s",password);

			puts("注册成功！");

			break;
		case 2:

			puts("请输入登录用户名");
			scanf("%s",loginName);
			puts("请输入登录用户密码");
			scanf("%s",loginPassword);
			
			n_t = strcmp(name,loginName);
			p_t = strcmp(password,loginPassword);

			if(n_t)
			{
				puts("username error!");
			}else if(p_t)
			{
				puts("password error!");
			}else if(!n_t &&!p_t)
			{
				puts("login success!");
			} 

			break;
		case 3:
			puts("您已退出系统。");

                       return;
			break;

		default:
			puts("输入错误,请重新输入！");
			break;

	}
	}
}

void hmwk10()
{
    puts("请输入第n个数");
    int n;
    scanf("%d",&n);
    
    int result=0;
    
    if(n==1 ||n==2)
    {
        result =1;
    }else if(n>=3)
    {
        for(int i=3,a=1,b=1;i<=n;i++)
        {
            result=a+b;
            a=b;
            b=result;
        }
    }
    printf("第%d位的值是%d \n",n,result);
}

int main(int argc, char *argv[]) {

	puts("-------作业一执行结果--------");
	hmwk1();
	puts("-------作业二执行结果--------");
	hmwk2();
	puts("-------作业三执行结果--------");
	hmwk3();
	puts("-------作业四执行结果--------");
	hmwk4();
	puts("-------作业五执行结果--------");
	hmwk5();
	puts("-------作业六执行结果--------");
	hmwk6();
	puts("-------作业七执行结果--------");
	hmwk7();
	puts("-------作业八执行结果--------");
	hmwk8();
	puts("-------作业九执行结果--------");
	hmwk9();
	puts("-------作业十执行结果--------");
	hmwk10();
    return 0;
}
