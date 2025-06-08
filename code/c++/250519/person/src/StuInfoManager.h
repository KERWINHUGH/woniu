/***************************************************
# File Name:    this指针使用.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月19日 星期一 10时32分11秒
****************************************************/
#ifndef _STUINFOMANAGER_H
#define _STUINFOMANAGER_H

class StuInfoManager{
private:
	int m_id;
	std::string m_name;
	int m_age;
	int m_grade;

public:
	StuInfoManager& setId(int id);
	int getId() const;
	StuInfoManager& setName(std::string name);
	std::string getName() const;
	StuInfoManager& setAge(int age);
	int getAge() const;
	StuInfoManager& setGrade(int grade);
	int getGrage() const;

	void printInfo();
};

#endif
