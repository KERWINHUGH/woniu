/***************************************************
# File Name:    sysytem.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 11:51:48 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "system.h"



char *getTime()
{
	char *t = (char *)malloc(128);
	
	time_t rawtime;
	struct tm *now;
	
	//获取当前时间
	time(&rawtime);
	now = localtime(&rawtime);
	
	//格式化日期和时间，但不包括星期
	strftime(t, 128, "%Y年%m月%d日 %H:%M:%S ", now);
	
	return t;
}

//初始化用户数据
void initUserData()
{
	userdata=(UserData *)malloc(sizeof(UserData)*size);
	//管理员用户
	strcpy(userdata->id,"wnno.0001");
	strcpy(userdata->names,"admin");
	strcpy(userdata->passwords,"1234");
	userdata->age=20;
	userdata->tel=13246579811;
	strcpy(userdata->address,"南京江宁888号");
	strcpy(userdata->loginTime,"1900年1月1日 00:00:00");
	length++;
}

void toString(UserData *u)
{
	printf("用户信息：[ 用户ID：%s，账号：%s, 密码：%s, 年龄：%d, 电话：%ld, 地址：%s ] \n", u->id, u->names, u->passwords, u->age, u->tel, u->address );
}

//判断输入的用户名是否存在，并返回索引
int nameIsExist(char *userName)
{
	//循环遍历数组，匹配需要的值
	int index=-1;//默认输入的用户名不存在
	for(int i=0;i<length;i++)
	{
		if(strcmp(userdata[i].names,userName)==0)
		{
			index=i;//index>=0时表示已经有用过此用户名
			break;
		}
	}
	return index;
}
//验证用户密码是否正确，并返回
bool passwodrVerify(char *verifyPassword,int index)
{
	//循环遍历数组，匹配需要的值
		if(strcmp(userdata[index].passwords,verifyPassword)==0)
		{
			return true;
		}
	return false;
}
//判断是names数组是否存在空间，并返回索引
int spaceIsExist()
{
	int index=-1;//默认没有空间存放用户名
	//要先选中可以写入数据的索引
	for(int i=0;i<length;i++)
	{
		if(strcmp(userdata[i].names,"")==0)//比较数组中字符串与空，看是否有空间可以存放新用户名
		{
			index=i;//index>=0时有空间
			break;
		}
	}
	return index;
}
//如果空间不够，使用此函数进行数组扩容
UserData* addSpace()
{
	size*=2;
	UserData *space=realloc(userdata,sizeof(UserData)*size);//空间不够扩容到之前的两倍空间
	if(space == NULL)
	{
		fprintf(stderr, "对不起，扩容失败");
		free(space);
		return 0;
	}
	memset(space+size/2,0,sizeof(UserData)*size/2);//初始化未有数据的空间
	UserData *p=space;
	free(space);
	space=NULL;
	return p;
}
//注册流程
void addUser(char *userName,char *password)
{										
	if(size>length)
	{
		strcpy(userdata[length].names,userName);
		strcpy(userdata[length].passwords,password);
		length++;
		puts("-----注册成功-----");	
	}else
	{

		userdata=addSpace();

	
		strcpy(userdata[length].names,userName);
		strcpy(userdata[length].passwords,password);
		length++;
		puts("-----注册成功-----");	

	}
		   
}

//登录显示所有已存在的用户名和密码
void displayUser()
{
	for(int i=0;i<length;i++)
	{
		if(strcmp(userdata[i].names,"")!=0)
		{
			//	可以使用指针->
			//printf("用户名：%s，密码：%s \n",userdata[i].names,userdata[i].passwords);
			toString(&userdata[i]);
		}
	}
}

//登录流程
int loginUser(char *userName,char *password)
{					
	int index =nameIsExist(userName);
	if(index>=0)
	{
		if(strcmp(userdata[index].passwords,password)==0)
		{
			index=1;
		}else
		{
			index=0;
		}
	}
	return index;
}

//修改流程
int modifyUser(char *modifyName,char *modifyPassword,int index)
{
			strcpy(userdata[index].names,modifyName);
			strcpy(userdata[index].passwords,modifyPassword);
}
//如果空间不够，使用此函数进行数组扩容
UserData* deleteSpace()
{
	size/=2;
	UserData *space=realloc(userdata,sizeof(UserData)*size);//空间不够扩容到之前的两倍空间
	if(space == NULL)
	{
		fprintf(stderr, "对不起，缩容失败");
		free(space);
		return 0;
	}
	UserData *p=space;
	free(space);
	space=NULL;
	return p;
}
//删除流程
bool deleteUser(int index)
{	
	if(index>=0)
	{
		strcpy(userdata[index].names,"");
		strcpy(userdata[index].passwords,"");
		return true;
	}else
	{
		return false;
	}
		
}

void wn_system()
{
	initUserData();
	puts("欢迎使用蜗牛门禁系统！");
	while(f)
	{
		puts("请选择需要的操作：1：注册    2：登录    3：退出");	
		
		// 正常返回 1， 不正常返回 0
		int result = scanf(" %d", &op);
							
		if(!result){
			// 处理掉异常： 如果scanf出现了异常，我们不断地调用getchar()清空缓冲区。
			while( getchar() != '\n' ){ }
			continue;
		}

		switch(op)
		{
			case 1:
					puts("请输入新用户名:");
					scanf("%s",new.names);
					// 返回 -1 代表这个用户名，在已经有的数据里不存在。
					int index = nameIsExist(new.names);
					if(index == -1){
						puts("请输入新密码：");
						scanf(" %s" , new.passwords);
						// 调用我们自己写的，新增用户的函数。
						addUser(new.names, new.passwords);
					}else{
						puts("对不起，用户名已经存在！");
					}
					break;
			case 2:
					puts("请输入登录用户名:");
					scanf("%s",login.names);
					puts("请输入登录用户密码:");
					scanf("%s",login.passwords);
						
					int f = loginUser(login.names,login.passwords);
							
					
					if(f>0)
					{
						if( strcmp( userdata[f].loginTime , "") != 0 ){
							printf("上次登录时间是：%s \n", userdata[f].loginTime);
						}else 
						{
							puts("---- 这是你第一次登录 ---");
							printf("初始时间是：%s \n", userdata[0].loginTime);
						}
						char *t = getTime();
						// 把当前时间，设置进用户的数据里					
						strcpy( userdata[f].loginTime, t );
						
						int op;
						while(true)
						{
							puts("请选择:    1.显示所有用户    2.新增用户    3.修改用户    4.删除用户    5.退出");
							// 正常返回 1， 不正常返回 0
							int result = scanf(" %d", &op);
							
							if(!result){
								// 处理掉异常： 如果scanf出现了异常，我们不断地调用getchar()清空缓冲区。
								while( getchar() != '\n' ){ }
								continue;
							}
										
							printf("op-------->%d\n",op);
							if(op==1)
							{
								displayUser();
							}else if(op==2)
							{
								puts("请输入新用户名:");
								scanf("%s",new.names);
								// 返回 -1 代表这个用户名，在已经有的数据里不存在。
								int index = nameIsExist(new.names);
								if(index == -1){
									puts("请输入新密码：");
									scanf(" %s" , new.passwords );
									// 调用我们自己写的，新增用户的函数。
									addUser(new.names, new.passwords);
								}else{
									puts("对不起，用户名已经存在！");
								}
							}else if(op==3)
							{
								puts("请输入修改前的用户名:");
								scanf("%s",modifyBefore.names);
								int f =nameIsExist(modifyBefore.names);
								if(f>=0)
								{
									puts("请输入修改后的用户名:");
									scanf("%s",modifyAfter.names);
									puts("请输入修改前的密码:");
									scanf("%s",modifyBefore.passwords);
									int z =passwodrVerify(modifyBefore.passwords,f);
									if(z)
									{
										puts("请输入修改后的密码:");
										scanf("%s",modifyAfter.passwords);
										int x =modifyUser(modifyAfter.names,modifyAfter.passwords,f);
										if(x)
										{
											puts("用户名修改成功！");
										}else
										{
											puts("修改失败！");
										}	
									}else
									{
										puts("对不起，密码错误！");
									}
								}else 
								{
									puts("对不起，用户名不存在！");
								}			
							}else if(op==4)
							{	
								puts("请输入想要删除的用户名");
								scanf("%s",delete.names);
								int f=nameIsExist(delete.names);
								
								if(f<0)
								{
									puts("-----对不起，想要删除的用户不存在！-----");
								}else
								{
									puts("请输入用户密码:");
									scanf("%s",delete.passwords);
									int z=passwodrVerify(delete.passwords,f);
									if(z)
									{
										int x =deleteUser(f);
										if(x)
										{
											puts("删除成功！");
											if(f<length/2)
											{
												deleteSpace(userdata);
											}
										}else
										{
											puts("删除失败！");
										}
									}else
									{
										puts("对不起，密码错误！");
									}
												
								}
							}else if(op==5)
							{
								break;
							}else 
							{
								puts("-----对不起，请输入正确的选项！-----");
							}	
						}
									
					}else if(f<0)
					{
						puts("-----username  error!-----");
					}else
					{
						puts("-----password error!-----");
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
	
	wn_system();
    
    return 0;
}

