- linux指令的学习和练习



#### 一、 Linux终端操作和使用权限

##### 1 打开终端

> ###### 1. 右键最后打开终端  
>
> ###### 2. 打开应用程序面板(左下角) 
>
> ###### 3. ctrl + alt + t(快捷键)

##### 2 调整终端

> ###### 放大：ctrl + shift + " + "
>
> ###### 缩小：ctrl + " - "

##### 3 关闭终端

> ##### 1. exit
>
> ##### 2. alt + F4



##### 4 Linux使用权限(两种)

- ##### 5.4.1 超级管理员权限：以 `#` 结尾的是超级管理员权限

- ##### 5.4.2 普通用户权限：以 `$` 结尾的是普通用户权限

![image-20221123095417018](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/20240103165923.png)

- ##### 5.4.3 超级管理员和普通用户权限的切换：

  - ###### 普通用户向超级管理员权限切换

    - `sudo su`
    - `su root`

  - ###### 超级管理员权限向普通用户切换

    - `exit`
    - `su` + 用户名(`su ciyeer`)

- ##### 5.4.4 sudo 临时权获得管理员权限，放在需要执行的命令之前

  - 输入 sudo 命令后，需要输入 Linux 系统的登录密码才可执行该指令。

  - 注意：Linux 系统内输入密码不回显

- ##### 5.4.5 passwd 修改用户密码

  - 语法格式：`passwd` + 用户名

  ![image-20240102231704111](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/20240103093630.png)

  - 注意如果设置 root 用户密码，需要在命令前加 sudo

  ![image-20240102232041387](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/20240103093626.png)



##### 5.命令提示符 

<span style="font-size:16px;color:black;font-weight:bold;">命令提示符标识了命令行的开始。用户在提示符后面输入一条命令并按【Enter】键，完成向系统提交指令。</span>

<span style="font-size:16px;color:black;font-weight:bold;">命令提示符格式：</span>

![image-20221123095710787](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/20240103165750.png)

![image-20221123094433194](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/20240103165822.png)

<span style="font-size:16px;color:black;font-weight:bold;">如下图所示：</span>

**![image-20240102231203544](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/20240103093601.png)**

<span style="font-size:16px;color:black;font-weight:bold;">用户名: ciyeer</span>

<span style="font-size:16px;color:black;font-weight:bold;">主机名：ubuntu</span>

<span style="font-size:16px;color:black;font-weight:bold;">当前目录是用户目录，即 `/home/ciyeer`</span>



#### 二、 Linux常用命令（指令）

根据指令操作对象和动作类型不同，分为以下几类：

- 文件操作指令：这类指令用于管理文件系统中的文件和目录。如ls、cd、cmd、mkdir、touch等
- 文本处理指令：用于查看、编辑、排序、比较和搜索文本文件的内容等。比如cat、more、less、tail、sort、grep、find、vim等
- 系统管理指令：系统操作相关指令。比如top、ps、free、kill、mount等
- 网络操作指令：用于网络配置和管理方面。比如ping、ifconfig、netstat等
- 软件包指令：对于软件管理命令。比如apt
- 用户和权限指令：设置用户和权限相关。比如chmod、su等
- 其他指令：比如压缩(tar)等。

