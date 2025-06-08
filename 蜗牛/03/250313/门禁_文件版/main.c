#include <stdio.h>
#include <stdlib.h>
#include "src.h"

int login_status = 0;

void firstUi(){
    // 一级界面
    char flag = '1';
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("- - - - - - - - -  欢迎使用蜗牛门禁系统 - - - - - - - -\n");
    
    while(flag == '1'){
        printf("- - - - - - - - - 1-登录 2-注册 3-退出 - - - - - - - -\n");
        printf("请选择服务：");
        char choice;
        scanf(" %c", &choice);
        switch (choice) {
            case '1': login_status = login();flag = '0';break;
            case '2': addUser();break;
            case '3': exit(0);break;
            default: printf("输入错误，请重新输入！\n");break;
        }
    }
}

void secondUi(){
    if(role == 1){
        // 普通用户界面
        while(1){
            printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
            printf("1-显示详细信息\n2-修改密码\n3-修改手机号\n4-修改地址\n5-退出\n");
            printf("请选择服务：");
            int choice;
            scanf("%d", &choice);
            if(choice == 1){
                displayUserInfo();  // 显示用户信息
            }else if(choice == 2 || choice == 3 || choice == 4){
                modifyUserInfo(choice);
            }else if(choice == 5){
                exit(0);
            }else{
                printf("没有该服务，请重新输入！\n");
            }
        }
    }else if(role == 0){
        // 管理员界面
        while(1){
            printf("- - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
            printf("1-显示所有用户\n2-查询用户详情\n3-新增用户\n4-删除用户\n5-修改密码\n6-修改手机号\n7-修改地址\n8-修改状态\n9-解除锁定\n0-退出\n");
            printf("请选择服务：");
            int choice;
            scanf("%d", &choice);
            if(choice == 1){
                displayAllUsersInfo();  // 显示用户信息
            }else if(choice == 2){
                displayUserInfo();  // 显示用户信息;
            }else if(choice == 3){
                addUser();
            }else if(choice == 4){
                deleteUser();
            }else if(choice == 5 || choice == 6 || choice == 7 || choice == 8 || choice == 9){
                modifyUserInfo(choice);
            }else if(choice == 0){
                exit(0);
            }else{
                printf("没有该服务，请重新输入！\n");
            }
        }
    }
}

int main(){
    firstUi();
    if(login_status == 1){
        secondUi();
    }
    return 0;
}