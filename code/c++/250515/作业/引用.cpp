/***************************************************
# File Name:    引用.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月15日 星期四 17时45分16秒
****************************************************/

#include <iostream>
using namespace std;

/*****************************************************
** 1.编写一个函数 swap，使用引用参数交换两个整数的值。
** 2.在 main 函数中调用 swap 函数，并输出交换前后的值。
*****************************************************/

void swap(int &a, int &b){
	int s = a;
	a = b;
	b = s;
}

int main(int argc, char *argv[]) {
	int a = 10;
	int b = 20;
	cout<<a<<endl<<b<<endl;
	swap(a,b);
	cout<<a<<endl<<b<<endl;
	return 0;
}
