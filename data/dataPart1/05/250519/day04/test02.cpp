/***********************************************************************************
# File Name:    test02.cpp
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Mon May 19 10:47:02 2025
***********************************************************************************/

#include <iostream>
using namespace std;

class StuInfoManager {
public:
    StuInfoManager& setId(int id) {
        this->m_id = id;
        return *this;
    }
    int getId() const {
        return this->m_id;
    }
    StuInfoManager& setName(string name) {
        this->m_name = name;
        return *this;
    }
    string getName() const {
        return this->m_name;
    }
    StuInfoManager& setAge(int age) {
        this->m_age = age;
        return *this;
    }
    int getAge() const {
        return this->m_age;
    }
    StuInfoManager& setGrade(int grade) {
        this->m_grade = grade;
        return *this;
    }
    int getGrade() const {
        return this->m_grade;
    }
    void printInfo() {
        cout << "id: " << (*this).m_id << endl;
        cout << "name: " << this->m_name << endl;
        cout << "age: " << this->m_age << endl;
        cout << "grade: " << this->m_grade << endl;
    }

private:
    int m_id;
    string m_name;
    int m_age;
    int m_grade;
};

int main(int argc, char* argv[]) {
    StuInfoManager stu;
    stu.setId(1).setName("Zhangsan").setAge(20).setGrade(2025).printInfo();

    return 0;
}
