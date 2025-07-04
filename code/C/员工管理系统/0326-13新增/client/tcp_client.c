/***************************************************
# File Name:    system.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月20日 星期四 21时55分11秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/socket.h>
//用于互联网地址族，包括 sockaddr_in 结构和 IP 地址定义。
#include <netinet/in.h>
#include <unistd.h>

#include "cJSON.h"
#include "json.h"
#include "data.h"			//引入系统所需要的结构体
#include "sysOpera.h"		//引入用户输入验证
#include "tcp_client.h"

//#include "tcp_server.h"
//#include "common.h"

//创建客户端连接并发送用户操作
Employee * create_client(OP op, Node * head,int *employee_quantity){
	//1.创建套接字
	//第三个参数:为0代表自动选择
	 int client_fd = socket(AF_INET, SOCK_STREAM, 0); 
	 if(client_fd <0){
	 	perror("创建套接字失败");
	 	close(client_fd);
	 	exit(EXIT_FAILURE);
	 }	 
	 //2.创建服务器端口结构体并设置端口协议，地址等信息
	 struct sockaddr_in server_addr = {0};	//创建空地址结构体
	 server_addr.sin_family = AF_INET;	//设置协议为ipv4
	 server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);	//127.0.0.1代表客户端本机
	 server_addr.sin_port = htons(SERVER_PORT);	//将主机字节序（host byte order）的16位整数转换为网络字节序（network byte order）
	 
	//3.连接
	if( connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr ))<0){
		perror("连接失败");
	 	close(client_fd);
	 	exit(EXIT_FAILURE);
	}
	puts("连接成功");
	//向客户端发送Employee表的操作请求，并接收返回的新Employee表(结构体数组)
	Employee *employee = client_write( client_fd, op ,head, employee_quantity);
	close(client_fd);	
	return employee;
}	

//客户端通信发送用户Employee的操作与用户数据
Employee* client_write(int client_fd ,OP op,Node *head, int *employee_quantity){
	//向服务器发送操作信息
	//将枚举转为字符串，然后进行发送（字符串不用考虑字节序问题）
	char *op_str = op_to_string( op );
	//memset(json_buf,0,sizeof(op_buf));
	if(write(client_fd, op_str, strlen(op_str)) < 0){
		perror("向服务端发送操作失败！\n");
	}
	Employee *p =NULL;
	//操作者为管理员
	if(head == NULL || head->data.roles == 0){	
	puts("向服务端发送操作");
		switch(op){
			//增Employee操作
			case ADD_EMPLOYEE:	puts("增Employee操作");	p = clientAddEmployee(head,client_fd);return p;
			//删Employee操作	 
			case DELETE_EMPLOYEE:puts("删Employee操作");p = clientDeleteEmployee(head,client_fd);return p;
			//改Employee操作
			case UPDATE_EMPLOYEE:puts("改Employee操作");p = clientAdminUpdate(head,client_fd);return p;
			//查Employee操作,
			case INQUR_EMPLOYEE:	//puts("查Employee操作");//查询并返回整张表所有成员信息
			case DESC_SALARY:	//puts("查工资降序操作");//按工资降序显示员工信息
			case ASC_AGE:	//puts("查年龄升序操作");//按年龄升序显示员工信息 
			case GENDER_BY_DEPARTEMNT:	//puts("查男女人数操作");//显示指定部门的男女员工人数
			case AVG_SALARY_BY_DEPARTMENT:	//puts("查平均工资操作");//统计每个部门的平均工资并显示
			case COUNT_BY_TITLE:	//puts("查管理基层操作");//统计管理层和基层员工人数并显示
			p = clientInqurEmployee(client_fd,employee_quantity);return p;			
			default:puts("op error!");return NULL;	
		}
	}else if(head->data.roles == 1){
		//操作为员工,只有查询和修改功能
		switch(op){
			//改Employee操作
			case UPDATE_EMPLOYEE:puts("员工改Employee操作");p = clientEmployeeUpdate(head, client_fd);return p;
			//查Employee操作-------员工从链表当中查询
			//case INQUR_EMPLOYEE:puts("员工查Employee操作");p = clientInqurEmployee(client_fd,employee_quantity);return p;			
			default:puts("op error!");return NULL;	
		}
	}
	return NULL;
}

//查询数据库，根据返回的表，遍历查询用户名是否存在，存在则继续判断密码是否正确
bool EmployeeName_is_exist( int client_fd, char *name ){
	//应先查询数据库，根据返回的表，遍历查询用户名是否存在，存在则继续判断密码是否正确
	int employee_quantity= 0;
	Employee *p = clientInqurEmployee(client_fd,&employee_quantity);
	//循环遍历数据表结构体数组是否存在该用户
	for(int i=0; i<employee_quantity; i++){
		if(strcmp(p[i].name ,name) != 0){
			printf("用户名不存在 \n");
			return false;
		}else{
			printf("找到该用户 \n");
			return true;
		}
	}	
	return false;		
}

//查询数据库，根据返回的表，遍历查询用户名是否存在，存在则继续判断密码是否正确
bool EmployeePassword_is_exist(int client_fd, char *password){
	//应先查询数据库，根据返回的表，遍历查询用户名是否存在，存在则继续判断密码是否正确
	int employee_quantity= 0;
	Employee *p = clientInqurEmployee(client_fd,&employee_quantity);
	//循环遍历数据表结构体数组判断该用户密码是否正确
	for(int i=0; i<employee_quantity; i++){
		if(strcmp(p[i].password ,password) != 0){
			printf("用户密码错误 \n");
			return false;
		}else{
				printf("密码正确 \n");
				return true;
		}
	}
	return false;
}

//更新管理员用户操作-----增操作
Employee *clientAddEmployee(Node *head,int client_fd){
	int gets_info =0;
	//查询数据库，根据返回的表，遍历查询用户名是否存在，不存在则继续判断密码是否正确
	Employee employee = {0};
	
	printf("请输入用户名：\n");
	int result = scanf("%s",employee.name);	
	if(!result){
		// 处理掉异常： 如果scanf出现了异常，我们不断地调用getchar()清空缓冲区。
		while( getchar() != '\n' ){ continue;}	
	}
	Node * cur = search_node(head, employee.name);
	if(cur != NULL){
		printf("用户名已存在");
		return NULL;
	}	
		printf("请输入密码：\n");
		result = scanf("%s",employee.password);	
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}
		printf("请输入年龄：\n");
		int age=0;
		result =scanf("%d",&age);
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}
		employee.age =age;
		
		printf("请输入工资：\n");
		float salary=0;
		result =scanf("%f",&salary);
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}
		employee.salary = salary;

		
	while(!gets_info){
		printf("请输入性别（1：MALE	2：FEMALE）\n");
		int choice =0;
		result = scanf("%d",&choice);
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}
		if(choice == 1){
			Gender g =MALE;
			employee.genders = g;
		}else if(choice == 2){
			Gender g =FEMALE;
			employee.genders = g;
		}else{
			printf("请输入“1”或“2”选择性别！");
			break;
		}

		printf("请输入部门：（1：SALES	2：MARKETING		3：AFTER_SALE）\n");
		choice =0;
		result = scanf("%d",&choice);
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}		
		if(choice == 1){
			Department d = SALES;
			employee.departments = d;
		}else if(choice == 2){
			Department d = MARKETING;
			employee.departments = d;
		}else if(choice == 3){
			Department d = AFTER_SALE;
			employee.departments = d;
		}else{
			printf("请输入正确的选项！");
			break;
		}
		
		printf("请输入职位：（1：MANAGER		2：CAPTAIN		3：SALES_WORKER		4：MARKETING_WORKER		5：AFTER_SALE_WORKER）\n");
		result = scanf("%d",&choice);
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}			
		if(choice ==  1){
			Title t = MANAGER;
			employee.titles = t;
		}else if(choice == 2){
			Title t = CAPTAIN;
			employee.titles = t;
		}else if(choice == 3){
			Title t = SALES_WORKER;
			employee.titles = t;
		}else if(choice == 4){
			Title t = MARKETING_WORKER;
			employee.titles = t;
		}else if(choice == 5){
			Title t = AFTER_SALE_WORKER;
			employee.titles = t;
		}else{
			printf("请输入正确的选项！");
			break;
		}
		
		
		printf("请输入角色：（1：ROLE_ADMIN	2：ROLE_EMPLOYEE）\n");
		choice =0;
		result = scanf("%d",&choice);
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}
		if(choice == 1){
			Role r =ROLE_ADMIN;
			employee.roles = r;
		}else if(choice == 2){
			Role r =ROLE_EMPLOYEE;
			employee.roles = r;
		}else{
			printf("请输入“1”或“2”选择角色！");
			break;
		}
		
		gets_info =1;
	}
	//向服务器发送操作信息
	//usleep(500000);//模拟间隔发送
	//通过json先转换用户信息
	int count=1;
	char* json_str = employees_to_json( &employee ,count);
	//向服务器发送用户信息
	if(write(client_fd, json_str, strlen(json_str)) < 0){
		perror("向服务端发送用户信息失败！\n");
	}	
	//读取服务端数据，并将得到的数据转换为Employee结构体数组
	int employee_quantity= 0;
	Employee *p = client_read(client_fd,&employee_quantity);
	return p;
}
//跟新管理员用户操作-----删操作
Employee *clientDeleteEmployee(Node * head,int client_fd){
	Employee employee = {0};
	printf("请输入用户名：\n");
	int result = scanf("%s",employee.name);	
	if(!result){
		// 处理掉异常： 如果scanf出现了异常，我们不断地调用getchar()清空缓冲区。
		while( getchar() != '\n' ){ continue;}	
	}
	Node * cur = search_node(head, employee.name);
	if(cur == NULL){
		printf("用户名不存在");
		return NULL;
	}	
	
	//向服务器发送操作信息
	//通过json先转换用户信息
	char* json_str = Employee_to_json( &employee );
	//向服务器发送用户信息
	if(write(client_fd, json_str, strlen(json_str)) < 0){
		perror("向服务端发送用户信息失败！\n");
	}	
	//读取服务端数据，并将得到的数据转换为Employee结构体数组
	int employee_quantity= 0;
	Employee *p = client_read(client_fd,&employee_quantity);
	return p;
}
//跟新管理员用户操作-----改操作
Employee *clientAdminUpdate(Node * head,int client_fd){
	char* json_str ;		//通过json先转换用户信息
	int gets_info = 0;
	Employee employee = {0};	
	//操作为修改需要输入修改用户的用户名，查询数据库并判断用户是否存在
	printf("请输入用户名：\n");
	int result = scanf("%s",employee.name);	
	if(!result){
		// 处理掉异常： 如果scanf出现了异常，我们不断地调用getchar()清空缓冲区。
		while( getchar() != '\n' ){ continue;}	
	}
	Node * cur = search_node(head, employee.name);
	if(cur == NULL){
		printf("用户名不存在");
		return NULL;
	}	
	while(!gets_info){
		printf("请输入新用户名：\n");
		result = scanf("%s",employee.name);	
		if(!result){
			while( getchar() != '\n' ){ continue;}	
		}
		printf("请输入密码：\n");
		result = scanf("%s",employee.password);	
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}
		printf("请输入年龄：\n");
		int age=0;
		result =scanf("%d",&age);
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}
		employee.age =age;
		
		printf("请输入工资：\n");
		float salary=0;
		result =scanf("%f",&salary);
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}
		employee.salary = salary;

		printf("请输入性别（1：MALE	2：FEMALE）\n");
		int choice =0;
		result = scanf("%d",&choice);
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}
		if(choice == 1){
			Gender g =MALE;
			employee.genders = g;
		}else if(choice == 2){
			Gender g =FEMALE;
			employee.genders = g;
		}else{
			printf("请输入“1”或“2”选择性别！");
			break;
		}

		printf("请输入部门：（1：SALES	2：MARKETING		3：AFTER_SALE）\n");
		choice =0;
		result = scanf("%d",&choice);
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}		
		if(choice == 1){
			Department d = SALES;
			employee.departments = d;
		}else if(choice == 2){
			Department d = MARKETING;
			employee.departments = d;
		}else if(choice == 3){
			Department d = AFTER_SALE;
			employee.departments = d;
		}else{
			printf("请输入正确的选项！");
			break;
		}
		
		printf("请输入职位：（1：MANAGER		2：CAPTAIN		3：SALES_WORKER		4：MARKETING_WORKER		5：AFTER_SALE_WORKER）\n");
		result = scanf("%d",&choice);
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}			
		if(choice ==  1){
			Title t = MANAGER;
			employee.titles = t;
		}else if(choice == 2){
			Title t = CAPTAIN;
			employee.titles = t;
		}else if(choice == 3){
			Title t = SALES_WORKER;
			employee.titles = t;
		}else if(choice == 4){
			Title t = MARKETING_WORKER;
			employee.titles = t;
		}else if(choice == 5){
			Title t = AFTER_SALE_WORKER;
			employee.titles = t;
		}else{
			printf("请输入正确的选项！");
			break;
		}
		
		
		printf("请输入角色：（1：ROLE_ADMIN	2：ROLE_EMPLOYEE）\n");
		choice =0;
		result = scanf("%d",&choice);
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}
		if(choice == 1){
			Role r =ROLE_ADMIN;
			employee.roles = r;
		}else if(choice == 2){
			Role r =ROLE_EMPLOYEE;
			employee.roles = r;
		}else{
			printf("请输入“1”或“2”选择角色！");
			break;
		}
		
		gets_info =1;
	}
	
	//通过json先转换用户信息
	json_str = Employee_to_json( &employee );
	//向服务器发送用户信息
	if(write(client_fd, json_str, strlen(json_str)) < 0){
		perror("向服务端发送用户信息失败！\n");
	}	
	//读取服务端数据，并将得到的数据转换为Employee结构体数组
	int employee_quantity= 0;
	Employee *p = client_read(client_fd,&employee_quantity);
	return p;
}
//员工修改密码操作
Employee *clientEmployeeUpdate(Node * head,int client_fd){
	char* json_str ;		//通过json先转换用户信息
	int gets_info =0;
	Employee employee = {0};
	//操作为修改需要输入修改用户的用户名，查询数据库并判断用户是否存在
	printf("请输入用户名：\n");
	int result = scanf("%s",employee.name);	
	if(!result){
		// 处理掉异常： 如果scanf出现了异常，我们不断地调用getchar()清空缓冲区。
		while( getchar() != '\n' ){ continue;}	
	}
	Node * cur = search_node(head, employee.name);
	if(cur == NULL){
		printf("用户名不存在");
		return NULL;
	}	
	while(!gets_info){
		printf("请输入密码：\n");
		result = scanf("%s",employee.password);	
		if(!result){
			while( getchar() != '\n' ){ continue;}
		}	
		gets_info =1;
	}
	//通过json先转换用户信息
	json_str = Employee_to_json( &employee );
	//向服务器发送用户信息
	if(write(client_fd, json_str, strlen(json_str)) < 0){
		perror("向服务端发送用户信息失败！\n");
	}	
	//读取服务端数据，并将得到的数据转换为Employee结构体数组
	int employee_quantity= 0;
	Employee *p = client_read(client_fd,&employee_quantity);
	return p;
}
//查询Employee表并返回结构体数组
Employee *clientInqurEmployee(int client_fd,int *employee_quantity){
	//读取服务端数据，并将得到的数据转换为Employee结构体数组
	//puts("查前");
	Employee *p = client_read(client_fd,employee_quantity);
	if(p == NULL){
		printf("clientInqurEmployee查询后返回的结构体为空！");
	}
	/*
	for(int i=0;i<8;i++){
	printf("sql查询后:第%d次循环",i);
		printf(" %d: %s, %s, %d, %.1f, %s, %s, %s, %s\n",
			p[i].id,
			p[i].name,
			p[i].password,
			p[i].age,
			p[i].salary,
			gender_to_string(p[i].genders),
			department_to_string(p[i].departments),
			title_to_string(p[i].titles),
			role_to_string(p[i].roles));
		
	}
	*/
	//puts("查后");
	return p;
}