| 命令             | 描述                             | 常用参数（示例）                    |
| ---------------- | -------------------------------- | ----------------------------------- |
| `ls`             | 列出目录内容                     | `-l` 列出详细信息 `-a` 显示隐藏文件 |
| `cd`             | 切换目录                         | `cd /path/to/dir` 切换到指定目录    |
| `pwd`            | 显示当前工作目录的绝对路径       | 无参数                              |
| `mkdir`          | 创建新目录                       | `-p` 创建多级目录                   |
| `rmdir`          | 删除空目录                       | 无参数                              |
| `rm`             | 删除文件或目录                   | `-r` 递归删除 `-f` 强制删除         |
| `cp`             | 复制文件或目录                   | `-r` 复制目录 `-p` 保留文件属性     |
| `mv`             | 移动或重命名文件或目录           | 无特别参数                          |
| `touch`          | 创建空文件或更新现有文件的时间戳 | 无参数                              |
| `cat`            | 查看文件内容                     | `-n` 显示行号                       |
| `more`           | 分页显示文件内容                 | 无参数                              |
| `less`           | 逐步查看文件内容                 | 无参数,需要`:q`退出                 |
| `head`           | 显示文件开头内容                 | `-n` 指定显示行数                   |
| `tail`           | 显示文件末尾内容                 | `-n` 指定显示行数                   |
| `ln`             | 创建硬链接或软链接               | `-s` 创建软链接                     |
| `chmod`          | 改变文件或目录的权限             | `+x` 添加执行权限                   |
| `chown`          | 改变文件或目录的所有者           | `-R` 递归更改所有者                 |
| `df`             | 显示磁盘空间使用情况             | `-h` 人类可读的格式                 |
| `du`             | 显示目录或文件的磁盘使用情况     | `-h` 人类可读的格式 `-s` 显示总计   |
| `ps`             | 显示当前进程                     | `-aux` 显示所有进程                 |
| `kill`           | 发送信号到进程                   | `-9` 强制杀死进程                   |
| `top`            | 显示实时进程活动                 | 无参数                              |
| `tar`            | 打包和解包文件                   | `-cvf` 创建新的档案 `-xvf` 解包文件 |
| `grep`           | 文件内容搜索                     | `-i` 忽略大小写 `-r` 递归搜索       |
| `find`           | 在目录树中搜索文件               | `-name` 按名称搜索 `-type` 类型搜索 |
| `ssh`            | 远程登录                         | `-p` 指定端口号                     |
| `scp`            | 远程拷贝文件                     | `-P` 指定端口号 `-r` 递归拷贝       |
| `sudo`           | 以超级用户权限执行命令           | 无参数                              |
| `apt-get`或`apt` | 包管理工具                       | `update` 更新源 `install` 安装包    |

学习命令：

- apt
- pwd：显示当前目录
- cd：进入某个目录
- ls：显示当前目录文件夹及文件
- mkdir:新建一个文件夹
- rmdir
- touch：新建一个文件
- rm
- find
- grep
- mv
- cp
- clear
- vim
- cat
- sudo
- ifconfig



##### 1 上下键翻看 `terminal` 终端历史命令

##### 2 安装软件指令

- `sudo apt install` + 软件名
- `sudo apt-get install` + 软件名

##### 3 Linux隐藏文件

- <span style="font-size:16px;color:black;font-weight:bold;">所有以 `.` 开头的文件都是隐藏文件(文件夹)</span>

- 比如: `.vimrc` - 这就是个隐藏文件

##### 4 查看ip地址

- windows下在终端输入：ipconfig
- ubuntu下在终端输入: ifconfig
- 注意（如果以上错误）：需要安装net-tools: sudo apt install net-tools

##### 5 `ls` - 列举目录内容

- 蓝色是文件夹

- 白色的是文件

- `ls` : 显示当前目录下的文件或者目录，参数

- `ls -a`：显示所有文件包含隐藏文件（以 . 开头的文件就是隐藏文件）

- `ls -r`：逆向显示文件

- `ls -R`：递归地列举所有目录（在当前目录下）的所有内容

- `ls -l`：详细显示文件属性

  <span style="font-size:16px;color:black;font-weight:bold;">注意：`.` 表示当前目录，`..` 表示上级目录</span>

  

##### 6 `pwd` - 查看当前目录路径

- <span style="font-size:16px;color:black;font-weight:bold;">pwd </span>命令用于显示用户在文件系统中的当前位置，该命令没有任何选项和参数，命令执行结果显示为绝对路径名。

- <span style="font-size:16px;color:black;font-weight:bold;">`~`:  </span>表示用户目录(用户目录)

- <span style="font-size:16px;color:black;font-weight:bold;">`/`: </span> 表示根目录

```c
pwd
```

##### 7 cd - 进入指定的文件夹

- `cd` +空格 + 目录/文件夹名 就可以进入指定的文件夹
- `cd` +空格 + 连续目录 `cd  /home/dengiswenn`
- `cd /home/ciyeer`：进入用户目录
- 注意 ：我们通过 `ls -a`会发现文件夹中会有两个蓝色文件夹，文件夹名分别为 `.` 和 `..`
- `.` 表示当前目录
- `..` 表示上一级目录
- 返回上级目录：`cd ../`
- 返回上上级目录：`cd ../../`
- 进入用户主目录`~`:  `cd`  或 `cd ~` 即可

