/***************************************************
# File Name:    访问限制.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月16日 星期五 15时19分36秒
****************************************************/

#include <iostream>
using namespace std;

class Person{
private:
   string m_strName;
   int m_nAge;
public:
   void set(string &name,int age){
		m_strName = name;
		if(age>0 && age<100)
		m_nAge = age;
   }
	string getString(){
		return m_strName;
	}
	int getage(){
		return m_nAge;
	}
   void init(string name , int age){
		set(name,age);
   }
};

void print(string name, int age){
	cout << "name = " << name << "age = " << age << endl;
}

int main(int argc, char *argv[]) {
	
    return 0;
}