//接收服务端发送的数据表，并转为Employee结构体数组
Employee * client_read(int client_fd ,int *employee_quantity){
	char json_str[BUFF_SIZE*2];			//服务器返回数据的缓冲区
	int count = 0;			//用于判断服务器是否返回数据
	//每次接受信息之间，应该先清空数组中的缓存
	memset(json_str,0,BUFF_SIZE*2);
	//count用于判断接收服务器的消息
	//char buffer[4096];
	//int total_received = 0;
	//处理可能导致接收数据不完整
	puts("读服务端前");
	//多层调用Employee_quantity，在这里改变值，得到结构体数组长度
	read(client_fd,employee_quantity,sizeof(employee_quantity));
	//网络字节序转为主机字节序,得到结构体数组长度
	*employee_quantity = ntohl(*employee_quantity);
	//读取传来的josn数据（包含查询的用户表）
	count =	read(client_fd,json_str,sizeof(json_str)-1);
	puts("读服务端后");	
	//接收服务器消息，count大于0说明客户端一直在发送信息
	if(count >0){
		//接收成功则将服务器返回的json字符串解析为Employee结构体数组
		printf("服务器说：%s\n",json_str);
		//得到结构体数组
		Employee *p = malloc(sizeof(Employee*) * (*employee_quantity) );
		memset(p,0,sizeof(Employee*) * (*employee_quantity));
		p = json_to_employees( json_str, &count);
		if(p == NULL){
			printf("客户端json_to_employees失败。\n");
			return NULL;
		}
		/*
		for(int i=0; i< count; i++){
		printf("client_read ------:%d\n",i);
		printf("%d: %s, %s, %d, %.1f, %s, %s, %s, %s\n",
			p->id,
			p->name,
			p->password,
			p->age,
			p->salary,
			gender_to_string(p->genders),
			department_to_string(p->departments),
			title_to_string(p->titles),
			role_to_string(p->roles));
		}
		*/
		puts("client_read结束---------------");
		/*
		puts("得到数组");
		//循环遍历数据表结构体数组判断该用户密码是否正确
		for(int i=0; i<Employee_quantity; i++){
			printf("数据库操作后返回结构体数组：\n%d %s %s\n",p[i].id,p[i].name,p[i].password);
		}
		*/
		return p;	
	}else if(count == 0){
		//count等于0说明服务器正常退出
		puts("服务器关闭了。");	
		return NULL;
	}else{
		//count小于0说明读取服务器信息出错
		perror("读取服务器信息错误");
		return NULL;	
	}	
}

/*
int main(int argc, char *argv[]){
	client_write();
	//readFromServer();
	return 0;
	
}
*/






