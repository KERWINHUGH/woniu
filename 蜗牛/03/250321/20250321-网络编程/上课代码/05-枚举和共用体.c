/***************************************************
# File Name:    05-枚举和共用体.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 21 Mar 2025 10:40:51 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct User {
	char name[32];
	int age;
	double height;
}User;
// 共用体的特点：所有的成员共用一块内存， 以最大字节数的成员为准。
typedef union TestUnion{
	short a;
	
	float b;

}TestUnion;


// 枚举：
enum Gender {
	// 如果没有设置值：默认从0开始，后面依次累加
	// 如果设置了值，则从设置的值开始
	male = 1 , female
};


int main(int argc, char *argv[]) {
	puts("------------------- 枚举 ------------------------");
	enum Gender a = male;
	//enum Gender b = female;
	
	switch(a){
		case male:
			puts("---是男性---");
			break;
		case female:
			puts("---是女性---");
			break;
	}
	
	
	
	
	//printf("%d \n", a);
	//printf("%d \n", b);
	


	puts("------------------- 共用体 ------------------------");
	//printf("%ld \n", sizeof(User));
	//printf("%ld \n", sizeof(TestUnion));
	
	// 初始化共用体时，只能一个成员有值。 如果同时赋值，后面覆盖前面。
	TestUnion t = {
			.b = 88.88,
			.a = 99
	};
	printf("共用体：a=%d ， b=%f \n", t.a, t.b );
	t.b = 88.99999;
	printf("共用体：a=%d ， b=%f \n", t.a, t.b );

    return 0;
}






