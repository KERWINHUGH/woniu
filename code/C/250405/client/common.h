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


// 构建 JSON 数据包（带校验字段）
char* build_json_packet(const double* numbers, int num_count, const char** strings, int str_count) ;
/**
 * 可靠发送数据（处理 TCP 分片问题）
 * @param sockfd    Socket 描述符
 * @param data      待发送数据
 * @param len       数据长度
 * @return          成功发送的字节数，-1 表示失败
 */
int reliable_send(int sockfd, const char* data, size_t len);
/**
 * 可靠接收数据（基于头部长度信息）
 * @param sockfd    Socket 描述符
 * @param buffer    输出缓冲区（需预先分配内存）
 * @param max_len   缓冲区最大容量
 * @return          实际接收的数据长度，-1 表示失败
 */
int reliable_recv(int sockfd, char* buffer, size_t max_len) ;



#endif
