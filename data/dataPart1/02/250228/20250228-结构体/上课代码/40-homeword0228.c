/***************************************************
# File Name:    40-homeword0228.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Fri 28 Feb 2025 10:53:32 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool indexOf(char target[], char src[]);

/*
	- 一共有多少人？
	- 第五个人是谁？
	- 姓名以j开头的人有哪些？ （如果中文如何处理？）
	- 姓名以j开头的人有几个？
*/
void one( char src[] ){
	char str[][32] = {"jack","lili","赵四","jerry","李小丽", "赵强" , "json"};
	int oneLength = sizeof(str) / sizeof(str[0]);
	
	// 1:
	printf("一共有 %d 个人\n", oneLength);
	
	// 2:
	int n = 5;
	if(n <= oneLength -1 && n >= 0){
		printf("第五个人是:%s \n", str[n-1]);
	
	}else {
		printf("对不起，数组的位置范围是：1 ~ %d \n", oneLength );
	}
	
	// 3:
	/*
	int count = 0;
	for(int i = 0; i < oneLength; i++){
		if(str[i][0] == 'j'){
			printf("%s \n", str[i]);
			count++;
		}
	}
	*/
	// 第二种方式（中文也可以）：
	int count = 0;
	for(int i = 0; i < oneLength; i++){
		if(indexOf(str[i], src )){
			count++;
		}
	}
	
	printf("以%s开头的有：%d个。\n", src,  count);
}

//自己写一个函数, 判断一个字符串，是否以另一个字符串开头：
bool indexOf(char target[], char src[]){
	int index = 0;
	while( target[index] != '\0' && src[index] != '\0' ){
		if(target[index] != src[index]){
			//printf("target:--%c==  , str:--%c==", target[index], src[index]);
			return false;
		}
		index++;
	}
	return true;
}

// 拆数字：方法一：用字符串：
void splitNumberByString(){
	char number[32];
	puts("请输入数字：");
	scanf("%s", number);
	
	int length = strlen(number);
	
	for(int i = 0; i < length; i++){
		if(i != length -1){
			printf("%c***", number[i]);
		}else {
			printf("%c", number[i]);
		}
	}
	printf("\n");
}
// 拆数字：方法二，用数学方式：
void splitNumberByInt(){
	int number;
	puts("请输入数字：");
	scanf("%d", &number);
	// 1: 得到数字的位数
	int length = 1;
	int temp = number;
	while( (temp /= 10) != 0 ){
		length++;
	}
	printf("数字的长度：%d \n", length );
	int arr[length];
	// 2: 拆数字，并把拆下的数字存起来
	int x = 10;
	int y = 1;
	for(int i = length -1; i >= 0; i--){
		arr[i] = number % x / y;
		x *= 10;
		y *= 10;
	}
	// 3: 遍历	
	for(int i = 0; i < length; i++){
		if(i != length -1){
			printf("%d***", arr[i]);
		}else {
			printf("%d", arr[i]);
		}
	}
	printf("\n");
}

// 自定义一个函数，实现系统 strcmp()的类似功能
int my_strcmp(char s1[], char s2[]){
	int index = 0;
	
	int countA = 0;
	int countB = 0;
	while( s1[index] != '\0' && s2[index] != '\0' ){
		if(s1[index] > s2[index]){
			return 1;
			
		}else if(s1[index] < s2[index]){
			return -1;
			
		}else if(s1[index] == s2[index]){
			
			countA += s1[index];
			countB += s2[index];
		}
		index++;
	}
	
	if(countA > countB){
		return 1;
	}else if(countA < countB){
		return -1;
	}
	
	return 0;
}
// 自定义一个函数，实现系统 strlen()的类似功能
int my_strlen(char ss[]){
	
	int length = 0;
	int i = 0;
	while(ss[i] != '\0'){
		length ++;
		i++;
	}
	return length;
}

 
int main(int argc, char *argv[]) {
	/*
	char target[] = "张三";
	char src[] = "李";
	int result = indexOf( target , src );
	printf("结果：%d \n", result);
*/
	//one("j");

	//splitNumberByString();
	
	//splitNumberByInt();
	
	/*
	char a[] = "axy";
	char b[] = "abc";
	
	int result = my_strcmp(a, b);
	printf("my结果：%d \n", result);
	
	puts("-----------------------------");

	int result2 = strcmp(a, b);
	printf("系统结果：%d \n", result2);
	*/
	char name[32] = "";
	int len = my_strlen( name );
	printf("长度：%d \n",len);
	

    return 0;
}
