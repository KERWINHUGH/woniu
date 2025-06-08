/***************************************************
# File Name:    DeviceManager.h
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月29日 星期四 19时30分29秒
****************************************************/
#ifndef _DEVICEMANAGER_H
#define _DEVICEMANAGER_H
#include <map>
#include <vector>
#include "Device.h"

class DeviceManager {
public:
DeviceManager();
void addDevice(const Device& device);
void removeDevice(int deviceId);
Device* getDevice(int deviceId);
void updateDeviceStatus(int deviceId, const std::string& newStatus);
std::vector<Device> getAllDevices() const;
private:
std::map<int, Device> devices;
};

#endif

