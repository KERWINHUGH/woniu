/***************************************************
# File Name:    common.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月25日 星期二 20时11分53秒
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "cJSON.h"
#include "json.h"
#include "common.h"


//安全发送数据，处理部分发送
/*
** 参数char* data：要发送的数据
** 参数len：要发送的json字符串长度
*/
void send_all(int sock, const char* data, size_t len) {
    size_t total_sent = 0;		//正在发送的数据总长度
    //服务端发送时处理分包
    while (total_sent < len) {
        ssize_t sent = send(sock, data + total_sent, len - total_sent, 0);
        if (sent == -1) {
            perror("send error");
            exit(EXIT_FAILURE);
        }
        total_sent += sent;		//计算每次发送的长度，确保json字符串完整发送
    }
}
// 安全接收（处理部分接收）
int recv_all(int sock, char* buffer, size_t len) {
    size_t total_received = 0;
    while (total_received < len) {
        ssize_t received = recv(sock, buffer + total_received, len - total_received, 0);
        if (received <= 0) {
            return -1;  // 连接关闭或错误
        }
        total_received += received;
    }
    return 0;
}
void send_combined_data(int sock, const char* str_a, const char* str_b) {
    // 计算各部分长度
    uint32_t len_a = strlen(str_a);
    uint32_t len_b = strlen(str_b);
    
    // 总长度 = len_a头 + len_a内容 + len_b头 + len_b内容
    uint32_t total_len = sizeof(uint32_t) + len_a + sizeof(uint32_t) + len_b;
    uint32_t net_total_len = htonl(total_len);

    // 构造数据包
    char* buffer = malloc(sizeof(uint32_t) + total_len);
    memcpy(buffer, &net_total_len, sizeof(uint32_t));  // 总长度头

    uint32_t net_len_a = htonl(len_a);
    uint32_t net_len_b = htonl(len_b);
    
    char* p = buffer + sizeof(uint32_t);
    memcpy(p, &net_len_a, sizeof(uint32_t));  // 字符串A长度头
    p += sizeof(uint32_t);
    memcpy(p, str_a, len_a);                  // 字符串A内容
    p += len_a;
    
    memcpy(p, &net_len_b, sizeof(uint32_t));  // 字符串B长度头
    p += sizeof(uint32_t);
    memcpy(p, str_b, len_b);                  // 字符串B内容

    // 发送完整数据包
    send_all(sock, buffer, sizeof(uint32_t) + total_len);
    free(buffer);
}
// 解析嵌套数据包
void parse_combined_data(char* data, uint32_t total_len) {
    uint32_t pos = 0;
    
    // 解析字符串A
    uint32_t len_a = ntohl(*(uint32_t*)(data + pos));
    pos += sizeof(uint32_t);
    char* str_a = data + pos;
    pos += len_a;
    printf("String A (len=%u): %.*s\n", len_a, len_a, str_a);

    // 解析字符串B
    uint32_t len_b = ntohl(*(uint32_t*)(data + pos));
    pos += sizeof(uint32_t);
    char* str_b = data + pos;
    pos += len_b;
    printf("String B (len=%u): %.*s\n", len_b, len_b, str_b);
}
