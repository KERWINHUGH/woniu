/***************************************************
# File Name:    LogManager.h
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月29日 星期四 19时16分17秒
****************************************************/
#ifndef _LOGMANAGER_H
#define _LOGMANAGER_H
#include "Log.h"
#include "../UserManager/UserManager.h"
#include "../DeviceManager/DeviceManager.h"
#include <mutex>

class LogManager {
public:
LogManager();
void logAction(Log::LogType logType, int userId, int deviceId, const
std::string& content);
void saveLogsToFile(const std::string& filename);
std::vector<Log> getLogsByUser(int userId) const;
std::vector<Log> getLogsByDevice(int deviceId) const;
private:
std::vector<Log> logs;
std::mutex logMutex; // 用于线程安全的日志写入
};

#endif
