/***************************************************
# File Name:    DatabaseManager.h
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月29日 星期四 19时16分17秒
****************************************************/
#ifndef _DATABASEMANAGER _H
#define _DATABASEMANAGER_H
#include <string>
#include <vector>
// #include "sqlite3.h"

class DatabaseManager {
public:
DatabaseManager(const std::string& dbPath);
bool connect();
bool disconnect();
bool executeQuery(const std::string& query);
std::vector<std::string> fetchResults(const std::string& query);
private:
std::string dbPath;
// sqlite3* db;
};

#endif