```c
cd 某个目录
cd 绝对路径 

例子：
cd  ../
cd /home/dengiswen
cd ~  或 cd   ：都是进入用户主目录
```



##### 8 创建一个文件

- `touch` 创建文件如果文件不存在，创建文件，如果文件存在，则修改该文件的时间戳为当前时间
- `touch ` + 文件名
- `touch infomation.txt`
- 同时创建三个文件：`touch 3.txt 4.txt 5.txt`

##### 9 删除一个文件

- rm [ -i | -f | -r | -v ] 目录

- `rm` + 文件名
- `rm infomation.txt`  : 删除 `infomation.txt` 这个文件

```c
rm  文件名 
rm -r 目录名
rm -fr 文件名或目录    //强制珊删除目录或文件
rm -v 文件名或目录  
rm  *.c  删除当前目录的所有以.c为后缀的文件
rm dengnaiwen/*.txt
```



| 选项 | 描述                                                         |
| ---- | ------------------------------------------------------------ |
| -f   | 非交互模式的删除操作，忽略不存在的文件，有点**强制删除**的意思 |
| -i   | 交互模式的删除操作。在删除目标文件之前将给出提示，要求用户确认，回答“y”表示目标文件将被删除 |
| -r   | 若源文件是一个目录，rm 命令将递归地删除该目录下的所有子目录和文件 |
| -v   | 显示详细的删除过程                                           |



##### 10 创建目录/文件夹

- 要求用户在当前目录下具有写权限，并且要创建的目录不能与已有目录重名。

- `mkdir` + 目录/文件夹：创建一个空目录
- 例子：`mkdir week_45`    --    创建了一个名为week_45的文件夹
- mkdir -p 子目录 1/子目录 2：先创建子目录 1 再在子目录 1 下创建子目录 2
- mkdir -v 目录名：创建目录后显示信息
- mkdir -m 权限码 目录名：创建一个权限为（权限码）的空目录

##### 11 删除 空 目录/文件夹

- `rmdir` + 空 文件夹/目录
- `rmdir week45`  --  删除名为 `week45` 的空文件夹/目录
- 注意：`rmdir` 删除的只能是空文件夹，不能删除非空文件夹

##### 12 删除非空目录/文件夹

- `rm -r ` + 目录/文件夹
- `rm -r week45`  --  递归删除名为week45的非空文件夹/目录
- 注意：这里要删除的文件夹可以是空文件夹，也可以是非空文件夹
- `rm -r` ： 递归删除，可删除子目录和文件
- `rm -f` ： 强制删除
- `rm -rf`：强制递归删除
- `rm *.c`：批量删除所有`.c`文件
- `rm *`：删除所有文件

##### 13 复制文件/或者文件夹

- `cp` + 源文件 + 目标目录：复制源文件到目标目录中（目标目录中无该源文件）
- `cp -a` 源目录 目标目录：复制整个目录到目标目录
- `cp -a` 源目录/. 目标目录： 复制整个目录的文件到目标目录

- `cp test.c ~/`：将 `test.c` 文件拷贝到`~`中
- `cp level01/week01/day01/test.cpp . `   : 将 `level01/week01/day01/` 目录中的`test.cpp`文件拷贝到当前目录

| 选项 | 描述                                                         |
| ---- | ------------------------------------------------------------ |
| -a   | 该选项通常在拷贝目录时使用，保留链接、文件属性，并递归地拷贝目录，其作用等于 dpr 选项的组合 |
| -d   | 拷贝时保留链接                                               |
| -f   | 非交互模式的复制操作。覆盖已经存在的目标文件而不提示         |
| -i   | 交互模式的复制操作，与-f 选项相反。在覆盖目标文件之前将给出提示，要求用户确认，回答“y”表示目标文件将被覆盖 |
| -p   | 除复制源文件内容外，还将其修改时间和访问权限也同时复制       |
| -r   | 若源文件是一个目录，cp 命令将递归地复制该目录下的所有子目录和文件 |
| -v   | 显示详细的复制过程                                           |

例子

- 当前目录里的1.txt复制为2.txt
- 当前目录下的a文件夹完全复制为b，
- 当前目录下的b文件夹复制到a文件夹中并时间、权限保持同步

细节：

- 如何判断是复制+重命名还是说只复制

  - 只需要写目标目录时是否带有新的文件夹名称。如果带那就是复制+重命名 ，没有则复制，名称一样。

    ```c
    1.复制+重命名
    cp 源文件夹 目标文件夹/新文件件名称 
    2. 复制
    cp 源文件夹 目标文件夹
    ```

    



