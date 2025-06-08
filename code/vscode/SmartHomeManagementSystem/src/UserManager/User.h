/***************************************************
# File Name:    User.h
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月29日 星期四 19时29分27秒
****************************************************/
#ifndef _USER_H
#define _USER_H
#include <string>

class User {
public:
enum class Role { Admin, User };
    User(int id, const std::string& username, const std::string&password_hash, Role role)
    : id(id), username(username), password_hash(password_hash),role(role) {}
    int getId() const { return id; }
    const std::string& getUsername() const { return username; }
    const std::string& getPasswordHash() const { return password_hash; }
    Role getRole() const { return role; }
private:
    int id;
    std::string username;
    std::string password_hash;
    Role role;
};

#endif
