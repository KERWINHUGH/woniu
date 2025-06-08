/***************************************************
# File Name:    类型转换.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月28日 星期三 12时00分06秒
****************************************************/

#include <iostream>
using namespace std;

class Animal{};
class Dog : public Animal{};
class Other{};

//基础数据类型转换
void test1(){
	char a = 'a';
	double b = static_cast<double>(a);
}

//继承关系指针的转换
void test2(){
	Animal *animal = nullptr;
	Dog * dog = nullptr;
	//子类转换为父类------------上行转换--------------安全
	animal = static_cast<Animal *>(dog);
	//父类转换为子类------------下行转换--------------不安全
	dog = static_cast<Dog *>(animal);
}

//继承关系的引用互相转换
void test3(){
	Animal ani_ref;
	Animal& animal = ani_ref;
	
	Dog dog_ref;
	Dog& dog = dog_ref;

	//子类指针转换为父类指针----------安全
	animal = static_cast<Animal &>(dog);

	//父类指针转换为子类指针----------不安全
	dog = static_cast<Dog &>(animal);
}

//无继承关系转换
void test4(){
	Animal* animal = nullptr;
	Other* other = nullptr;

	//无继承关系不能转换，转换错误
//	animal = static_cast<Animal*>(other);
//	other = static_cast<Other*>(animal);	
}

int main(int argc, char *argv[]) {
	test1();
	test2();
	test3();
	test4();
	return 0;
}
