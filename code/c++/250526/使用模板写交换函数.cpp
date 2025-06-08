/***************************************************
# File Name:    使用模板写交换函数.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月26日 星期一 10时02分15秒
****************************************************/

#include <iostream>
using namespace std;

template <typename T1, class T2>
void swapNum(T1 &a, T2 &b){
	T1 c = a;
	a = (T1)b;
	b = (T2)c;
}

int main(int argc, char *argv[]) {
	
	int a = 2;
	double b = 3.8;
	
	cout << "a = " << a << endl << "b = " << b << endl;
	
	swapNum(a,b);

	cout << "a = " << a << endl << "b = " << b << endl;
    return 0;
}
