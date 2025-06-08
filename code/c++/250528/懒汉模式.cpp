/***************************************************
# File Name:    懒汉模式.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月28日 星期三 21时02分34秒
****************************************************/

#include <iostream>
#include <mutex>
using namespace std;

class Singleton{
public:
    static Singleton* getInstance(){
        if(!m_pInstance)
        {
            std::lock_guard<std::mutex> lock(mutex);
            m_pInstance = new Singleton;
        }
    }
    Singleton(const Singleton& ) = delete;
    Singleton& operator=(const Singleton&) = delete;
private:
    Singleton(){
        std::cout << "singleton" << std::endl;
    }
    ~Singleton(){}

    static Singleton* m_pInstance;
    static std::mutex mutex;
};

Singleton *Singleton::m_pInstance = nullptr;
std::mutex Singleton::mutex;

int main(int argc, char *argv[]) {

    return 0;
}
