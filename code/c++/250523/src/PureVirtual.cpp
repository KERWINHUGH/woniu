/***************************************************
# File Name:    多态纯虚函数实现泡茶流程.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月23日 星期五 16时02分56秒
****************************************************/

#include <iostream>
#include "PureVirtual.h"
using namespace std;

void Produce::Production(AbstractDrinking *drink){
	drink->Boil();
	drink->Brew();
	drink->Pour();
	drink->Addthings();
	delete drink;
	drink = nullptr;
}

void Coffe::Boil(){
	cout << "煮水" << endl;	
}

void Coffe::Brew(){
	cout << "冲泡咖啡" << endl;		
}

void Coffe::Pour(){
	cout << "倒入杯中" << endl;		
}

void Coffe::Addthings(){
	cout << "加糖和牛奶" << endl;		
}	

void Tea::Boil(){
	cout << "煮水" << endl;	
}

void Tea::Brew(){
	cout << "冲泡茶叶" << endl;		
}

void Tea::Pour(){
	cout << "倒入杯中" << endl;		
}

void Tea::Addthings(){
	cout << "加柠檬" << endl;		
}	

void test(){
	Produce::Production(new Coffe);
	cout << "---------------------------" << endl;
	Produce::Production(new Tea);
}

