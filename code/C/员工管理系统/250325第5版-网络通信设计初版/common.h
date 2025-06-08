/***************************************************
# File Name:    common.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月25日 星期二 20时11分53秒
****************************************************/

#ifndef COMMON_H
#define COMMON_H


#define MAX_ADMINS 10
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


#endif
