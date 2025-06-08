## 一、makefile基础

##### 1. makefile概念

（1）概念

**Makefile** 是一个特殊的文件，它是由 `make` 工具用来自动化编译和构建c语言程序的过程。

`make`是一个自动化构建工具。它可以实现自动编译和链接c程序的源代码并生成可执行程序或者其他所需的输出。即使**用make可以快捷实现c语言程序的编译和执行。**

（2）工作流程

`make` 工具使用一个叫做 `Makefile` 的文件来定义项目中的构建规则和依赖关系。通过在项目目录中执行 `make` 命令，`make` 工具读取 `Makefile`，然后执行定义好的规则以构建项目指定的目标



##### 2.makefile安装

```bash
sudo apt install make
```

- 或者如果之前已经安装了`build-essential`,就无需再额外安装make



##### 3.makefile基本使用

（1）主要流程

- 在c文件同目录中编写makefile文件
- 执行make命令来生成可执行文件，并且可以立即执行
- 可选：执行make clean命令来清理之前生成的文件，方便下次生成

（2）一个基础的makefile

```bash
# 定义生成的可执行文件  
all: demo  
  
# 定义demo依赖的对象文件  
demo: 01-hello.o  
	gcc -o demo 01-hello.o  
  
# 定义01-hello.o的依赖和构建方法  
01-hello.o: 01-hello.c  
	gcc -c 01-hello.c -o 01-hello.o  
  
# 清理生成的文件  
clean:  
	rm -f demo 01-hello.o
```

在这个Makefile中，目标 `all` 依赖于 `demo`，而 `demo` 又依赖于 *01-hello.o*

clean 是一个额外的目标，用以清除编译生成的所有文件，以便重新开始一个干净的构建过程

make执行某个目标命令：

```bash
make all       (执行编译)
或
make clean     (清除文件)
```

- 执行同目录下的makefile文件里的all目标。

<font color='red'>注意：</font>

> - 使用makefile文件时，makefile文件要和 .c 源文件放在同一目录下。
> - 注意 ：如果有同名的文件，或目录，可能执行失败。

<font color='red'>总结</font>：make本质上就是给想要执行的linux指令提供一个别名。

- 改进版makefile

  > 前面的文件，步骤较多，操作太多，我们可以改进成一句执行命令：

  ``` bash
    1 # 定义生成的可执行文件                                                      
    2 all: demo
    3 
    4 # 定义demo的依懒对象文件　
    5 demo:
    6     gcc 02-hello.c -o demo
    7     ./demo
  
  ```



##### 4.makefile基本配置

- 定义变量

> 这样修改后，使用上更灵活

```bash
# 定义变量，一般大写 
TARGET=01-hello

# 定义生成的可执行文件 
all: demo  
  
# 定义demo依赖的对象文件  
demo: $(TARGET).o  
	gcc -o demo $(TARGET).o  
  
# 定义01-hello.o的依赖和构建方法  
$(TARGET).o: $(TARGET).c  
	gcc -c $(TARGET).c -o $(TARGET).o  
  
# 清理生成的文件  
clean:  
	rm -f demo $(TARGET).o
```

变量可以在Makefile的任何地方定义，但通常它们定义在文件的顶部，这样它们就容易被找到和修改。如果变量在第一次使用之前定义，那么在整个Makefile中的任何地方都可以使用它们



- 最终版：makefile文件修改为：

  > 这样写，每次执行不同文件时，还是要修改第二行的变量 TARGET的值。

``` makefile
# 定义变量，一般大写 
# TARGET=01-hello  // 变量　注释掉，使用的时候以参数的方式传进来
# 定义生成的可执行文件 
all: $(TARGET)  
  
# 定义demo依赖的对象文件  
$(TARGET): $(TARGET).o  
	gcc -o $(TARGET) $(TARGET).o  
	# 可以设置编译完后直接运行
	./$(TARGET)
  
# 定义01-hello.o的依赖和构建方法  
$(TARGET).o: $(TARGET).c  
	gcc -c $(TARGET).c -o $(TARGET).o  
  
# 清理生成的文件  
clean:  
	rm -f $(TARGET) $(TARGET).o
```

- 使用

``` bash
# 使用命令注入的方式，把TARGET的值注入进来
make TARGET=01-hello
```



- 可以隐藏执行的过程：

> 要隐藏的命令，前面都加上 @ 符号

``` bash
  1 # 定义变量，一般大写                                                        
  2 # TARGET=01-hello  // 变量　注释掉，使用的时候以参数的方式传进来
  3 # 定义生成的可执行文件 
  4 all: $(name)  
  5   
  6 # 定义demo依赖的对象文件  
  7 $(name): $(name).o  
  8     @gcc -o $(name) $(name).o  
  9     @# 可以设置编译完后直接运行并删除不需要的程序
 10     @rm -f $(name).o
 11     @./$(name)
 12   
 13 # 定义01-hello.o的依赖和构建方法  
 14 $(name).o: $(name).c  
 15     @gcc -c $(name).c -o $(name).o  
 16   
 17 # 清理生成的文件  
 18 clean:  
 19     @rm -f $(name) $(name).o
 20 

```

- 最终精简版：

``` bash
 # n=02-hello
 
# 定义生成的可执行文件
all: demo
# 定义demo的依懒对象文件　
demo:
	@gcc $(n).c -o $(n)  
	@./$(n)
	@rm -f ./$(n) 
    
   
```

















