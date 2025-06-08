/***************************************************
# File Name:    异常处理.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月27日 星期二 16时56分15秒
****************************************************/

#include <iostream>
using namespace std;

enum class ErorrCode{
	overflow,
	underflow
};

int arrayIndex(int *arr, int index){
	if(index < 0){
		throw ErorrCode::underflow;
	}
	if(index > 9){
		throw ErorrCode::overflow;
	}
	return arr[index];
}

int main(int argc, char *argv[]) {
	int arr[] = {1, 5, 3, 7, 8, 0, 6, 4, 2 ,9};
	try{
		cout << arrayIndex(arr, 3) << endl;
		cout << arrayIndex(arr, 10) << endl;
		cout << arrayIndex(arr, -1) << endl;
	}

	catch(ErorrCode e){
		switch(e){
			case ErorrCode::overflow:
				cout << "overflow" << endl;
				exit(1);
			case ErorrCode::underflow:
				cout << "underflow" << endl;
				exit(1);
			default:
				cout << "unknow" <<endl;
				break;
		}
	}
    return 0;
}
