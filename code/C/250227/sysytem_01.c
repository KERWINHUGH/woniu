/***************************************************
# File Name:    sysytem.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 11:51:48 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char names[10][32]={"admin"};//存放多个用户名
char passwords[10][32]={"1234"};//存放多个用户密码

int length=sizeof(names)/sizeof(names[0]);
	
bool f=true;
		
int op;

void xianshi();
void xiugai(char xiugaiName[],int length);
void delete(char deleteName[],int length);

void system();
void zhuce();
void denlu();

int chongming();


char loginName[32];
char loginPassword[32];

char newName[32];
char newPassword[32];


char xiugaiName[32];
char xiugaiPassword[32];

char deleteName[32];



//重名验证
int chongming()
{
	int temp=1;
	for(int i=0;i<length;i++)
	{
		temp=strcmp(names[i],newName);
		
		if(temp==0)
		{
			break;
		}
	}
	return temp;
}

//注册流程
void zhuce()
{									
	puts("请输入新用户名:");
	scanf("%s",newName);
	puts("请输入新用户密码:");
	scanf("%s",newPassword);	
		
	int temp =chongming();
									
	int index=-1;
	//要先选中可以写入数据的索引
	for(int i=0;i<length;i++)
	{
		if(strcmp(names[i],"")==0)//比较数组中字符串与空，看是否有空间可以存放新用户名
		{
			index=i;
			break;
		}
	}	

	if(index>=0&&temp!=0)
	{
		strcpy(names[index],newName);
		strcpy(passwords[index],newPassword);
		puts("-----注册成功-----");
	}else 
	{
		if(temp==0)
		{
			puts("用户名已使用！");
		}else
		{
			puts("-----对不起，数据已经满了-----");
		}
	}		

    
}

//登录显示所有已存在的用户名和密码
void xianshi()
{
	for(int i=0;i<length;i++)
	{
		if(strcmp(names[i],"")!=0)
		{
			printf("用户名：%s，密码：%s \n",names[i],passwords[i]);
		}
	}
}

//登录流程
void denlu()
{			
	puts("请输入登录用户名:");
	scanf("%s",loginName);
	puts("请输入登录用户密码:");
	scanf("%s",loginPassword);
			
	//循环遍历数组，匹配需要的值
	bool f=false;
	for(int i=0;i<length;i++)
	{
		if(strcmp(names[i],loginName)==0&&strcmp(passwords[i],loginPassword)==0)
		{
			f=true;
			break;
		}
	}
	if(f)
	{
		int op;
		while(true)
		{
			puts("请选择:    1.显示所有用户    2.新增用户    3.修改用户    4.删除用户    5.退出");
			scanf("%d",&op);
						
			printf("op-------->%d\n",op);
			if(op==1)
			{
				xianshi();
			}else if(op==2)
			{
				zhuce();
			}else if(op==3)
			{
				xiugai(xiugaiName,length);		
			}else if(op==4)
			{	
				//puts("请选择想要删除的用户名：");
				//scanf("%s",deleteName);
				
				delete(deleteName,length);				
			}else if(op==5)
			{
				break;
			}else 
			{
				puts("-----对不起，请输入正确的选项！-----");
			}	
		}
					
	}else
	{
		puts("-----username or password error!-----");
	}
}

//修改流程
void xiugai(char xiugaiName[],int length)
{
	//修改用户名
	
	//修改用户密码
	
}

//删除流程
void delete(char deleteName[],int length)
{
	int index=0;
	char deleteName[]={'0'};
	puts("请输入想要删除掉名字");
	scanf("%s",&deleteName);
	
	for(int i=0;i<length;i++)
	{
		if((strcmp(names[i],deleteName))==0)
		{
			index=i;
			f=0;
			break;
		}
	}
	
	if(!f)
	{
		strcpy(names[index],"");
		strcpy(passwords[index],"");
		printf("删除成功 \n");
	}else
	{
		printf("输入的用户名不存在 \n");
	}
	
}

 void system()
{
	puts("欢迎使用蜗牛门禁系统！");
	
	while(f)
	{
		puts("请选择需要的操作：1：注册    2：登录    3：退出");	
		scanf("%d",&op);

		switch(op)
		{
			case 1:
					zhuce();
					break;
			case 2:
					denlu();
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
	
	system();
    
    return 0;
}
