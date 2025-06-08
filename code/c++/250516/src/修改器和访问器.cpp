/***************************************************
# File Name:    修改器和访问器.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月16日 星期五 14时30分00秒
****************************************************/

#include <iostream>
using namespace std;


class Student {
private:
	int m_Id;
	string m_name;
	int m_score;
public:
	//修改器mutator
	void setId(int id){
		m_Id = id;
	}
	//访问器accessor
	int getId() const{
		return m_Id;
	}
};


int main(int argc, char *argv[]) {
	Student stu1;
	Student stu2;

	Student * pstu1 = &stu1;
	//使用修改器
	pstu1->setId(10001);
	//使用访问器
	cout << "id = " << pstu1->getId() << endl;
	
    return 0;
}
