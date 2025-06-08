/***************************************************
# File Name:    mystring.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月21日 星期三 19时27分05秒
****************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

class mystr{
public:
	mystr() : p(nullptr), len(0) {}
	mystr(char *str){
		len = strlen(str);
		p = new char(len+1);
		strcpy(p,str);
		p[len] = '\0';
	}
	mystr(const mystr& str){
		p = new char(len+1);
		strcpy(p,str.p);
	}
	~mystr(){
		delete[] p;
		p = nullptr;
	}
	int length(char *s) const{
		return len;
	}
	mystr operator+(const mystr &str)const{
		mystr s;
		s.len = len + str.len;
		s.p = new char[s.len+1];

		strcpy(s.p,p);
		strcat(s.p,str.p);
		return s;
	}
	void print(){
		cout << "s = " << len << endl;
	}
	char *getc(void){
		return p;
	}
	mystr& operator=(const mystr& str) {
    if (this != &str) {
        delete[] p;
        len = str.len;
        p = new char[len + 1];
        strcpy(p, str.p);
    }
    return *this;
	}
private:
	//char *string;
	char *p;
	int len;
};

int main(int argc, char *argv[]) {
	//mystr s1;
	mystr s2("hello");
	mystr s3(s2);
//	mystr s3("world");
	mystr s4 = s2 + s3;
	
	//s4.print();

//	int l2 = s2.length(s2.getc());
	s4.print();
	//cout << "s4'length = " << s4.getlen() << endl;
    return 0;
}
