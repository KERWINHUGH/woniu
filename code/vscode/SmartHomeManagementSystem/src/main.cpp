/***************************************************
# File Name:    UserManager.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月29日 星期四 19时30分29秒
****************************************************/
#include <iostream>
using namespace std;
#include "UserManager/UserManager.h"
#include "UserManager/User.h"


enum FirstMenuChoice {
    EXIT,
    LOGIN,
    LOGOUT,
    REGISTER,
    RESET_PASSWORD,
    CHANGE_PASSWORD,
    DELETE_USER,
    CHANGE_INFO,
    QUERY_USER_INFO,
};
void firstMenu()
{
    cout << "*********************************************************************" << endl;
    cout << "-----------------------欢迎来到智能家居管理系统------------------------" << endl;
    cout << "-------------------------------1. 登录-------------------------------" << endl;
    cout << "-------------------------------2. 登出-------------------------------" << endl;
    cout << "-------------------------------3. 注册用户---------------------------" << endl;
    cout << "-------------------------------4. 重置密码---------------------------" << endl;
    cout << "-------------------------------5. 修改密码---------------------------" << endl;
    cout << "-------------------------------6. 删除用户---------------------------" << endl;
    cout << "-------------------------------7. 更改个人信息-----------------------" << endl;
    cout << "-------------------------------8. 查询用户信息-----------------------" << endl;
    cout << "-------------------------------0. 退出------------------------------" << endl;    
    cout << "********************************************************************" << endl;
    cout << "-------------------------------请选择：------------------------------" << endl;

    int choice;
    bool sign = true;

    while(sign){
        
        cin >>  choice;
        while(choice < 0 || choice > 8)
        {
            cout << "输入错误，请重新输入" << endl;
            cin.ignore();
            cin >> choice;
        }

        switch(choice)
        {
            case LOGIN:
                cout << "登录" << endl;
                break;
            case LOGOUT:
                cout << "登出" << endl;
                break;
            case REGISTER:
                cout << "注册用户" << endl;
                break;
            case RESET_PASSWORD:
                cout << "重置密码" << endl;
                break;
            case CHANGE_PASSWORD:
                cout << "修改密码" << endl;
                break;
            case DELETE_USER:
                cout << "删除用户" << endl;
                break;
            case CHANGE_INFO:
                cout << "更改个人信息" << endl;
                break;
            case QUERY_USER_INFO:
                cout << "查询用户信息" << endl;
                break;
            case EXIT:
                cout << "退出" << endl;
                sign = false;
                break;
            default:
                cout << "输入数字不在系统服务范围之内" << endl;
                break;
        }
    }
}


int main()
{
    firstMenu();
    return 0;
}
