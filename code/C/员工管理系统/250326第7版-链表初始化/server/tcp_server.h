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

//取出客户端传来的用户数据，并使用sql执行新增Admin操作
void serverAddAdmin(Admin  *p);
//取出客户端传来的用户数据，并使用sql执行删除Admin操作
void clientDeleteAdmin(Admin  *p);
//取出客户端传来的用户数据，并使用sql执行修改Admin操作
void clientUpdateAdmin(Admin  *p);
//使用sql执行查询Admin表并返回结构体数组,查询后返回结构体数组的大小
Admin * clientInqurAdmin(int *Admin_quantity);
//接收线程
//接收用户发送的请求，并使用write返回数据库查询结果
void *server_read(void *args);
//处理用户发送的请求，并返回数据库查询结果
void server_write( int client_fd, char *op_buf, char *json_buf);




#endif






