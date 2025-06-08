/***************************************************
# File Name:    31-字符串.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Wed 26 Feb 2025 02:04:09 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void one(){
	
	char str[32] = "hello";  // 数组的长度是6 ， 字符串的长度是：5
	
	printf("字符串的长度（不含结束符）：%ld \n", strlen(str) );
	
	// 字符串的复制：
	strcpy(str, "world!" );
	printf("字符串复制后：%s \n", str );
	
	strncpy(str, "jerry" , 3 );
	printf("strncpy字符串复制后：%s \n", str );
	
	// 字符串的比较：
	char one[] = "zzz" ;
	char two[] = "zzz" ;
	
	int result = strcmp(one, two);
	
	if(result < 0){
		printf("%s 比 %s 小 \n", one, two);
	}else if(result > 0){
		printf("%s 比 %s 大 \n", one, two);
	}else{
		printf("%s 和 %s 相等 \n", one, two);
	}

	puts("------- 需求：把用户按名称排序：  年龄排序， 工资排序--------------");
	char names[][32] = {"jerry","alice", "mike", "jack","lili"};
	int length = sizeof(names) / sizeof(names[0]);
	
	char temp[32];
	for(int i = 0; i < length - 1; i ++){
		for(int j = i+1 ; j < length; j++){
			if(strcmp( names[i], names[j] ) > 0){
				strcpy(temp, names[i]);
				strcpy(names[i], names[j]);
				strcpy(names[j], temp);
			}
		}
	}
	
	for(int i = 0; i < length; i ++){
		printf("%s\n", names[i]);
	}
	
	puts("------------- strcat ----------------");
	char a[32] = "jack";
	char b[] = " love rose";
	
	char *newStr = strcat(a, b);
	
	printf("字符串拼接后：%s \n", a);
	printf("字符串拼接后(指针)：%s \n", newStr );
	
	
	
	puts("------------- strchr ----------------");
	char str2[] = "hello,world!";
	
	char tmp = 'x';
	
	char *p = strchr(str2 , tmp );

	if(p != NULL){
		printf("---%c===\n", *p );
	}else {
		puts("没找到字符！");
	}

}

// 字符串练习：
/*
	定义一个二维的字符数组，最多10个字符串
		1.自行输入多个字符串并保存到数组中
		2.完成对二维字符数组的排序
		3.将最小的字符串和最大的字符串进行合并并输出
		4.获取整个二维字符数组一共有多少个有效字符
*/
void two(){
	char ss[5][32] = {0};
	int length = sizeof(ss) / sizeof(ss[0]);
	
	for(int i = 0; i < length; i++){
		printf("请输入%d号位置的字符：\n",i);
		
		scanf(" %s", ss[i] );
	}
	puts("----排序-----");
	
	char temp[32];
	for(int i = 0; i < length - 1; i ++){
		for(int j = i+1 ; j < length; j++){
			if(strcmp( ss[i], ss[j] ) > 0){
				strcpy(temp, ss[i]);
				strcpy(ss[i], ss[j]);
				strcpy(ss[j], temp);
			}
		}
	}
	puts("---- 遍历 ----");
	int total = 0;
	for(int i = 0; i < length; i++){
		total += strlen(ss[i]);
		printf("%s\n",ss[i]);
	}
	printf("所有的有效字符数是：%d\n", total );
	
	puts("---- 合并 ----");

	strcat(ss[0], ss[length-1]);
	printf("合并后：%s\n",ss[0]);
	
	


}


 
int main(int argc, char *argv[]) {
	
	two();

    return 0;
}























