## 一：字符串与字符数组

#### 3.1 字符串

字符串常量是由一对双引号括起来的，以’\0’为结束标志的一组字符数组。例如字符串"hello"在内存中按照如下方式存储：

![img](https://gitee.com/ciyeer/picgo-image/raw/master/202202221119283.jpg) 

```c
"hello world"
"123"
""
   
```



#### 3.2 字符数组的定义

在C语言中没有专门的字符串类型，通常用一个字符数组来存储一个字符串（存储字符串所包含的所有字符）。因此当一个字符串存入一个数组后，也会把一个结束符’\0’存入数组，并以此作为该字符串是否结束的标志。

字符数组是元素的数据类型为字符类型的数组,可以是一维的，也可以是多维的,它既具有普通数组的一般性质,又具有某些特殊性质。

**字符数组的定义形式如下：**

```c
char c[10]="hello";//等同于{'h','e','l','l','o','\0'};
char c[10]={'h','e','l','l','o','\0'};//'\0'对应的ASCII就是0
char d[10]="";
char e[10]={0};//\0
```

- 本质上字符串常量`比如 "hello"`就是字符数组，只不过字符数组剩余位置上默认是结束标志（`\0`,ASCII为0）
- 需要结束标志的原因在于字符数组不一定时刻数据是拉满的，实际上会有一些位置是空余的，如果没有结束标志，那么在输出字符串时会输出垃圾值（随机值），所以为了避免，那么就在进行初始化时空余的位置默认就是结束标志（必须要初始化）
- **结束标志的体现**：如果在遍历字符数组时，如果也输出了结束标志，那么终端上会显示一个空格。

#### 3.3 字符数组初始化

##### 3.3.1 逐个元素初始化

和普通数组相同，逐个为数组元素赋值。

**示例1：**

```C
char ch[6] = {‘H’,’e’,’l’,’l’,’o’,’\0’};
或
char ch[6] = "Hello";//末尾会自动填充结束标志 \0
```

![image-20240224094008823](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/image-20240224094008823.png)

**示例2：**

```C
char diamond[][5]={{'.', '.','*'},{'.','*','.','*'},{'*', '.', '.', '.' ,'*'},{'.','*', '.','*'},{'.', '.','*'}};
```

![img](https://gitee.com/ciyeer/picgo-image/raw/master/202202221119653.jpg) 



##### 3.3.2 使用字符串常量为数组元素赋值

**示例1：**

```C
char ch[6]={“abcde”};
等同于
char ch[6]=['a','b','c','d','e','\0'];
```

![image-20240224094040850](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/image-20240224094040850.png)

**示例2：** 

```C
char fruit[][7] = {"Apple", "Orange", "Grape", "Pear", "Peach"};

展开来看： 
char fruit[][7]={'A','p','p','l','e','\0','\0','O','r','a','n','g','e','\0',...}
```

遍历

```c

```

![img](https://gitee.com/ciyeer/picgo-image/raw/master/202202221119186.jpg) 



#### 3.4 字符串的输入输出

输出字符串不必使用for()循环遍历整个数组，直接使用%s格式控制符即可。

```C
printf("%s", c);
```



**例如：**

![image-20240227135658443](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/image-20240227135658443.png)

当然，我们也可以使用%s在 scanf() 函数中直接输入一个字符串：

```C
scanf("%s", c);
```

不过，使用 %s 输入整个字符串需要注意以下几点：

① 因为C语言不检查数组下标越界问题，因此如果直接键入字符串给字符数组，需要将字符数组设置的足够大，这样才不会丢失数据。

② 输入字符串给字符数组，注意 scanf() 的第二个参数不要带&(取地址符)。因为数组名就代表了数组的地址。 

③ 用scanf输入地字符串里面可能有空格、制表符等空白字符，空白字符后面地字符不能被存入到数组中。

这种情况可以通过下面方式处理（内部使用了正则表达式来完成输入字符的限制要求）

``` c
int main() {
	char name[32];
	puts("请输入名字：");
	scanf("%s",name);             // %s 整个输入作为一个字符串，尾部加 '\0'
	//scanf("%4s", name );        // %ns n是一个整数，限制输入的一个字符串长度
	//scanf("%[a-z|A-Z]", name ); // %[a-z|A-Z] [a-z]是一个正则,代表限制的输入字符
	//scanf("%[^=]", name );      // 读取任意多的字符，直到=停止　
	//scanf("%[^\n]", name );     // 读取任意多的字符，直到换行　
	//scanf("%5[^\n]", name );    // 读取5个任意字符，直到换行
    
	printf("得到的名字是：%s \n",name); 
    
    return 0;
}
```





#### 3.5 字符串处理函数;

- strcmp
- strcpy
- strcat
- strlen

##### 3.5.1 字符串拷贝 strcpy 与 strncpy

- 尽量使用strncpy，同时预留一个位置给结束标志

![image-20240227121514542](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/image-20240227121514542.png)



**函数说明：**

- [1] strcpy 把 src 所指向的字符串复制到 dest。

- [2] strncpy 把 src 所指向的字符串复制到 dest, 最多复制 n 个字符。

**参数：**

- dest : 指向用于存储复制内容的目标字符数组。
- src : 要复制的字符串(可以是字符串常量也可以是字符数组)
- n ：指定要从源中复制的字符数。

**返回值：**

- 返回指向目标字符串dest的指针

**注意：目标数组 dest 不够大，而源字符串的长度又太长，可能会造成缓冲溢出的情况。**

![image-20240227122059647](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/image-20240227122059647.png)



##### 3.5.2 字符串拼接 strcat 与 strncat

![image-20240227121442944](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/image-20240227121442944.png)

 **函数说明：**

- [1] strcat把 src 所指向的字符串追加到 dest 所指向的字符串的结尾。

- [2] strncat把 src 所指向的字符串追加到 dest 所指向的字符串的结尾，直到 n 字符长度为止。

**参数：**

- dest ：指向目标数组，该数组包含了一个 C 字符串，且足够容纳追加后的字符串。
- src ：指向要追加的字符串
- n : 要追加的最大字节数

**返回值：**

- 返回 指向目标字符串dest的指针

**示例：**

![image-20240227142911442](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/image-20240227142911442.png)

越界会报如下错误:

![image-20240227141403500](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/image-20240227141403500.png)



##### 3.5.3 字符串比较

> strcmp、strncmp、strcasecmp、strncasecmp

![image-20240227121618561](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/image-20240227121618561.png)

![image-20240227121654539](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/image-20240227121654539.png)



**函数说明：**

	[1] strcmp把 s1 所指向的字符串和 s2 所指向的字符串进行比较。
	
	[2] strncmp把 s1 所指向的字符串和 s2 所指向的字符串进行比较,最多比较前 n 个字符
	
	[3] strcasecmp把 s1 所指向的字符串和 s2 所指向的字符串进行比较(忽略大小写)。
	
	[4] strncasecmp把 s1 所指向的字符串和 s2 所指向的字符串进行比较(忽略大小写)，最多比较前 n 个字节

**参数：**

- s1 ：要进行比较的第一个字符串。
- s2 ：要进行比较的第二个字符串。
- n ：要比较的最大字符数。

**返回值：**

- 如果返回值 < 0，则表示 s1 小于 s2。

- 如果返回值 > 0，则表示 s1 大于s2。

- 如果返回值 = 0，则表示 s1 等于 s2。

**示例：** 

![image-20240104110944921](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/20240104110945.png)



##### 3.5.4 字符串长度 strlen

![image-20240227145429321](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/image-20240227145429321.png)

 

**函数说明：**

> 计算字符串 s 的长度，直到空结束字符’\0’，但不包括空结束字符’\0’。

**参数：**

> str : 要计算长度的字符串。

**返回值：**

> 该函数返回字符串的长度，但不包括’\0’。

**示例：**

![image-20240227145401173](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/image-20240227145401173.png)

计算结果：

![image-20240227145519876](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/image-20240227145519876.png)

**注意：sizeof() 与 strlen() 的区别：**

> sizeof()的长度是整个字符数组的总长度，其中包括'\0'；而strlen()不包括'\0'。



## 二：c语言字符串api大全

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















