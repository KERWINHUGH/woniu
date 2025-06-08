/***************************************************
# File Name:    hmwk.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Mon 03 Mar 2025 06:55:13 PM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


/*已知有一个字符串数组，记录字母a出现的总次数并输出，使用指针
- 需要封装成函数
- 写一个函数，实现统计数组里指定字符出现的次数功能
- 使用指针完成
*/
int find(char *arr,char character)
{
	int length=0;
	int count =0;
	while(*(arr+length)!='\0')
	{
		length++;
	}
	for(int i=0;i<length;i++)
	{
		if(*(arr+i)=='a')	
		{
			count++;
		}	
	}
	return count;
}


/*写一个函数实现截取字符的功能( 使用指针完成 )：

如：有字符 “hello,world”  

int startIndex = 2;          int endIndex = 6;

结果： "llo,"
*/
void Cut(char *arr,int startIndex,int endIndex)
{
	int length=0;
	int count =0;
	while(*(arr+length)!='\0')
	{
		length++;
	}
	for(int i=startIndex;i<endIndex;i++)
	{
		printf("%c",*(arr+i));
	}
	printf("\n");
}
char* subString(char *s,int startIndex,int endIndex)
{
	int targetLength = strlen(s);
	int length = endIndex-startIndex+1;
	char temp[length];
	
	if(startIndex>=0&&startIndex<targetLength&&endIndex>=0&&endIndex<targetLength)
	{
		for(int i=startIndex,j=0;i<endIndex;i++,j++)
		{
			temp[j]=*(s+i);
		}
	}else
	{
		puts("参数不正确！");
		return NULL;
	}
	temp[length-1]='\0';
	cahp *p=temp;
	return p;
}

