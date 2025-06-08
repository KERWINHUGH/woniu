/***************************************************
# File Name:    48-指针初识.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 03 Mar 2025 11:35:19 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// hello,world  o   x    hellx,wxrld
void replace(char *str, char oldChar, char newChar){
	int i = 0;
	while( *(str+i) != '\0' ){
		if(*(str + i) == oldChar ){
			*(str + i) = newChar;
		}
		i++;
	}
}

// 我不喜欢你                      不               很        我很喜欢你。
// 1: 参数的长度要一样的。
// 2: 找到目标字符的准确索引。
// 3: 执行替换
void replace_plus(char* s, char *oldStr , char *newStr ){
	int ll = strlen(oldStr);
	printf("%d \n", ll);

	// 1: 参数的长度要一样的。
	int oldLength = 0;
	while( *(oldStr+oldLength) != '\0' ){
		oldLength++;
	}
	int newLength = 0;
	while( *(newStr+newLength) != '\0' ){
		newLength++;
	}
	if(oldLength != newLength){
		puts("对不起，两个参数长度不相符");
		return;
	}
	// 2: 找到目标字符的准确索引。
	int i = 0;
	int targetIndex = -1;
	while( *(s + i) != '\0'){
		bool f = true;
		for(int j = 0; j < oldLength; j++){
			if( *(s + i + j) != *(oldStr + j) ){
				f = false;		
			}
		}
		if(f){
			targetIndex = i;
			printf("%d -------------\n", i);
			break;
		}
		i++;
	}
	printf("找到的索引位置：%d \n", targetIndex );
	for(int i = 0; i < oldLength; i++){
		*(s + targetIndex + i) = *(newStr + i);
	}
}



int main(int argc, char *argv[]) {
	char str[] = "你是个坏蛋！";  // "hello-world"
	//replace(str , 'o' , 'x');
	
	
	char oldStr[] = "坏蛋";
	int length = sizeof(oldStr) / sizeof(oldStr[0]);
	printf("中文数组长度：%d \n", length );
	
	char newStr[] = "好人";
	
	replace_plus(str, oldStr, newStr);
	
	printf("%s \n", str);
	
	
    return 0;
}











