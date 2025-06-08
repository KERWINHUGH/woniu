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



#### 三：常用命令：

- ls   显示目录内容
- ll    详细显示目录内容（包含隐藏文件和目录）
- pwd   显示路径
- mkdir  创建目录
- rmdir   移除目录（目录要是空的）
- touch   创建空文件（可以带扩展名）

- vim 编辑文件
  - 一进入是：命令模式：
  - 按i键：       插入模式：
  - ESC切换到命令模式：
  - ：               底行模式
  - :wq            保存退出
  - :q!               强制退出，不保存