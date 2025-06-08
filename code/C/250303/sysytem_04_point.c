/***************************************************
# File Name:    sysytem.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 11:51:48 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool f=true;
	//登录内的操作	
int op;

//定义用户数据结构体
typedef struct UserData
{
	char id[32];
	char names[32];//存放多个用户名，此处使用一维数组存放单个用户名，需要存放多个用户时可以使用结构体数组，不适用结构体时使用二维数组
	char passwords[32];//存放多个用户密码
	int age;
	long tel;
	char address[32];
	
}UserData;

//定义用户结构体类型的变量，并初始化用户数据
UserData userdata[10] =
{
	{.id={"wnno.0001"}, .names={"admin"}, .passwords={"1234"}, .age=20, .tel=13246579811, .address={"南京江宁888号"}},
	{.id={"wnno.0002"}, .names={"jacky"}, .passwords={"12345"}, .age=21, .tel=18957649822, .address={"上海皇甫88号"}},
	{.id={"wnno.0003"}, .names={"rosey"}, .passwords={"123456"}, .age=21, .tel=16446579833, .address={"北京昌平99号"}}
};

int length=sizeof(userdata)/sizeof(userdata[0]);//已存在的用户个数
UserData login={0};//登录信息
UserData new={0};//注册信息
UserData modifyBefore={0};//修改前信息
UserData modifyAfter={0};//修改后信息
UserData delete={0};//删除信息
//验证信息
char verifyPassword[32];

//重名判断,用isExist()函数代替
//int chongming();
//判断用户名是否存在，并返回索引//index>=0时表示已经有用过此用户名
int nameIsExist(char userName[]);
//验证用户密码是否正确，并返回
bool passwodrVerify(char verifyPassword[],int index);
//判断是userdata[].names数组是否存在空间，并返回索引//index>=0时有空间
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
		if(strcmp(userdata[i].names,userName)==0)
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
//注册流程
void addUser(char userName[],char password[])
{										
	//int temp =chongming();
										
	int index=nameIsExist(userName);//index<0表示没有使用过
	int dex=spaceIsExist();//dex>=0表示有空间
	if(dex>=0)//注册前先判断输入的用户名是否已使用
	{
		strcpy(userdata[dex].names,userName);
		strcpy(userdata[dex].passwords,password);
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
		if(strcmp(userdata[i].names,"")!=0)
		{
			//	可以使用指针->
			printf("用户名：%s，密码：%s \n",userdata[i].names,userdata[i].passwords);
		}
	}
}

//登录流程
int loginUser(char userName[],char password[])
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
int modifyUser(char modifyName[],char modifyPassword[],int index)
{
			strcpy(userdata[index].names,modifyName);
			strcpy(userdata[index].passwords,modifyPassword);
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
		temp=strcmp(userdata[i].names,new.names);
		
		if(temp==0)
		{
			break;
		}
	}
	return temp;
}
*/
