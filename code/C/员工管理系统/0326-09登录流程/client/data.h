/***************************************************
# File Name:    emploee_system.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月23日 星期日 17时16分10秒
****************************************************/
#ifndef DATA_H
#define DATA_H

#define USER_LENGTH			50			//定义用户名和用户密码数组长度
#define TIME_STAMP			60			//定义日志时间戳数组长度
#define OPERATION			100			//定义日志操作类型数组长度
#define TRUE				1
#define FALSE				0

//定义客户端向服务器发送的sql操作枚举，根据OP选择对应的operaion数组元素，将对应指令传到服务器
typedef enum {
	//操作管理员
	ADD_EMPLOYEE,			//增加管理员---0
	DELETE_EMPLOYEE,		//删除管理员---1
	UPDATE_EMPLOYEE,		//修改管理员---2
	INQUR_EMPLOYEE,		//查询管理员---3
	EMPLOYEE_UNKNOWN
}OP;
//定义客户端向服务器发送的sql操作，与OP枚举对应
//extern const char *op_str[] ;

//枚举性别
typedef	enum {
		MALE,				//- 男性
		FEMALE,				//- 女性
		GENDER_UNKNOWN
}Gender;					//- 性别  使用枚举  - `MALE`、`FEMALE`
//const char * gender_str[] = { "MALE","FEMALE" };
//枚举部门
typedef	enum {
		SALES,				//- 销售部
		MARKETING,			//- 市场部
		AFTER_SALE,			//- 售后部
		DEPT_UNKNOWN
}Department;				//- 部门  - `SALES`、`MARKETING`、`AFTER_SALE`	
//const char * department_str[] = { "SALES","MARKETING","AFTER_SALE" };
//枚举职位
typedef	enum {
		MANAGER,			//- 经理
		CAPTAIN,			//- 组长
		SALES_WORKER,		//- 销售员
		MARKETING_WORKER,	//- 市场员工
		AFTER_SALE_WORKER,	//- 售后员
		TITLE_UNKNOWN
}Title;						//- 职位  - `MANAGER`、`SALES`、`CAPTAIN`、`WORKER`、`AFTER_SALE`
//const char * title_str[] = { "MANAGER","SALES_WORKER","CAPTAIN","MARKETING_WORKER","AFTER_SALE_WORKER" };
//枚举角色
typedef enum {
		ROLE_ADMIN,			//- 管理员
		ROLE_EMPLOYEE,		//- 员工
		ROLE_UNKNOWN
}Role;						//- 角色  - Employee   employees	
//const char * role_str[] = { "role_Employee","role_employees" };

//定义管理员结构体
typedef struct Admin{
	int id;						//- 工号
	char name[USER_LENGTH];		//- 名字
	char password[USER_LENGTH];	//- 密码 
}Admin;

//定义员工结构体
typedef struct Employee{
	int id;						//- 工号
	char name[USER_LENGTH];		//- 名字
	char password[USER_LENGTH];	//- 密码 
	int age;					//- 年龄
	float salary;				//- 工资
	//枚举性别
	Gender genders;				//- 性别  使用枚举  - `MALE`、`FEMALE`
	//枚举部门
	Department departments;		//- 部门  - `SALES`、`MARKETING`、`AFTER_SALE`
	//枚举职位
	Title titles;				//- 职位  - `MANAGER`、`SALES`、`CAPTAIN`、`WORKER`、`AFTER_SALE`
	//枚举角色
	Role roles;					//- 角色  - Admin   employees
}Employee;
//定义日志结构体
typedef struct OperationLog{
	int id;						//- 工号
	char operation[OPERATION];	//- 操作内容
	char timestamp[TIME_STAMP];	//- 时间戳
	char username[USER_LENGTH];	//- 操作员用户名
}OperationLog;

char *op_to_string(OP op);								//枚举转字符串映射函数
OP string_to_op(const char *str);						//字符串转枚举映射函数
const char *gender_to_string(Gender gender);			//枚举转字符串映射函数
Gender string_to_gender(const char *str);				//字符串转枚举映射函数
const char *department_to_string(Department department);//枚举转字符串映射函数
Department string_to_department(const char *str);		//字符串转枚举映射函数
const char *title_to_string(Title title);				//枚举转字符串映射函数
Title string_to_title(const char *str);					//字符串转枚举映射函数
const char *role_to_string(Role role);					//枚举转字符串映射函数
Role string_to_role(const char *str);					//字符串转枚举映射函数


#endif