##### 14 移动文件/目录

- `mv` + 要移动的文件/文件夹 + 目标目录
- `mv test.c ~/`：将 `test.c` 文件移动到主目录中
- `mv level01/week01/day01/test.cpp ./ `   : 将 `level01/week01/day01/` 目录中的`test.cpp`文件移动到当前目录

##### 15 重命名文件/目录

- mv + 源文件 + 目标文件：将源文件重命名为目标文件

- mv + 源文件 + 目标目录：将源文件移动至目标目录（源文件可以有多个）

- mv + 源目录 + 目标目录：如果目标目录存在，则将源目录移动至目标目录；如果目标目录不存在，则重命名该目录为目标目录

- mv -i 源文件 目标文件：将源文件命名为目标文件，如果目标文件名存在，则询问是否覆盖

- mv -f 源文件 目标文件：将源文件命名为目标文件，如果目标文件名存在，则直接覆盖

- `mv test.cpp test.c` ：将`test.cpp`改名为`test.c`

- 例子：将`~/demo下的`目录b移动到`~/`下并重命名为a.当前目录为主目录`~`下的demo文件夹

  ```c
  mv ./b ../a
  ```

- 练习

  - 当前目录为主目录（如果文件或文件夹没有则自行新建）

    - 将主目录下的demo文件夹移动到主目录下并重命名为a

      ```c
      mv demo a
      ```

    - 将主目录下的a文件夹里的1.txt修改为2.txt

      ```c
      mv ./a/1.txt ./a/2.txt
      ```

    - 将修改的2.txt移动到主目录并重命名为a.txt


##### 16 查看文件内容

- `cat` + 文件名
- `cat test.c`：查看 `test.c` 文件中的内容

##### 17 查看 ip 地址

- `ifconfig`

##### 18 清屏

- `clear`

##### 19、切换用户

- `su 用户名`
- 例子：`su  root`

##### 20、修改密码

- 修改当前用户密码：`passwd`
- 修改root账号密码：`sudo passwd root`
- 所有用户信息都在`/etc/passwd`中，可以使用`cat /etc/passwd`进行查看
  - 格式：`用户名:密码:用户ID:组ID:全名或描述:家目录:默认shell`



##### 21、解压缩

- tar：主要用于解压缩`.tar.gz`格式文件

  - 解压

    ```c
    # 解压当前目录下的archive_name.tar.gz
    tar -xzvf archive_name.tar.gz
    ```

  - 压缩

    ```c
    tar -czvf archive_name.tar.gz directory_to_compress/
    ```

  - 参数

    - `-c`: 创建一个新的归档文件。
    - `-x`: 从归档文件中提取文件。
    - `-v`: 详细模式，显示命令执行的详细过程。
    - `-f`: 指定归档文件的名称。
    - `-z`: 与gzip压缩相关。
    - `-t`: 列出归档内容，不解压。

- unzip/zip

  - 压缩

    ```c
    zip -r filename.zip file_to_compress
    ```

    - `-r`: 递归地处理目录，将目录及其中所有文件和子目录全部压缩。
    - `-q`: 安静模式，压缩时不显示任何信息。
    - `-v`: 详细模式，显示压缩过程中的详细信息。

  - 解压

    ```c
    unzip filename.zip
    ```

- sort：排序

  ```c
  sort 参数  待排序的文件
  例子：
  sort -n numbers.txt
  sort -k 2 -n names.txt
  ```



##### 22、grep

- 概念：文件内容的搜索命令。

- 语法

  ```c
  grep -参数  搜索的内容   要搜素的文件
      
  例子：
  grep 1.c abc 
  ```

  - n：提供查找内容的行数

##### 23、find：查找文件

- 概念：根据名字和文件的种类来查找文件

- 语法

  ```c
  find 需要查找的目录 -name 待查找文件名
  find 需要查找的目录 -type d
  例子：
  1.查找主目录下的所有的1.c
  find ~ -name "1.c"
  2.查找根目录下名字以1开头的c文件,*指任意内容
  find / -name "1*.c"
  3.查找根目录下名字以1结尾的c文件,*指任意内容
  find / -name "*1.c"
  4.查找根目录下名字包含1的c文件,*指任意内容
  find / -name "*1*.c"
  5.查找主目录下的所有普通文件 
  find ~ -type f
  6.查找主目录下的所有目录
  find ~ -type d
  ```

