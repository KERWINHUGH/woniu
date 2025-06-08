/***************************************************
# File Name:    class3.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 25 Feb 2025 03:08:27 PM CST
****************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void hmwk1()
{
	 puts("请输入数组的层数");
	 int i;
	 scanf("%d",&i);
	 puts("请输入数组的列数");
	 int j;
	 scanf("%d",&j);
	 
	 int arr[i][j];
	 int oneLength=sizeof(arr)/sizeof(arr[0]);
	 int twoLength=sizeof(arr[0])/sizeof(arr[0][0]);
	 
	 printf("请输入数组元素\n");
	 
	 for(int i=0;i<oneLength;i++)
	 {
	 	for(int j=0;j<twoLength;j++)
	 	{
	 		scanf("%d",&arr[i][j]);
	 	}
	 }
	 
	 for(int i=0;i<oneLength;i++)
	 {
	 	for(int j=0;j<twoLength;j++)
	 	{
	 		printf("%d\t",arr[i][j]);
	 	}
	 	printf("\n");
	 }
	
}
void hmwk2()
{
	 puts("请输入数组的层数");
	 int i;
	 scanf("%d",&i);
	 puts("请输入数组的列数");
	 int j;
	 scanf("%d",&j);
	 
	 int arr[i][j];
	 int oneLength=sizeof(arr)/sizeof(arr[0]);
	 int twoLength=sizeof(arr[0])/sizeof(arr[0][0]);
	 
	 int aver[oneLength];
	 //int temp1 =0;//存放每个一维数组的总和
	 int temp2 =0;//存放每个一维数组的平均数
	 
	 printf("请输入数组元素\n");
	 
	 //手动输入数组元素
	 for(int i=0;i<oneLength;i++)
	 {
	 	for(int j=0;j<twoLength;j++)
	 	{
	 		printf("请输入[%d][%d]号位置的值",i,j);
	 		scanf("%d",&arr[i][j]);
	 	}
	 }
	 puts("-----------for each----------------");
	 //遍历打印输入的数组元素
	 for(int i=0;i<oneLength;i++)
	 {
	 	for(int j=0;j<twoLength;j++)
	 	{
	 		printf("%d\t",arr[i][j]);
	 	}
	 	printf("\n");
	 }
	  puts("-----------for avg----------------");
	 //求每个一维数组的平均数，并放入到aver[]数组中
	 for(int i=0;i<oneLength;i++)
	 {
	 
	 	int temp1 = 0;
	 	for(int j=0;j<twoLength;j++)
	 	{
	 		temp1+=arr[i][j];
	 		//printf("temp1的值是%d \n",temp1);
			//printf("twoLength：的值是%d \n",twoLength);
	 	}
	 		 //temp2=temp1;
	 		//temp2/=twoLength;
	 		
	 		//printf("temp2的值是===%d \n",temp2);
	 		
	 		aver[i]=temp1/twoLength;
	 		
	 		// if(j==twoLength)
	 		//{
	 			//temp1=0;
	 		//}
	 	 //printf("-------temp1的值是====%d \n",temp1);	
	 	//temp2=0;
	 	printf("\n");
	 }
	 //输出aver[]数组中的元素
	 for(int i=0;i<oneLength;i++)
	 {
	 	printf("------>>%d\t",aver[i]);
	 }
	 printf("\n");
}

void hmwk3()
{
	int num;
	char name[32];

	int length=sizeof(name)/sizeof(name[0]);
	char names[length];
	int temp =1;
	
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
				scanf("%s",names);

				for(int i=0;i<length;i++)
				{
					temp=strcmp(names,&name[i]);
					//printf("names:%s \n",names);
					//puts("---------------------");
					//printf("name[i]:%s \n",name[i]);
					//printf("temp:%d \n",temp);
					if(temp==0)
					{
						puts("用户名已使用，请重新输入！");
						break;
					}else
					{
						for(int i=0;i<length;i++)
						{
							name[i]=names[i];
						}				
					}
				}
				if(temp)
				{
					puts("请输入新用户密码");
					scanf("%s",password);		
					puts("注册成功！");		
				}




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

				return ;

			default:
				puts("输入错误,请重新输入！");
				break;
		}
	}
}

int main(int argc, char *argv[]) {

	puts("作业一输出：");
	//hmwk1();
	
	puts("作业二输出：");
	hmwk2();
	
	puts("作业三输出：");
	//hmwk3();
	
	puts("作业四输出：");
	//hmwk4();
	
    return 0;
}
