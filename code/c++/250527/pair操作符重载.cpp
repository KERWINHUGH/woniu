/***************************************************
# File Name:    pair操作符重载.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月27日 星期二 14时53分54秒
****************************************************/

#include <iostream>
using namespace std;

template<class T1, class T2> class Pair{
public:
	Pair(T1 key, T2 value): m_key(key), m_value(value){}
	friend ostream &operator<<(ostream &out, const Pair<T1, T2> &p) {
		out << p.m_key << "--------------------" << p.m_value;
		return out;
	}
private:
		T1 m_key;
		T2 m_value;
};

int main(int argc, char *argv[]) {
	Pair<int, string> p1(1001, "Zhangsan");
	Pair<int, string> p2(1002, "Lisi");

	cout << p1 << endl;
	cout << p2 << endl;
    return 0;
}