- 参数

  - -name：按照文件名字来查找
    - 如果名字中带有`*`，一定要用一对引号包围起来，不然会报错
  - -type：按照文件类型来查找
    - f：普通文件
    - d：目录
    - ...

##### 24、sort

- 概念：能够对某个文件或管道输入进行排序并**输出**排序后的结果，本身命令对源文件没影响。

- 语法

  ```c
  sort -参数1 -参数2  待排序的文件
  ```

- 参数

  - -n：按照数字来排序。没有-n默认是按照字母数字的自然顺序来排序（底层是用的ASCII码来排序）
  - -k：按照指定的第几列进行排序
  - -s：稳定排序
  - -o：将排序结果保存到某个文件中

##### 25、wc：统计命令

- 概念：可以统计管道或某文件指定字符出现的次数或行数或字符的总数量（根据参数不同，统计的东西不同）

- 语法

  ```c
  wc -参数  文件
  ```

- 参数

  - l:统计行数
  - w:统计单词的数量 
  - c:统计字符的数量

#### 三、 vim 编辑器及使用

Linux 系统内支持多种文本编辑器，常用的有 gedit、OpenOffice、emacs 等，但是使用最为广泛的文本编辑器还是 vim。vim 是 Linux 系统下一个功能强大、高度可定制的文本编辑器，它基于 VI，同时又增加了许多新的特性。

由于程序员在写代码的时候双手需要时刻停留在键盘上，因此 vim 专门针对程序员进行了优化，例如分割视窗、多级撤销、定位代码、控制光标等操作，这样程序员的双手就无需离开键盘去点击鼠标。而且，vim 无需使用图形化界面，这也就意味着对于某些极端情况（例如图形桌面系统全面崩溃等）下，vim 是唯一一种可靠的编辑器。

vim 是vi的升级版



##### 1 打开vim编辑器

`vi/vim` + 文件名

- 如果要打开的文件不存在，则创建并打开该文件
- 如果要打开的文件存在，则直接打开该文件

##### 2.安装vim编辑器

- 如果提示没有安装vim，就使用以下命令来安装（需输入密码，密码不可见）

```c
sudo apt install vim
```



##### 3 vim 工作模式 

- ##### vim 编辑器基本上可以分为 3 种模式

  - ##### 					1. 命令模式（command mode）

    - 控制屏幕光标的移动，进行文本的删除、复制等文字编辑工作（不使用[Del]键和[Backspace]键）以及进入插入模式，或者回到底行模式。

  - ##### 					2. 插入模式（Insert mode）

    - 只有在插入模式下，才可以输入文字。并且按[Esc]键可回到命令行模式。很多 `vim` 编辑器使用者希望一打开 `vim` 就可以输入内容，但这是不能成功的，因为刚打开 `vim` 编辑器时处于命令模式。

  - ##### 					3. 底行模式（last line mode）

    - 保存文件或退出 `vim`，同时也可以设置编辑环境和一些编译工作，如列出行号、寻找字符串等。

  

##### 3 Vim 模式相互转换关系图

![image-20240102153521885](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/20240102153521.png)

##### 4.vim的一般使用步骤

- 使用vim命令打开文件（进入命令模式）
- 按下`a或i或o`进入插入模式，就可以开始编辑文件
- 编写完成后，按下`esc`退回命令模式
- 按下`:`进入底行模式，输入w和q进行保存并退出

##### 5 模式切换

###### 4.1 插入模式

- ###### 新增（append**，**简写为 a）

  - ###### a：从光标所在位置后面开始新增

  - ###### A：从光标所在行最后的地方开始新增

- ###### 插入（insert，简写为 i） 

  - ###### i：从光标所在位置前面开始插入

  - ###### I：从光标行所在的第一个非空白字符前面开始插入

- ###### 开始（open，简写为 o） 

  - ###### o：在光标所在行的下一行新增一行并开始插入

  - ###### O：在光标所在行的上一行新增一行并开始插入

###### 4.2 命令模式 

- ###### 返回命令模式："[ESC]" 键

- ###### 移动光标

