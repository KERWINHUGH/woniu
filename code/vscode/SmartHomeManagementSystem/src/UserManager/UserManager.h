/***************************************************
# File Name:    UserManager.h
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月29日 星期四 19时30分29秒
****************************************************/
#ifndef _USERMANAGER_H
#define _USERMANAGER_H
#include <string>
#include <map>
#include "User.h"

class UserManager {
public:
    UserManager();
    bool registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password);
    void logoutUser(int userId);
    User* getUser(int userId);
private:
    std::map<int, User> users;
    std::map<int, std::string> sessions; // 记录会话信息，如登录时间等
};

#endif

