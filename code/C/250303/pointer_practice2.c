/***************************************************
# File Name:    pointer.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Mon 03 Mar 2025 11:50:36 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*
void replace(char *str,char oldChar,char newChar,int length)
{
	
	for(int i=0;i<length;i++)
	{
		if(*(str+i)==oldChar)
		{
			*(str+i)=newChar;
		}
	}
}
void replace1(char *str,char oldChar,char newChar)
{
	
	while(*(str+i)!='\0')
	{
		if(*(str+i)==oldChar)
		{
			*(str+i)=newChar;
		}
		i++;
	}
}
*/
/*//自己写的不对
void replace_plus(char *str,char *oldChar,char *newChar,int length)
{
	
	for(int i=0;i<length;i++)
	{
		if(*(str+i)==*(oldChar+i))
		{
			*(str+i)=*(newChar+i);
		}
	}
}
*/
//课上写的，替换一段字符内部的一段字符，可以是汉字
void replace_plus(char* s, char *oldStr , char *newStr ){
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
	/*
	char str[]="hello,world";
	int length =sizeof(str)/sizeof(str[0]);
	char *p=str;
	printf("调用前：%s\n",str);
	replace(p,'o','x',length);
	printf("调用后：%s\n",str);
	*/
	/*自己写的
	char str[]="我不爱你";
	char *oldChar=&str[1];
	char *newChar="很";
	//char *newChar=&a;
	int length =sizeof(str)/sizeof(str[0]);
	char *p=str;
	printf("调用前：%s\n",str);
	replace_plus(p,oldChar,newChar,length);
	printf("调用后：%s\n",str);
	*/
	
	
	char str[] = "你是个坏蛋！";  // "hello-world"
	//replace(str , 'o' , 'x');
	
	
	char oldStr[] = "坏蛋";
	char newStr[] = "好人";
	
	replace_plus(str, oldStr, newStr);
	
	printf("%s \n", str);
	
    return 0;
}
