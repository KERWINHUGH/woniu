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


// 构建 JSON 数据包（带校验字段）
char* build_json_packet(const double* numbers, int num_count, const char** strings, int str_count) {
    cJSON* root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "version", 1.0); // 协议版本号
    cJSON_AddStringToObject(root, "checksum", "md5_placeholder"); // 预留校验位
    // 其他字段添加...
    return cJSON_PrintUnformatted(root);
}
/**
 * 可靠发送数据（处理 TCP 分片问题）
 * @param sockfd    Socket 描述符
 * @param data      待发送数据
 * @param len       数据长度
 * @return          成功发送的字节数，-1 表示失败
 */
int reliable_send(int sockfd, const char* data, size_t len) {
    size_t total_sent = 0;
    while (total_sent < len) {
        ssize_t sent = send(sockfd, data + total_sent, len - total_sent, 0);
        if (sent <= 0) {
            if (errno == EINTR) continue; // 处理系统中断
            perror("send failed");
            return -1;
        }
        total_sent += sent;
    }
    return total_sent;
}
/**
 * 可靠接收数据（基于头部长度信息）
 * @param sockfd    Socket 描述符
 * @param buffer    输出缓冲区（需预先分配内存）
 * @param max_len   缓冲区最大容量
 * @return          实际接收的数据长度，-1 表示失败
 */
int reliable_recv(int sockfd, char* buffer, size_t max_len) {
    // 先接收头部（4字节长度信息）
    uint32_t data_len;
    if (recv(sockfd, &data_len, sizeof(data_len), MSG_WAITALL) != sizeof(data_len)) {
        return -1;
    }
    data_len = ntohl(data_len); // 转换网络字节序

    // 检查数据长度合法性
    if (data_len > max_len) {
        fprintf(stderr, "数据过长: %u > %zu\n", data_len, max_len);
        return -1;
    }

    // 接收实际数据
    size_t total_received = 0;
    while (total_received < data_len) {
        ssize_t recv_len = recv(sockfd, buffer + total_received, 
                              data_len - total_received, 0);
        if (recv_len <= 0) {
            if (errno == EINTR) continue;
            return -1;
        }
        total_received += recv_len;
    }
    return data_len;
}
/*void server_main(int port) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {.sin_family = AF_INET, 
                              .sin_port = htons(port),
                              .sin_addr.s_addr = INADDR_ANY};
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);
        char header[4];
        char json_buffer[4096];

        // 接收数据
        int len = reliable_recv(client_fd, json_buffer, sizeof(json_buffer)-1);
        if (len > 0) {
            json_buffer[len] = '\0';
            printf("收到原始JSON: %s\n", json_buffer);

            // 反序列化处理
            double numbers[10];
            char* strings[10];
            int num_count, str_count;
            parse_json(json_buffer, numbers, 10, strings, 10, &num_count, &str_count);
        }
        close(client_fd);
    }
}
*/
/*
void client_main(const char* server_ip, int port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {.sin_family = AF_INET,
                              .sin_port = htons(port),
                              .sin_addr.s_addr = inet_addr(server_ip)};
    connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));

    // 构建 JSON 数据
    double nums[] = {1.1, 2.2, 3.3};
    const char* strs[] = {"hello", "world"};
    char* json_str = build_json_packet(nums, 3, strs, 2);

    // 发送数据（添加4字节长度头）
    uint32_t len = strlen(json_str);
    uint32_t net_len = htonl(len);
    reliable_send(sockfd, (char*)&net_len, sizeof(net_len));
    reliable_send(sockfd, json_str, len);

    free(json_str);
    close(sockfd);
}
*/
