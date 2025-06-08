/***************************************************
# File Name:    48-指针初识.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 03 Mar 2025 11:35:19 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void one(){
	double arr[6] = {3.2 , 4.1, 8.8, 9, 0.7 , 6.66};
	double *p = arr;
	int length = sizeof(arr) / sizeof(arr[0]);
	for(int i = 0; i < length; i++){
		printf("%f \n", *(p+i) );
	}
}

void two(int *start_p, int *end_p){
	
	int spance = end_p - start_p;
	
	for(int i = 0; i <= spance; i++){
		printf( "%d \n", *(start_p + i) );
	}
}

int main(int argc, char *argv[]) {
	//one();
	
	int arr[] = { 11,22,33 };

	two(arr, &arr[2]);



    return 0;
}











