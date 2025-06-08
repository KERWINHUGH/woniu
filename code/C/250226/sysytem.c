/***************************************************
# File Name:    sysytem.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 11:51:48 AM CST
****************************************************/

#include <stdio.h>
 
 void system()
{
	puts("欢迎使用蜗牛门禁系统！");
	//int num;
	//char name[32];	
	//int temp =1;
	
	char names[10][32]={"admin"};
	char password[10][32]={"1234"};
	
	bool f=true;
		
	int length=sizeof(name)/sizeof(name[0]);
	
	int op;
	

	//int n_t,p_t;	
		
	while(f)
	{

		puts("请选择需要的操作：1：注册    2：登录    3：退出");
		
		scanf("%d",&op);

		switch(op)
		{
			case 1:
					char newName[32];
					char newPassword[32];
									
					puts("请输入登录用户名:");
					scanf("%s",loginName);
					puts("请输入登录用户密码:");
					scanf("%s",loginPassword);	
									
					int index=-1;
					//要先选中可以写入数据的索引
					for(int i=0;i<length;i++)
					{
						if(strcmp(names[i],"")==0)
						{
							index=i;
							break;
						}
					}			
					if(index>=0)
					{
						strcpy(names[index],newname);
						strcpy(passwords[index],newpassword);
						puts("-----注册成功-----");
					}
					else 
					{
					puts("-----对不起，数据已经满了-----");
					}		
				//puts("请输入新用户名");
				//scanf("%s",names);

				//for(int i=0;i<length;i++)
				//{
					//temp=strcmp(names,&name[i]);
					//printf("names:%s \n",names);
					//puts("---------------------");
					//printf("name[i]:%s \n",name[i]);
					//printf("temp:%d \n",temp);
					//if(temp==0)
					//{
						//puts("用户名已使用，请重新输入！");
						//break;
					//}else
					//{
						//for(int i=0;i<length;i++)
						//{
						//	name[i]=names[i];
						//}				
					//}
				//}
				//if(temp)
				//{
					//puts("请输入新用户密码");
					//scanf("%s",password);		
					//puts("注册成功！");		
				//}
				
				break;
			case 2:
				char loginName[32];
				char loginPassword[32];
				
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
							for(int i=0;i<length;i++)
							{
								if(strcmp(names[i],loginName)==0&&strcmp(passwords[i],loginPassword)==0)
								{
									printf("用户名：%s，密码：%s \n",names[i],passwords[i]);
								}
							}
						}else if(op==2)
							{
									char newName[32];
									char newPassword[32];
									
									puts("请输入登录用户名:");
									scanf("%s",loginName);
									puts("请输入登录用户密码:");
									scanf("%s",loginPassword);	
									
									int index=-1;
									//要先选中可以写入数据的索引
									for(int i=0;i<length;i++)
									{
										if(strcmp(names[i],"")==0)
										{
										index=i;
										break;
										}
									
										if(index>=0)
										{
											strcpy(names[index],newname);
											strcpy(passwords[index],newpassword);
											puts("-----注册成功-----");
										}
										else 
										{
											puts("-----对不起，数据已经满了-----");
										}		
									}
							}else if(op==3)
							{
								
							}else if(op==4)
							{
								
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
				//n_t = strcmp(name,loginName);
				//p_t = strcmp(password,loginPassword);

				//if(n_t)
				//{
					//puts("username error!");
				//}else if(p_t)
				//{
					//puts("password error!");
				//}else if(!n_t &&!p_t)
				//{
				//	puts("login success!");
				//} 

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
