#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // 用于操作目录的结构和函数
#include <unistd.h> // 用于access函数

/*
opendir函数，传入目录路径，返回一个DIR结构体指针，失败时返回NULL并设置errno
readdir函数，传入DIR结构体指针，返回一个dirent结构体指针，失败时返回NULL并设置errno
closedir函数，传入DIR结构体指针，关闭目录，失败时返回-1并设置errno
access(filepath, F_OK)函数，传入文件路径和权限，判断文件是否存在，失败时返回-1并设置errno
*/

int main() {
    char *dir_path = "/home/dengjj/NJ_Scripts/门禁_文件版/users";
    char username[20],filepath[1024];
    struct dirent *entry;  // 定义dirent结构体指针，保存文件信息
    DIR *dir = opendir(dir_path);   // 打开目录
    if (dir == NULL) {     // 检查打开是否成功
        perror("opendir");
        return 1;
    }
    // 遍历目录下的所有文件
    while((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0){
            continue;
        }
        snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, entry->d_name);
        printf("%s\n",filepath);
    }
    closedir(dir);  // 关闭目录
    return 0;
}