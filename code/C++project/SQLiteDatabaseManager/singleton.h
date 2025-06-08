#ifndef _SINGLETON_H
#define _SINGLETON_H
#include <iostream>
#include <mutex>

class Singleton{
public:
    static Singleton* getInstance(){
        if(!m_pInstance)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if(!m_pInstance)
            {
                m_pInstance = new Singleton;
            }   
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
    static std::mutex m_mutex;
};

Singleton* Singleton::m_pInstance = nullptr;
std::mutex Singleton::m_mutex;

#endif //_SINGLETON_H