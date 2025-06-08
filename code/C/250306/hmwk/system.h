/***************************************************
# File Name:    sysytem.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 11:51:48 AM CST
****************************************************/

#ifndef SYSTEM_H
#define SYSTEM_H


int size=6;//用户容量（可以容纳的用户上限总数量）
int length=0;//用户数量（当前用户个数）
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
	char loginTime[128];
	
}UserData;

UserData *userdata;//用户信息结构体指针

UserData login={0};//登录信息
UserData new={0};//注册信息
UserData modifyBefore={0};//修改前信息
UserData modifyAfter={0};//修改后信息
UserData delete={0};//删除信息


char *getTime();//获取当前时间

char verifyPassword[32];//验证密码

void initUserData();//初始化用户数据
//重名判断,用isExist()函数代替
//int chongming();
//判断用户名是否存在，并返回索引//index>=0时表示已经有用过此用户名
int nameIsExist(char userName[]);
//验证用户密码是否正确，并返回
bool passwodrVerify(char verifyPassword[],int index);
//判断是userdata[].names数组是否存在空间，并返回索引//index>=0时有空间
int spaceIsExist();

void wn_system();
void addUser(char *userName,char *password);//新增用户
UserData* addSpace();//增加用户空间
int loginUser(char *userName,char *password);//用户登录
bool deleteUser(int index);//删除用户
UserData* deleteSpace();//(UserData userName[]);//删除用户空间
int modifyUser(char *modifyName,char *modifyPassword,int index);//修改用户名或密码

void displayUser();

void toString(UserData *u);//显示用户信息



#endif


