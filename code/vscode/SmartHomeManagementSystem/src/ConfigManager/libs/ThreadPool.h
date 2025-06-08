/***************************************************
# File Name:    ThreadPool.h
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月29日 星期四 19时16分17秒
****************************************************/
#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include "../../UserManager/UserManager.h"
#include "../../DeviceManager/DeviceManager.h"

class ThreadPool {
public:
ThreadPool(size_t numThreads);
void enqueueTask(std::function<void()> task);
~ThreadPool();
private:
std::vector<std::thread> workers;
std::queue<std::function<void()>> tasks;
std::mutex queueMutex;
std::condition_variable condition;
bool stop;
};

#endif
