/***************************************************
# File Name:    commin.h
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年04月05日 星期六 21时36分14秒
****************************************************/
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "cJSON.h"

// 枚举定义
typedef enum {
    MALE, FEMALE
} Gender;

typedef enum {
    SALES, MARKETING, AFTER_SALE
} Department;

typedef enum {
    MANAGER, SALESMAN, CAPTAIN, WORKER, AFTER_SALE_STAFF
} Title;

typedef enum {
    ADMIN, EMPLOYEE
} Role;

// 操作类型
typedef enum {
    LOGIN, ADD_EMP, DELETE_EMP, UPDATE_EMP, QUERY_ALL, CHANGE_PWD
} OperationType;

// 请求结构体
typedef struct {
    OperationType type;
    char username[50];
    char password[50];
    int target_id;          // 用于删除/修改
    char data[1024];        // 存储JSON格式的员工数据
} Request;

// 响应结构体
typedef struct {
    int status;             // 0=成功, 1=失败
    char message[256];
    char data[4096];        // JSON格式的查询结果
} Response;

// 数据库全局连接（线程安全需加锁）
extern sqlite3 *db;
extern pthread_mutex_t db_mutex;

// 函数声明
void hash_password(const char *input, char *output);
cJSON *employee_to_json(sqlite3_stmt *stmt);
int exec_sql(const char *sql, cJSON **result);

#endif
