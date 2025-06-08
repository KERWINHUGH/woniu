/***************************************************
# File Name:    隐式转换.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月19日 星期一 16时50分35秒
****************************************************/

#include <iostream>
using namespace std;

class Info{
public:
	//使用单个参数的构造函数时，可能会存在 参数类型（int） 向 类类型（Info） 隐式转换的情况
	//我们不希望这种情况出现，此时使用explicit关键字，让出现这种情况时可以提示
	// Info(int id){
	explicit Info(int id){
		cout << "This is Info's constructor with param" << endl;
		m_id = id;
	}

	bool isEqual(const Info &info){
		return m_id ==info.m_id;
	}

private:
	int m_id;
};

int main(int argc, char *argv[]) {
	
	Info info(1);
	bool bEq = info.isEqual(1);

    return 0;
}