> ##### h：向前移动
>
> ##### j：向下移动
>
> ##### k：向上移动 
>
> ##### l：向后移动
>
> ##### b：移动到当前单词开始
>
> ##### e：移动到当前单词结尾(单词最后一个字母之前的位置)
>
> ##### w：移动到下一个单词(单词最前面)
>
> ##### 行首：0 (注意: 这是数字0, 不是字母o/O)
>
> ##### 行尾：$ (注意：其实是行尾最后一个字符的前面)
>
> ##### 文件头：gg
>
> ##### 文件最后一行：G
>
> ##### 文件尾： G$ (文件最后一个字母之前的位置)



###### 4.3 底行模式

- ###### 按 " : " 键可以进入底行模式

- ###### 保存操作

  - ###### 	1. 如果使用 vim 打开现有文件，可以使用命令 `:w` 直接保存到原始文件中

  - ###### 	2. `:w`  路径和文件名，即可以指定名称保存到指定路径。

  - ###### 	3. `:wq` 表示保存并退出命令

  - ###### 	4. `:q!` 表示不保存并强制退出命令

- ###### 查找操作

  - ###### 向下查找 :    /  需要查找的字符

  - ###### 向上查找：  ？需要查找的字符

  - ###### 如果文本中含有多个匹配字符，则可以按 n 来自动查找下一个匹配的字符，按 N 键就可以查找上一个匹配的字符。这样就能对查找到的内容进行上下移动。



###### 4.4. 复制剪切粘贴操作（命令模式）

<span style="font-size:16px;color:black;font-weight:bold;">1. 按行复制/剪切命令</span>

- 光标移动到文本文件的某一行，输入 `yy/dd`，表示按行复制/剪切； 

<span style="font-size:16px;color:black;font-weight:bold;">2. 对光标位置到该行的结尾进行复制/剪切</span>

- 命令 `y$/d$`，表示从当前光标复制/剪切到当前光标结尾

3. **多行复制命令**

- 我们可以将光标移动到某行，我们输入命令 `nyy`
- 删除多行内容:`ndd`
- 命令中的n是一个数字，比如`3yy`或`2dd`

<span style="font-size:16px;color:black;font-weight:bold;">4. 粘贴操作</span>

- 命令 `p` 表示粘贴，如果需要将复制的内容多次粘贴，则多次按 `p` 键就可以了。



##### 5 错误撤销恢复

- 命令 `u` 表示撤销上一步操作，如果需要多次撤销，则多次按 `u` 键就可以了

- 如果上一次的撤销错了，取消撤销，可以按 `ctrl+r` 恢复



##### 6 其他操作

###### 	1.跳转到对应行号

- `:n`  跳转到第 n 行 

###### 	2. 文件的插入

- `:r` 路径  /文件名 将文件中的内容插入到光标所在的位置



##### 7. vim  常见操作

- 复制、粘贴、删除（单或多行）
- 复制文件内容
- 定位到某一行
- 快捷光标指向文件开头和结尾
- 查找文件里的某个内容
- 撤回操作
- 某行下面插入一行并编写内容



例子：编写第一个C语言程序

```C
#inlcude <stdio.h>

int main(int argc, char *argv[]) {
    printf("Hello world!\n");
    return 0;
}
```

> <span style="font-size:16px;color:black;font-weight:bold;"> 编译：gcc + 原文件名 </span>
>
> <span style="font-size:16px;color:black;font-weight:bold;"> 生成：a.out  (默认的可执行文件名) </span>		
>
> <span style="font-size:16px;color:black;font-weight:bold;"> 运行：./a.out </span>
>
> <span style="font-size:16px;color:black;font-weight:bold;"> 生成结果：Hello world! </span>

