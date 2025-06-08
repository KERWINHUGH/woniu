/***************************************************
# File Name:    this指针使用.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月19日 星期一 10时32分11秒
****************************************************/

#include <iostream>
using namespace std;

class StuInfoManager{
private:
	int m_id;
	string m_name;
	int m_age;
	int m_grade;

public:
	StuInfoManager setId(int id){
		this->m_id = id;
		return *this;
	}
	int getId() const{
		return this->m_id;
	}
	StuInfoManager setName(string name){
		this->m_name = name;
		return *this;
	}
	string getName() const{
		return this->m_name;
	}
	StuInfoManager setAge(int age){
		this->m_age = age;
		return *this;
	}
	int getAge() const{
		return this->m_age;
	}
	StuInfoManager setGrade(int grade){
		this ->m_grade = grade;
		return *this;
	}
	int getGrage() const{
		return this->m_grade;
	}

	void printInfo(){
		cout << "id:" << this->m_id << endl;
		cout << "name" << this->m_name << endl;
		cout << "age" << this->m_age << endl;
		cout << "grade" << this->m_grade << endl;
	}
};

int main(int argc, char *argv[]) {

	StuInfoManager stu;
	stu.setId(1).setName("zhangsan").setAge(20).setGrade(2025).printInfo();
    return 0;
}
