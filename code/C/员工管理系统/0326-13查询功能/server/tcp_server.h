/***************************************************
# File Name:    system.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月20日 星期四 21时55分11秒
****************************************************/

#ifndef TCP_SERVER_H
#define TCP_SERVER_H 

#define SERVER_ADDR "127.0.0.1"		//定义服务器地址
#define SERVER_PORT 8080			//定义服务器端口号
#define BUFF_SIZE 1024				//定义缓冲区大小


// 公共函数声明
//发送数据时处理分包
/*
** 参数char* data：要发送的数据
** 参数len：要发送的json字符串长度
*/
void send_all(int sock, const char* data, size_t len);
int recv_all(int sock, char* buffer, size_t len);
// 解析嵌套数据包
void parse_combined_data(char* data, uint32_t total_len);
void send_combined_data(int sock, const char* str_a, const char* str_b);


//数据库操作
//取出客户端传来的用户数据，并使用sql执行新增Employee操作
void serverAddEmployee(Employee  *p);
//取出客户端传来的用户数据，并使用sql执行删除Employee操作
void serverDeleteEmployee(Employee  *p);
//取出客户端传来的用户数据，并使用sql执行修改Employee操作
void serverUpdateEmployee(Employee  *p);
//------查询------
//使用sql执行查询Employee表并返回结构体数组,查询后返回结构体数组的大小
Employee * serverInqurEmployee(int *Employee_quantity);
//使用sql执行查询Employee表并返回结构体数组------------**按工资降序显示员工信息**
Employee * descSalary(int *Employee_quantity);
//使用sql执行查询Employee表并返回结构体数组------------**按年龄升序显示员工信息
Employee * ascAge(int *Employee_quantity);
//取出客户端传来的用户数据-----------------**显示指定部门的男女员工人数
Employee *  genderByDepartment(Employee  *p,int *Employee_quantity);
//使用sql执行查询Employee表并返回结构体数组--------------统计每个部门的平均工资并显示
Employee * avgSalaryByDepartment(int *Employee_quantity);
//使用sql执行查询Employee表并返回结构体数组--------------**统计管理层和基层员工人数并显示**
Employee * countByTile(int *Employee_quantity);


//接收线程
//接收用户发送的请求，并使用write返回数据库查询结果
void *server_read(void *args);
//处理用户发送的请求，并返回数据库查询结果
void server_write( int client_fd, char *op_buf, char *json_buf);






#endif






