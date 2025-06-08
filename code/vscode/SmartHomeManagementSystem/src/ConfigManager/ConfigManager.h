/***************************************************
# File Name:    ConfigManager.h
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月29日 星期四 19时16分17秒
****************************************************/
#ifndef _CONFIGMANAGER_H
#define _CONFIGMANAGER_H
#include <string>
#include <map>

class ConfigManager {
public:
ConfigManager(const std::string& configFile);
void loadConfig();
void saveConfig();
void updateConfig(const std::string& key, const std::string& value);
std::string getConfig(const std::string& key);
private:
std::map<std::string, std::string> configData;
std::string configFile;
};

#endif
