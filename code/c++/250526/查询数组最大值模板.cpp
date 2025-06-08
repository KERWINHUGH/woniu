/***************************************************
# File Name:    查询数组最大值模板.cpp
# Author:       zhudongdong
# Mail:        1660397971 @qq.com
# Created Time: 2025年05月26日 星期一 11时26分24秒
****************************************************/

#include <iostream>
using namespace std;

#define LENGTH_ERROR -1

template <class T>
T selectMax(T *arr, int length){
	if(length < 0){
		return LENGTH_ERROR;
	}
	int index = 0;

	for( int i = 1; i < length; i++){
		if(arr[index] < arr[i]){
			arr[index] = arr[i];
		}
	}
	return arr[index];
}

int main(int argc, char *argv[]) {
	char arr[] = {'a','f','g','u','e','d'};
	int length = sizeof(arr)/sizeof(arr[0]);
	cout << "最大值为 ：" << selectMax(arr,length) << endl;
    return 0;
}
