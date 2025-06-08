/***************************************************
# File Name:    54-homework0304.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 04 Mar 2025 09:41:47 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int searchFromString(char*, char);

void one(){
	char words[4][32]={"aabbcc","admin","aaahhh","halo"};
	int length = sizeof(words) / sizeof(words[0]);
	int total = 0;
	char target = 'a'; 
		
	for(int i = 0 ; i < length ; i++){
		total += searchFromString(words[i], target);
	}
	printf("%c在数组里一共出现了：%d次。\n", target, total );
}

int searchFromString(char* p, char x ){
	int i = 0;
	int count = 0;
	while( *(p+i) != '\0'){
		if(*(p+i) == x){
			count++;
		}
		i++;
	}
	return count;
}

char* subString(char *s, int startIndex, int endIndex){
	int targetLength = strlen(s)+1;
	int length = endIndex - startIndex + 1;
	char temp[length];
	// 判断参数是不是在合理范围之内
	if(startIndex >=0 && startIndex < targetLength && endIndex >=0 && endIndex < targetLength ){
		//for(int i = 0, j = startIndex; i <= (endIndex - startIndex) ; i++,j++){
			//temp[i] = s[j];
		//}
		for(int i = startIndex, j = 0; i < endIndex; i++, j++){
			temp[j] = *(s+i);
		}
	}else {
		puts("参数不正确！");
		return NULL;
	}
	// 尾部加结束符
	temp[length - 1] = '\0';
	char *p = temp;
	
	return p;
}

bool equals(char *one, char *two){
	int oneLength =  strlen(one);
	int twoLength =  strlen(two);
	
	if(oneLength == twoLength){
		for(int i = 0; i <= oneLength; i++){
			if(one[i] != two[i]){
				return false;
			}
		}
		return true;
	}
	
	return false;
}


/*
	加密一个字符串。加密规则是:字符串中所有字母都循环向后4个字母。如a--->e、b--->f....x--->b、y--->c、Z--->d。A--->E、B--->F......X--->B、Y--->C、Z--->D。例如:
"Hello World!"--->"Lipps Asvph!"，注意非字母字符不转换。  

- **用字符数组和 指针、利用ASCII码、**

*/
char* encrypt(char *target){
	
	int length = strlen(target) + 1;
	char temp[length];
	
	int x;
	for( int i = 0; i < length ; i++ ){
		if( (target[i] >= 'A' && target[i] <= 'Z') ||  (target[i] >= 'a' && target[i] <= 'z')){
			
			x = target[i] + 4;
			
			if(x > 90 && x < 97 || x > 122){
				x -= 26;			
			} 
			
			temp[i] = x;
		
		}else {
			temp[i] = target[i];
		}
	}
	
	temp[length -1] = '\0';
	char *p = temp;
	return p;
}



 
int main(int argc, char *argv[]) {

	//one();	

	//char *p = subString("hello,world!", 3 , 12);
	//printf("%s \n", p);  // lo,wo 

	//char a[] = "jerry1";
	//char b[] = "jerry2";
	//bool f = equals(a, b);
	//printf("%d \n", f);


	char str[] = "Hello World!";
	char *p = encrypt(str);
	printf("%s \n", p);


    return 0;
}
