/***************************************************
# File Name:    立方体.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月19日 星期一 18时52分37秒
****************************************************/

#include <iostream>
using namespace std;

/*设计立方体类(Cube)

求出立方体的面积(2ab + 2ac + 2bc)和体积(a b c),分别用全局函数和成员函数判断两个立方体是否相等。
分别使用成员函数和构造函数实现
*/

class Cube{
public:
	void setA(int l);
	int getA() const;
	void setB(int w);
	int getB() const;
	void setC(int h);
	int getC() const;

//	Cube(int l, int w, int h):a(l),b(w),c(h){}

	int printSq(){
		return 2*a*b + 2*a*c + 2*b*c;
	}

	int printTj(){
		return a*b*c;
	}

	bool isEqual(const Cube& mem){
		return (a == mem.a)&&(b == mem.b)&&(c == mem.c);
	}
private:
	int a;	//长
	int b;	//宽
	int c;	//高
};

bool checkEqual(const Cube& mem1, const Cube& mem2){
	return (mem1.getA() == mem2.getA())&&
		   (mem1.getB() == mem2.getB())&&
		   (mem1.getC() == mem2.getC());
}

int main(int argc, char *argv[]) {
	
	Cube c1;
	c1.setA(3);
	c1.setB(3);
	c1.setC(3);

	Cube c2;
	c2.setA(3);
	c2.setB(3);
	c2.setC(3);
	
	Cube c3;
	c3.setA(4);
	c3.setB(4);
	c3.setC(4);

	//使用析构函数实现初始化成员变量
//	Cube c1(3,3,3);
//	Cube c2(3,3,3);
//	Cube c3(4,4,4);

	cout << "Cube1 表面积: " << c1.printSq() << endl;  //
	cout << "Cube1 体积: " << c1.printTj() << endl;  //

	cout << "Cube2 表面积: " << c2.printSq() << endl;  //
	cout << "Cube2 体积: " << c2.printTj() << endl;  //

	cout << "Cube3 表面积: " << c3.printSq() << endl;  //
	cout << "Cube3 体积: " << c3.printTj() << endl;  //

	//调用成员函数比较立方体
	//调用成员c1的成员函数，传入c2对象做比较
	cout << "成员函数判断c1与c2是否相等（0：不相等 1：相等 ）：" << c1.isEqual(c2) << endl;
	cout << "成员函数判断c1与c3是否相等（0：不相等 1：相等 ）：" << c1.isEqual(c3) << endl;

	//调用全局函数比较立方体
	cout << "全局函数判断c1与c2是否相等（0：不相等 1：相等 ）：" << checkEqual(c1,c2) << endl;
	cout << "全局函数判断c1与c3是否相等（0：不相等 1：相等 ）：" << checkEqual(c1,c3) << endl;


    return 0;
}

void Cube::setA(int l){
	a = l;
}
int Cube::getA() const{
	return a;
}
void Cube::setB(int w){
	b = w;
}
int Cube::getB() const{
	return b;
}
void Cube::setC(int h){
	c = h;
}
int Cube::getC() const{
	return c;
}

