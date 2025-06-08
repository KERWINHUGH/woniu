/***************************************************
# File Name:    this指针使用.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月19日 星期一 10时32分11秒
****************************************************/

#include <iostream>
#include "StuInfoManager.h"
using namespace std;


StuInfoManager &StuInfoManager::setId(int id){
	this->m_id = id;
	return *this;
}
int StuInfoManager::getId() const{
	return this->m_id;
}
StuInfoManager &StuInfoManager::setName(string name){
	this->m_name = name;
	return *this;
}
string StuInfoManager:: getName() const{
	return this->m_name;
}
StuInfoManager& StuInfoManager::setAge(int age){
	this->m_age = age;
	return *this;
}
int StuInfoManager::getAge() const{
	return this->m_age;
}
StuInfoManager& StuInfoManager::setGrade(int grade){
	this ->m_grade = grade;
	return *this;
}
int StuInfoManager::getGrage() const{
	return this->m_grade;
}

void StuInfoManager::printInfo(){
	cout << "id:" << this->m_id << endl;
	cout << "name" << this->m_name << endl;
	cout << "age" << this->m_age << endl;
	cout << "grade" << this->m_grade << endl;
}

