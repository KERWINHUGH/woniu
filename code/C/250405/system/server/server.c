/***************************************************
# File Name:    server.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年04月05日 星期六 21时39分44秒
****************************************************/

#include "common.h"

sqlite3 *db = NULL;
pthread_mutex_t db_mutex = PTHREAD_MUTEX_INITIALIZER;
/*
// 哈希密码（SHA-256）
void hash_password(const char *input, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input, strlen(input), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i*2), "%02x", hash[i]);
    }
    output[64] = '\0';
}
*/
// 将数据库查询结果转为JSON数组
cJSON *employee_to_json(sqlite3_stmt *stmt) {
    cJSON *root = cJSON_CreateArray();
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cJSON *emp = cJSON_CreateObject();
        cJSON_AddNumberToObject(emp, "id", sqlite3_column_int(stmt, 0));
        cJSON_AddStringToObject(emp, "name", (char*)sqlite3_column_text(stmt, 1));
        // 其他字段类似...
        cJSON_AddItemToArray(root, emp);
    }
    return root;
}

// 执行SQL并返回JSON结果
int exec_sql(const char *sql, cJSON **result) {
    pthread_mutex_lock(&db_mutex);
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        pthread_mutex_unlock(&db_mutex);
        return -1;
    }
    *result = employee_to_json(stmt);
    sqlite3_finalize(stmt);
    pthread_mutex_unlock(&db_mutex);
    return 0;
}

// 处理客户端请求
void handle_request(int client_fd) {
    Request req;
    Response resp = {0, "", ""};
    recv(client_fd, &req, sizeof(Request), 0);

    switch (req.type) {
        case LOGIN: {
            char hashed_pwd[65];
            hash_password(req.password, hashed_pwd);
            char sql[256];
            sprintf(sql, "SELECT * FROM admins WHERE name='%s' AND password='%s'", 
                    req.username, hashed_pwd);
            cJSON *result;
            if (exec_sql(sql, &result) == 0 && cJSON_GetArraySize(result) > 0) {
                resp.status = 0;
                strcpy(resp.message, "登录成功");
            } else {
                resp.status = 1;
                strcpy(resp.message, "用户名或密码错误");
            }
            cJSON_Delete(result);
            break;
        }
        case ADD_EMP: {
            cJSON *emp_json = cJSON_Parse(req.data);
            char sql[512];
            sprintf(sql, "INSERT INTO employees VALUES(%d, '%s', '%s', %d, %d, %f, %d, %d)",
                    cJSON_GetObjectItem(emp_json, "id")->valueint,
                    cJSON_GetObjectItem(emp_json, "name")->valuestring,
                    cJSON_GetObjectItem(emp_json, "password")->valuestring,
                    // 其他字段...
                   );
            if (exec_sql(sql, NULL) == 0) {
                resp.status = 0;
                strcpy(resp.message, "添加成功");
            }
            break;
        }
        // 其他操作类似...
    }

    send(client_fd, &resp, sizeof(Response), 0);
    close(client_fd);
}

int main() {
    sqlite3_open("employees.db", &db);
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(8080), INADDR_ANY};
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);
        pthread_t tid;
        pthread_create(&tid, NULL, (void*)handle_request, (void*)client_fd);
    }
    return 0;
}

