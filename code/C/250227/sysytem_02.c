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
int length=sizeof(names)/sizeof(names[0]);//已存在的用户名个数

//登录信息
char loginName[32];
char loginPassword[32];
//注册信息
char newName[32];
char newPassword[32];
//修改信息
char modifyBeforeName[32];
char modifyBeforePassword[32];
char modifyAfterName[32];
char modifyAfterPassword[32];
//删除信息
char deleteName[32];
char deletePassword[32];
//验证信息
char verifyPassword[32];

bool f=true;
//登录内的操作	
int op;

//重名判断,用isExist()函数代替
//int chongming();
//判断用户名是否存在，并返回索引//index>=0时表示已经有用过此用户名
int nameIsExist(char userName[]);
//验证用户密码是否正确，并返回
bool passwodrVerify(char verifyPassword[],int index);
//判断是names数组是否存在空间，并返回索引//index>=0时有空间
int spaceIsExist();

void system();
void addUser(char userName[],char password[]);//新增用户
int loginUser(char userName[],char password[]);//用户登录
bool deleteUser(int index);//删除用户
int modifyUser(char modifyName[],char modifyPassword[],int index);//修改用户名或密码

void displayUser();

//判断输入的用户名是否存在，并返回索引
int nameIsExist(char userName[])
{
	//循环遍历数组，匹配需要的值
	int index=-1;//默认输入的用户名不存在
	for(int i=0;i<length;i++)
	{
		if(strcmp(names[i],userName)==0)
		{
			index=i;//index>=0时表示已经有用过此用户名
			break;
		}
	}
	return index;
}
//验证用户密码是否正确，并返回
bool passwodrVerify(char verifyPassword[],int index)
{
	//循环遍历数组，匹配需要的值
		if(strcmp(passwords[index],verifyPassword)==0)
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
		if(strcmp(names[i],"")==0)//比较数组中字符串与空，看是否有空间可以存放新用户名
		{
			index=i;//index>=0时有空间
			break;
		}
	}
	return index;
}
//注册流程
void addUser(char userName[],char password[])
{										
	//int temp =chongming();
										
	int index=nameIsExist(userName);//index<0表示没有使用过
	int dex=spaceIsExist();//dex>=0表示有空间
	if(dex>=0)//注册前先判断输入的用户名是否已使用
	{
		strcpy(names[dex],userName);
		strcpy(passwords[dex],password);
		puts("-----注册成功-----");		
	}else 
	{
		puts("-----对不起，数据已经满了-----");
	}	   
}

//登录显示所有已存在的用户名和密码
void displayUser()
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
int loginUser(char userName[],char password[])
{					
	int index =nameIsExist(userName);
	if(index>=0)
	{
		if(strcmp(passwords[index],password)==0)
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
int modifyUser(char modifyName[],char modifyPassword[],int index)
{
			strcpy(names[index],modifyName);
			strcpy(passwords[index],modifyPassword);
}

//删除流程
bool deleteUser(int index)
{	
	if(index>=0)
	{
		strcpy(names[index],"");
		strcpy(passwords[index],"");
		return true;
	}else
	{
		return false;
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
					puts("请输入新用户名:");
					scanf("%s",newName);
					// 返回 -1 代表这个用户名，在已经有的数据里不存在。
					int index = nameIsExist(newName);
					if(index == -1){
						puts("请输入新密码：");
						scanf(" %s" , newPassword );
						// 调用我们自己写的，新增用户的函数。
						addUser(newName, newPassword);
					}else{
						puts("对不起，用户名已经存在！");
					}
					break;
			case 2:
					puts("请输入登录用户名:");
					scanf("%s",loginName);
					puts("请输入登录用户密码:");
					scanf("%s",loginPassword);
							
					int f = loginUser(loginName,loginPassword);
					//printf("%d \n",f);
					
					if(f>0)
					{
						int op;
						while(true)
						{
							puts("请选择:    1.显示所有用户    2.新增用户    3.修改用户    4.删除用户    5.退出");
							scanf("%d",&op);
										
							printf("op-------->%d\n",op);
							if(op==1)
							{
								displayUser();
							}else if(op==2)
							{
								puts("请输入新用户名:");
								scanf("%s",newName);
								// 返回 -1 代表这个用户名，在已经有的数据里不存在。
								int index = nameIsExist(newName);
								if(index == -1){
									puts("请输入新密码：");
									scanf(" %s" , newPassword );
									// 调用我们自己写的，新增用户的函数。
									addUser(newName, newPassword);
								}else{
									puts("对不起，用户名已经存在！");
								}
							}else if(op==3)
							{
								puts("请输入修改前的用户名:");
								scanf("%s",modifyBeforeName);
								int f =nameIsExist(modifyBeforeName);
								if(f>=0)
								{
									puts("请输入修改后的用户名:");
									scanf("%s",modifyAfterName);
									puts("请输入修改前的密码:");
									scanf("%s",modifyBeforePassword);
									int z =passwodrVerify(modifyBeforePassword,f);
									if(z)
									{
										puts("请输入修改后的密码:");
										scanf("%s",modifyAfterPassword);
										int x =modifyUser(modifyAfterName,modifyAfterPassword,f);
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
								scanf("%s",deleteName);
								int f=nameIsExist(deleteName);
								
								if(f<0)
								{
									puts("-----对不起，想要删除的用户不存在！-----");
								}else
								{
									puts("请输入用户密码:");
									scanf("%s",deletePassword);
									int z=passwodrVerify(deletePassword,f);
									if(z)
									{
										int x =deleteUser(f);
										if(x)
										{
											puts("删除成功！");
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
	
	system();
    
    return 0;
}

/*
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
*/
