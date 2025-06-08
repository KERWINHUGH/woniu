/***************************************************
# File Name:    Device.h
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月29日 星期四 19时29分27秒
****************************************************/
#ifndef _DEVICE_H
#define _DEVICE_H
#include <string>

class Device {
public:
enum class DeviceType { Light, Thermostat, Camera, Socket };
Device(int id, DeviceType type)
: id(id), type(type), status("off") {}
int getId() const { return id; }
DeviceType getType() const { return type; }
const std::string& getStatus() const { return status; }
void setStatus(const std::string& newStatus) { status = newStatus; }
private:
int id;
DeviceType type;
std::string status; // 设备状态，如 "on", "off", "adjusted"
};

#endif
