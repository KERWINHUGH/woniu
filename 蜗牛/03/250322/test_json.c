#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

int main() {
    // 创建一个JSON对象
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        fprintf(stderr, "Failed to create JSON object\n");
        return 1;
    }

    // 向JSON对象中添加一个键值对
    cJSON_AddStringToObject(root, "message", "Hello, cJSON!");

    // 将JSON对象转换为字符串
    char *json_str = cJSON_Print(root);
    if (json_str == NULL) {
        fprintf(stderr, "Failed to print JSON object\n");
        cJSON_Delete(root);
        return 1;
    }

    // 打印JSON字符串
    printf("%s\n", json_str);

    // 释放资源
    cJSON_free(json_str);
    cJSON_Delete(root);

    return 0;
}
