/***********************************************************************************
# File Name:    test01.cpp
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Mon May 19 10:36:41 2025
 **********************************************************************************/

 #include <iostream>
 using namespace std;
 
 class StuInfoManager {
 public:
     void setId(int id) {
         this->m_id = id;
     }
     int getId() const {
         return this->m_id;
     }
     void setName(string name) {
        this->m_name = name;
     }
     string getName() const {
         return this->m_name;
     }
     void setAge(int age) {
        this->m_age = age;
     }
     int getAge() const {
         return this->m_age;
     }
     void setGrade(int grade) {
        this->m_grade = grade;
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
     stu.setId(1);
     stu.setName("张三");
     stu.setAge(20);
     stu.setGrade(1);
     stu.printInfo();
 
     return 0;
 }
