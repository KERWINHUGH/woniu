/***************************************************
# File Name:    多态纯虚函数实现泡茶流程.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月23日 星期五 16时02分56秒
****************************************************/

#include <iostream>
using namespace std;

class AbstractDrinking{
public:
	virtual void Boil() = 0;
	virtual void Brew() = 0;
	virtual void Pour() = 0;
	virtual void Addthings() = 0;
	void Production(){
		Boil();
		Brew();
		Pour();
		Addthings();
	}
	~AbstractDrinking(){}
};

class Coffe : public AbstractDrinking{
	virtual void Boil(){
		cout << "煮水" << endl;	
	}
	virtual void Brew(){
		cout << "冲泡咖啡" << endl;		
	}
	virtual void Pour(){
		cout << "倒入杯中" << endl;		
	}
	virtual void Addthings(){
		cout << "加糖和牛奶" << endl;		
	}	
};

class Tea : public AbstractDrinking{
	virtual void Boil(){
		cout << "煮水" << endl;	
	}
	virtual void Brew(){
		cout << "冲泡茶叶" << endl;		
	}
	virtual void Pour(){
		cout << "倒入杯中" << endl;		
	}
	virtual void Addthings(){
		cout << "加柠檬" << endl;		
	}	
};

void DoWork(AbstractDrinking *drink){
	drink->Production();
	delete drink;
}

void test(){
	DoWork(new Coffe);
	cout << "---------------------------" << endl;
	DoWork(new Tea);
}

int main(int argc, char *argv[]) {
	test();
    return 0;
}
