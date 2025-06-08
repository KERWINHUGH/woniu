/***************************************************
# File Name:    53-结构体指针.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 03 Mar 2025 04:59:10 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {

	int id;
	char name[32];
	char password[32];

}User ;

void toString(User *u);
 
void changeInfo(User* user){
	user->id = 999;
	strcpy(user->name, "jack"); 
	strcpy(user->password, "112233"); 

	toString(user);
}

void toString(User *u){
	printf("id: %d, name:%s,  password:%s \n", (*(u)).id  , u->name, u->password);
}


void forEachUserArray(User *user , int length){
	for(int i = 0; i < length; i++){
		toString( user + i) ;
	}
}


int main(int argc, char *argv[]) {
/*
	User u = {0};
	User *p = &u;
	changeInfo( p );
	toString(p);
*/

	User arr[] = {
		100, "jack", "123456",
		200, "rose", "223344",
		300, "lili", "223366",
		400, "jerry", "112233"
	};
	
	int length = sizeof(arr) / sizeof(arr[0]);
	forEachUserArray(arr, length);

    return 0;
}