![img](https://woniumd.oss-cn-hangzhou.aliyuncs.com/aiot/ruishaojun/20240102170702.png)



#### 四、下载源设置

##### 1、配置下载源以及预下载对应的工具

- 思路：Ubuntu中有一个配置文件管理apt下载工具的远程服务器地址（地址也称镜像源），我们可以切换为国内镜像源，加快下载工具的速度。通过修改改配置文件并使用命令来重新让配置文件生效即可达到目的。

（1）重新设置ubuntu下载软件时的镜像源（提升工具包的下载速度）

- 打开终端，并以管理员身份编辑 `/etc/apt/sources.list` 文件（建议备份）

  ```bash
  sudo gedit /etc/apt/sources.list
  ```

- 将文件中原始的这些地址替换为你选择的镜像源地址（https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/）

  ```c
  # 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
  deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
  # deb-src http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
  deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
  # deb-src http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
  deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
  # deb-src http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
  
  deb http://security.ubuntu.com/ubuntu/ bionic-security main restricted universe multiverse
  # deb-src http://security.ubuntu.com/ubuntu/ bionic-security main restricted universe multiverse
  
  # 预发布软件源，不建议启用
  # deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse
  # # deb-src http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse
  ```

- 可能文件是只读的，需要更改文件的编辑权限之后才能保存：`sudo chmod 666 sources.list`

- 编辑完成后，保存文件并退出。然后运行以下命令以使更改生效

  ```bash
  sudo apt update  # 用于更新新的的软件包列表
  sudo apt upgrade # 用于升级已安装的软件都最新版
  ```

（4）下载课程中所需要的工具包

```shell
sudo apt install vim  build-essential
```

- vim：是vi的升级版。vi是linux系统的标准文本编辑器。vim相对于vi拥有`代码高亮`、`代码折叠`、`自定义配置`等新特性
- build-essential：是linux中用于编译和执行c/c++代码的工具整合包，里面包含但不限于`g++`、`gcc`、`make`等一系列工具。也就是按一次等同于安装了以上所有涉及的工具。
  - gcc：c语言代码编译和运行的所需环境工具包
  - g++：c++代码编译和运行所需的环境工具包
  - make：一个配置工具，能够完成快捷编译和运行c/c++代码。




#### 五、用户和用户组

##### 1、linux中的多用户机制

（1）多用户

linux本身是一个多用户模式的操作系统。每个用户都有自己的用户名、密码和个人信息。并且每个用户都有自己的**主目录**，表现为`/home`下同名的目录。而不同用户登录进来就可以操作linux系统，默认进入自己的主目录。

linux用户可以有很多个，并且在创建一个用户时，都会伴随一个用户id，一般是1000及以上。并且同时会生成一个用户组，该用户组仅包含该用户本身。相关的信息可以在配置文件`/etc/passwd`中查看用户id以及用户组

```bash
cat /etc/passwd
```



（2）用户组

Linux的用户组是指定一组用户的集合，使得系统管理员可以给予这个集合中的所有用户一组共同的权限。

**每个用户都至少属于一个用户组**。用户组的好处在于能够简化文件权限的管理。例如，如果有一个项目团队需要对某个目录中的文件有读写权限，系统管理员可以创建一个组，将所有团队成员加入该组，然后设置这个目录的权限，使得该组的成员都可以访问

![image-20240409221621304](https://woniumd.oss-cn-hangzhou.aliyuncs.com/web/dengnaiwen/20240409221621.png)

用户组信息可以查看`/etc/group`：这个文件包含了系统上所有的组，每个组的成员列表，以及关于组的其他信息。

系统管理员可以使用`usermod`、`groupadd`、`groupmod`等命令来管理用户和组的成员资格。例如，要将用户加入一个组，可以使用`usermod -a -G group_name user_name`命令

总结：**linux创建一个用户时，会同时创建一个同名 用户组，并自动将新用户放入该用户组中，可以通过指令来对用户组进行用户的追加和移除操作**

（3）用户组的一些操作

- 添加用户到用户组

  ```js
  sudo usermod -aG 用户名  用户组名
  ```

  - `-a`:表示追加用户到用户组
  - `-G`:表示设置用户组的用户

- 移除某个用户组里的某个用户

  ```js
  sudo usermod -d 用户组名  用户名
  ```

- 添加某个用户（自动创建新用户的主目录以及用户组）

  ```js
  sudo addUser   新用户名
  ```

  

##### 2、linux的权限机制

（1）权限基本概念

Linux的权限机制是构建在文件系统上的一套规则，用来控制不同用户对不同文件和目录的访问。权限主要分为三个层面：

1. **用户（User）**：文件的所有者。通常是创建文件的用户。
2. **用户组（Group）**：文件的所属组。所属组内的所有用户都拥有相同的权限。
3. **其他（Others）**：既不是文件所有者、也不在文件所属组内的其他用户。

并且，**每个文件或目录**都会有三个权限：

每个文件和目录都有三组权限：

- **读（Read，r）**：允许读取文件内容或列出目录内容。
- **写（Write，w）**：允许修改文件内容或向目录中添加/删除文件。
- **执行（Execute，x）**：允许执行一个文件或进入目录。

文件的权限可以通过`ls -l`命令查看，比如：

```c
-rwxr-xr-- 1 deng deng 123 Mar 10 10:00 example.txt
```

以上表示：

- 所有者`deng`有读、写和执行权限（`rwx`）。
- 组`deng`有读和执行权限（`r-x`）。
- 其他用户只有读权限（`r--`）。

（2）设置权限

可以使用`chmod`（change mode）命令来更改文件或目录的权限。权限控制谁可以读取（r）、写入（w）或执行（x）文件和目录。

- 第一种：使用符号来设置
- 第二种：使用数字来设置（推荐）

第一种：符号设置

使用字母 `u`（user，即文件所有者）、`g`（group，即文件所属组）、`o`（others，即其他用户）和 `a`（all，所有用户）来指定权限的更改将应用于哪些用户。然后，使用 `+`（添加权限）、`-`（删除权限）和 `=`（设置确切的权限）来修改读（r）、写（w）和执行（x）权限

```c
要给所有者添加执行权限：chmod u+x filename
要给组删除写权限：chmod g-w filename
要给其他用户设置读和执行权限：chmod o=rx filename
chmod u-x,g=rw,o=rx filename或目录：所有者删除执行权限，用户组设置为可读写权限，其他为可读可执行
要给所有用户设置所有权限：chmod a=rwx filenama
```

第二种：数字设置

使用三个数字来设置权限，每一位数字代表一个用户类别（所有者、组、其他用户）对应的所有权限。**每一位数字是其对应权限的总和**，其中读（r）是4、写（w）是2、执行（x）是1。即如果拥有读写那么数字为6，如果是拥有所有权限为数字7，数字5表示拥有读和执行。

```c
要设置所有者有全部权限（7），组有读和执行权限（5），其他用户有读权限（4）：chmod 754 filename
要设置所有者有读写权限（6），组和其他用户都有读权限（4）：chmod 644 filename
    
chmod 500 ：所有者：读 执行   用户组：没有任何权限   其他：没有任何权限
chmod 666 所有者：读写   用户组：读写   其他：读写
chmod 445：所有者： 读  用户组：读   其他： 读、执行
chmod 446：所有者： 读  用户组： 读   其他：读写
chmod 567 ：所有者：读执行   用户组：读写   其他：读写执行
```

在执行`chmod`命令时，你可能需要有足够的权限。如果你是文件的所有者，或者你是root用户，那么你通常可以更改文件的权限。如果你不是所有者，你可能需要通过使用`sudo`来获得必要的权限



#### 六、练习

- 课堂练习

```c
1. 列出当前目录下的所有文件和文件夹。 ls
2. 当前目录新建一个文件为file.txt touch file.txt
3. 将第二步新建的文件移动到名当前新目录"folder"中。 mkdir folder ;  mv file.txt folder
4. 进入folder目录中 cd folder
5. 显示当前所在的工作目录。 pwd
6. 复制file.txt 到上一级目录中 cp file.txt ../
7. 退回到上一级目录 cd ../
8. 删除folder目录以及里面的所有文件 rm -fr folder 
    
vim练习
1. 编写多个文件，并进行成绩排序以及输出到指定文件中
```

- 晚自习作业

```c
1.使用 mkdir 命令创建一个名为 project 的新目录，并进入该目录。
2.在 project 目录中，使用 touch 命令创建一个名为 main.c 的C语言源文件。
3.使用 vim 打开 main.c 文件，并在其中写入一个简单的 C 语言程序，该程序打印 "Hello, World!"。
4.使用 gcc 编译器将 main.c 编译为可执行文件 main。
5.使用 ./ 运行编译好的可执行文件 main，并确认输出 "Hello, World!"。
6.使用 more 命令查看 main.c 文件的内容。
7.在当前目录及其子目录中使用 find 命令查找所有以 .c 结尾的文件。
8.将 main.c 文件使用 zip 命令压缩为 source.zip。
9.使用 chmod 命令将 main 可执行文件的权限修改为所有用户都可以执行。
10.使用 cp 命令将 source.zip 复制到 /tmp 目录。
11.将 main.c 文件重命名为 hello.c。
12.删除重命名后的 hello.c 文件。
```



