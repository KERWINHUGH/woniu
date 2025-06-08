/***************************************************
# File Name:    Lambda.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月15日 星期四 17时35分35秒
****************************************************/

#include <iostream>
using namespace std;

/************************************************************
 编写一个函数 applyOperation，该函数接收一个 Lambda
 表达式和两个整数，调用 Lambda 表达式执行相应的运算并返回结果。
 ************************************************************/

void applyOperation( int *lam()){
	 lam();
}

int main(int argc, char *argv[]) {
	auto lam = [](){
		cout<<"lambda表达式内部"<<endl;	
	};
	int a = 5;
	int b = 6;
	 applyOperation(lam());
	//cout<<d<<endl;
	 return 0;
}
