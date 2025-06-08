/***********************************************************************************
# File Name:    test01.cpp
# Author:       ciyeer
# Mail:         ciyeer@outlook.com 
# Created Time: Thu May 15 09:42:59 2025
 **********************************************************************************/

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	int a = 10;
	int &ra = a;
	cout << "a's address = " << &a << endl;
	cout << "ra's address = " << &ra << endl;

	ra = 24;
	cout << "a = " << a << endl;
	cout << "ra = " << ra << endl;
	cout << "a's address = " << &a << endl;
	cout << "ra's address = " << &ra << endl;

	int t1 = 10;
	int t2 = 20;
	int &rt1 = t1;
	rt1 = t2;
	cout << "t1's address = " << &t1 << endl;
	cout << "rt1's address = " << &rt1 << endl;
	cout << "t2's address = " << &t2 << endl;

    return 0;
}
