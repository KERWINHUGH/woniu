/***************************************************
# File Name:    client.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年04月05日 星期六 21时42分12秒
****************************************************/

#include "common.h"

void send_request(int sockfd, Request *req) {
    send(sockfd, req, sizeof(Request), 0);
    Response resp;
    recv(sockfd, &resp, sizeof(Response), 0);
    if (resp.status == 0) {
        printf("操作成功: %s\n", resp.message);
        if (strlen(resp.data) > 0) {
            cJSON *root = cJSON_Parse(resp.data);
            // 解析并显示数据...
        }
    } else {
        printf("错误: %s\n", resp.message);
    }
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(8080)};
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));

    // 管理员登录
    Request req = {LOGIN};
    printf("用户名: ");
    scanf("%s", req.username);
    printf("密码: ");
    scanf("%s", req.password);
    send_request(sockfd, &req);

    // 管理员菜单循环
    while (1) {
        printf("1. 添加员工\n2. 删除员工\n...");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                cJSON *emp = cJSON_CreateObject();
                cJSON_AddNumberToObject(emp, "id", 1001);
                // 填充其他字段...
                req.type = ADD_EMP;
                strcpy(req.data, cJSON_Print(emp));
                send_request(sockfd, &req);
                cJSON_Delete(emp);
                break;
            }
            // 其他操作类似...
        }
    }
    return 0;
}

