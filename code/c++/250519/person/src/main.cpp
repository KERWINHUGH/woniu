/***************************************************
# File Name:    this指针使用.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月19日 星期一 10时32分11秒
****************************************************/

#include <iostream>
#include "StuInfoManager.h"
using namespace std;

int main(int argc, char *argv[]) {

	StuInfoManager stu;
	stu.setId(1).setName("zhangsan").setAge(20).setGrade(2025).printInfo();
    return 0;
}