/*写一个名为equals(s1, s2) 的函数，实现比较两个字符串的功能

- 如果两个字符串的内容相等，则返回true, 否则返回false 

- 使用指针完成
*/
/*
int equals(char *s1,char *s2)
{

	int length1=0;
	while(*(s1+length1)!='\0')
	{
		length1++;
	}
	int length2=0;
	while(*(s2+length2)!='\0')
	{
		length2++;
	}
	int count1 =0;
	if(length1!=length2)
	{
		if(length1>length2)
		{
			for(int i=0;i<length1;i++)
			{
				count1+=strcmp(*(s1+i),*(s2+i))
			}
		}
		
	}else
	{
		for(int i=0;i<length1;i++)
		{
			count1+=strcmp(*(s1+i),*(s2+i))
		}
	}

	int index=-1; 
   	int count = strcmp(*s1,*s2)
	if(count==0)
	{
		index=0;
		printf("两个字符串相等");
	}else if(count>0)
	{
		index=1;
		printf("%s比%s大",*s1,*s2);
	}else
	{
		printf("%s比%s小",*s1,*s2);
	}
	return index;
	
}
*/
int equals(char *s1, char *s2){
	int index = 0;
	
	int countA = 0;
	int countB = 0;
	while( *(s1+index) != '\0' && *(s2+index) != '\0' ){
		if(*(s1+index) > *(s2+index) ){
			return 1;
			
		}else if(*(s1+index) < *(s2+index) ){
			return -1;
			
		}else if(*(s1+index) == *(s2+index) ){
			
			countA += *(s1+index);
			countB += *(s2+index) ;
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

/*加密一个字符串。加密规则是:字符串中所有字母都循环向后4个字母。如a--->e、b--->f....x--->b、y--->c、Z--->d。A--->E、B--->F......X--->B、Y--->C、Z--->D。例如:
"Hello World!"--->"Lipps Asvph!"，注意非字母字符不转换。  

- **用字符数组和 指针、利用ASCII码、**
*/
void encipher(char *str)
{
	int length=0;
	while(*(str+length)!='\0')
	{
		length++;
	}
	//char enc[length];
	//char *p=enc;
	for(int i=0;i<length;i++)
	{
		if((*(str+i)>='a'&&*(str+i)<'w')||(*(str+i)>='A'&&*(str+i)<'W'))
		{
			*(str+i)+=4;
		}else if((*(str+i)>='w'&&*(str+i)<='z')||(*(str+i)>='W'&&*(str+i)<='Z'))
		{
			if(*(str+i)='w')
			{
				*(str+i)='a';
			}else if(*(str+i)='x')
			{
				*(str+i)='b';
			}else if(*(str+i)='y')
			{
				*(str+i)='c';
			}else if(*(str+i)='z')
			{
				*(str+i)='d';
			}else if(*(str+i)='W')
			{
				*(str+i)='A';
			}else if(*(str+i)='X')
			{
				*(str+i)='B';
			}else if(*(str+i)='Y')
			{
				*(str+i)='C';
			}else if(*(str+i)='Z')
			{
				*(str+i)='D';
			}
		}
		printf("%c",*(str+i));
	}
	printf("\n");
	//return enc;
}
/*
已知有字符串：
char str[] = "at7cHa63OPbQ81b";
- 一共有多少个字符组成？
- 其中有几个数字？
- 大写字母有几个？
- 小写字母有几个？
*/
void soulute(char *str)
{
	//第一问
	int length=strlen(str);
	printf("%s共有%d个字符\n",str,length);
	//第二问
	int count1 =0;
	for(int i=0;i<length;i++)
	{
		if(*(str+i)>='1'&&*(str+i)<='9')
		{
			count1++;
		}
	}
	printf("%s共有%d个数字\n",str,count1);
	//第三问
	int count2 =0;
	for(int i=0;i<length;i++)
	{
		if(*(str+i)>='A'&&*(str+i)<='Z')
		{
			count2++;
		}
	}
	printf("%s共有%d个大写字母\n",str,count2);
	//第四问
	int count3 =0;
	for(int i=0;i<length;i++)
	{
		if(*(str+i)>='a'&&*(str+i)<='z')
		{
			count3++;
		}
	}
	printf("%s共有%d个小写字母\n",str,count3);
}
/*
实现利用指针倒序遍历一个数字数组
*/
void reverse(char *str)
{	
	int length=0;
	while(*(str+length)!='\0')
	{
		length++;
	}
	for(int i=length-1;i>=0;i--)
	{
		printf("%c\n",*(str+i));
	}
}
/*
将字符串'Computer Science"赋给一个字符数组，然后从第一个字母开始间隔的输出该字符串，用指针完成。
*/
void interval(char *str)
{
	int length=0;
	while(*(str+length)!='\0')
	{
		length++;
	}
	char temp[length];
	char *p =temp;
	for(int i=1;i<length;i+=2)
	{
		//方法一
		/*
		if(i%2==0)
		{
			printf("%c",*(str+i));	
		}
		printf("\n");
		*/
		//方法二
		printf("%c",*(str+i));
		printf("\n");
		//方法三
		/*
		printf("%c",*(str+i+1));
		printf("\n");
		//if(i<length-1)
		//str++;*/

	}
}

int main(int argc, char *argv[]) {

/*
	//hmwk1:记录字母a出现的总次数并输出，使用指针
	char words[4][32]={"aabbcc","admin","aaahhh","halo"};
	int length1=sizeof(words)/sizeof(words[0]);
	int length2=sizeof(words[0])/sizeof(words[0][0]);
	char *w=NULL;
	int count=0;
	
	for(int i=0;i<length1;i++)
	{
		w=words[i];
		count += find(w,'a');	
	}	
	printf("数组中出现%d次%c \n",count,'a');
*/	
/*
	//hmwk2:截取字符的功能，使用指针
	char words[]={"hello,world"};
	char *c=words;
	Cut(c,2,6);
	
	char *p=subString("hello,world!,3,12");
	printf("%s \n",p);
*/
/*
	//hmwk3:截取字符的功能，使用指针
	char wordOne[]={"hello,world"};
	char wordTwo[]={"hello,world"};
	char *w1=wordOne;
	char *w2=wordTwo;	
	int val=equals(w1,w2);
	if(val>0)
	{
		printf("%s比%s大\n",w1,w2);
	}
	else if(val<0)
	{
		printf("%s比%s小\n",w1,w2);
	}else
	{
		printf("%s与%s相等\n",w1,w2);
	}
*/

	//hmwk4:加密一个字符串，使用指针	
	char word[]={"123HeLlO56,WorLd89."};
	char *w=word;
	printf("调用前字符串：%s\n",w);
	
	encipher(w);
	//printf("调用后字符串：%s\n",p);

/*
	//hmwk5:已知有字符串	
	char str[] = "at7cHa63OPbQ81b";
	char *s=str;
	soulute(s);
*/
/*
	//hmwk6:实现利用指针倒序遍历一个数字数组
	char str[] = "12345689";
	char *s=str;
	reverse(s);
*/	
/*
	//hmwk7:将字符串'Computer Science"赋给一个字符数组,第一个字母开始间隔的输出该字符串
	char str[] = "Computer Science";
	char *s=str;
	interval(s);
*/	
    return 0;
}
