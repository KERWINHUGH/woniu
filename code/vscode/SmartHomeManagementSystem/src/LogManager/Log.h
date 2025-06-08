/***************************************************
# File Name:    Log.h
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月29日 星期四 19时16分17秒
****************************************************/
#ifndef _LOG_H
#define _LOG_H
#include <string>

class Log {
public:
enum class LogType { UserAction, DeviceAction, SystemError };
Log(LogType logType, int userId, int deviceId, const std::string&
content)
: logType(logType), userId(userId), deviceId(deviceId),
content(content) {}
LogType getLogType() const { return logType; }
int getUserId() const { return userId; }
int getDeviceId() const { return deviceId; }
const std::string& getContent() const { return content; }
private:
LogType logType;
int userId;
int deviceId;
std::string content;
};

#endif
