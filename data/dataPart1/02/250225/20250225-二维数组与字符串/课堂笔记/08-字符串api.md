#### c语言字符串api大全

以下内置函数放在`string.h`中，需要再c文件中引入才能使用

#### 常用字符串api详解

##### 1、strcpy

**概念：** `strcpy` 函数用于将一个字符串复制到另一个字符串中，包括结束字符 `\0`。

**语法：**

```c
char *strcpy(char *dest, const char *src);
```

**参数：**

- `dest`: 目标字符串的指针。
- `src`: 源字符串的指针。

**返回值：** 返回指向目标字符串 `dest` 的指针。

```c
char name[16];
//把admin赋给name
strcpy(name,"admin");
printf("%s",name);//admin
```



------

##### 2、strncpy

**概念：** `strncpy` 函数类似于 `strcpy`，但是它将最多复制 `n` 个字符。如果 `src` 的长度小于 `n`，剩余的 `dest` 将用 `\0` 填充。

**语法：**

```c
char *strncpy(char *dest, const char *src, size_t n);
```

**参数：**

- `dest`: 目标字符串的指针。
- `src`: 源字符串的指针。
- `n`: 要复制的最大字符数。

**返回值：** 返回指向目标字符串 `dest` 的指针。

```c
char name[16];
//把admin赋给name
strncpy(name,"admin",3);
printf("%s",name);//adm
```

注意：如果n小于变量允许的字符数量，那么就要留意给字符数组设置一个结束字符`\0`,建议再定义字符数组时就进行初始化,不然有可能会输出乱码

------

##### 3、strcat

**概念：** `strcat` 函数将 `src` 字符串连接到 `dest` 字符串的末尾，覆盖 `dest` 的 `\0` 并在末尾添加一个新的 `\0`。

**语法：**

```c
char *strcat(char *dest, const char *src);
```

**参数：**

- `dest`: 目标字符串的指针。
- `src`: 源字符串的指针。

**返回值：** 返回指向目标字符串 `dest` 的指针。

```c
char ch1[16]="hello";
char ch2[16]="woniu";
strcat(ch1,ch2);
printf("%s",ch1);
```



------

##### 4、strcmp

**概念：** `strcmp` 函数比较两个字符串。比较是基于字符串中字符的无符号字符集值。

**语法：**

```c
int strcmp(const char *s1, const char *s2);
```

**参数：**

- `s1`: 第一个字符串的指针。
- `s2`: 第二个字符串的指针。

**返回值：** 如果 `s1` 和 `s2` 字符串相等，返回 `0`；如果 `s1` 小于 `s2`，返回小于 `0` 的值；如果 `s1` 大于 `s2`，返回大于 `0` 的值。

------

##### 5、strlen

**概念：** `strlen` 函数计算字符串的长度，直到但不包括结束字符 `\0`。

**语法：**

```c
size_t strlen(const char *s);

char name[16]="hello"; {'h','e','l','l','o','\0'};
```

**参数：**

- `s`: 要计算长度的字符串指针。

**返回值：** 返回字符串的长度，不包括 `\0`,printf里用`%lu`来接受。

------

##### 6、strchr

**概念：** `strchr` 函数在字符串 `s` 中查找第一次出现的字符 `c`，返回指向它的指针。

**语法：**

```c
char *strchr(const char *s, int c);
```

**参数：**

- `s`: 要搜索的字符串。
- `c`: 要查找的字符，以其 `int` 形式传递，但是内部转换为 `char`。

**返回值：** 如果找到指定的字符，函数返回指向该字符的指针；如果未找到，返回 `NULL`。



#### 字符串使用例子

```c
/***************************************************
# File Name:    41-字符串.c
# Author:       SuperYu
# Mail:         yujian001002@163.com
# Created Time: 2024年12月30日 星期一 11时42分42秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
	
	//char name[] = "hello";
	//char name[] = {'h','e','l','l','o','\0'};

	char one[32] = "aaaccc";
	char two[32] = "aaabbb";
	
	//int length = sizeof(name) /sizeof(name[0]);
	//printf("长度是:%d ,值是:%s \n",length, name);
	
	puts("----------- 比较字符串strcmp: ----------------");
	int result = strcmp(one, two);
	printf("比较的结果:%d \n", result);
	
	puts("----------- 比较字符串strncmp: ----------------");
	
	result = strncmp(one, two, 3);
	printf("比较的结果:%d \n", result);
	
	puts("----------- 字符串复制 strcpy: ----------------");
	// 把字符串"jack" ,复制进 one 中
	strcpy(one, "jack");
	
	printf("%s \n", one);
	
	puts("----------- 字符串复制 strncpy: ----------------");
	
	strncpy(two, "hello,world!", 6);
	printf("%s \n",two);
	
	puts("----------- 字符拼接 strcat: ----------------");

	char src[32] = "hello,wrold!";
	char desc[32] = "aabb";
	
	strcat(desc, src);

	printf("字符串拼接的结果:%s \n", desc);
	
	for(int i = 0; i<32; i++){
		if(desc[i] != '\0'){
			printf("索引:%d , %c \n",i, desc[i]);
		}
	}
	
	puts("----------- 字符串值的长度: strlen: ----------------");
	
	printf("str字符串的真实长度是:%ld \n", strlen(src) );
	
	
	puts("----------- 查找字符串中第一次出现的字符 : strlen: ----------------");
	
	char *p = strchr(src, 'x');
	
	printf("%s \n", p);
	
	
    return 0;
}
```



##### 字符串练习

```c
定义一个二维的字符数组，最多10个字符串
1.自行输入多个字符串并保存到数组中
2.完成对二维字符数组的排序
3.将最小的字符串和最大的字符串进行合并并输出
4.获取整个二维字符数组一共有多少个有效字符
```















