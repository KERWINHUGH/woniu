## 数据库（sqlite）

### 课程目标

1. 理解数据库的概念
2. 了解常用的数据库
3. 创建数据库
4. 理解表和数据
5. 掌握对于表的常规操作
6. 掌握对于数据的常规操作
7. 掌握在c语言中使用sqlite3进行操作

### 课程实验

1. 使用终端完成Sqlite数据库的 基本使用
2. 在c语言中通过apt下载第三方工具来使用Sqlite3，完成程序中数据的管理

### 课堂引入

> 为什么需要单独的数据库来进行管理数据？
>
> 1. 数据的各种查询功能
> 2. 数据的备份和恢复
> 3. 花大量时间在文件数据的结构设计和维护上
> 4. 要考虑多线程对数据的操作会涉及到同步问题，会增加很多额外工作

### 授课进程

#### 一、简介

##### 1、什么是数据库

从生活角度上：数据库，就是数据的`仓库`.用于保存数据，但是需要按照一定的次序和方式来管理。比如商品仓库。也就是保存和管理数据需要一定的规则，不能随意的放置。

![image-20240325161413087](https://woniumd.oss-cn-hangzhou.aliyuncs.com/web/dengnaiwen/20240325161413.png)

从it上来说，数据库，就是指提供了保存数据管理功能的软件，全称数据库管理系统（database Managment system）。针对要管理数据形式不同，不同it公司都提供了不同的数据库管理系统。

##### 2、常见数据库

（1）以类似表格形式保存数据的数据库:关系型数据库（数据大多数以二维表的形式来保存）

- SqlServer

- sqlite

- mysql

- oracle

  | id   | name | emil           | number | class    |
  | ---- | ---- | -------------- | ------ | -------- |
  | 1    | 张三 | 23@qq.com      | 001    | 三年二班 |
  | 2    | 李四 | 34@163.com     |        |          |
  | 3    | 王五 | 56@woniuxy.com |        |          |

  - 二维表：以行和列的形式来保存数据

（2）以键值对形式保存数据（非关系型数据库）

- MongoDB
- Redis
- indexDB
- R2

```c
{
    "name":"张三",
    "id":1,
    "age":23
}
```

保存数据的格式类似于结构体一样，没有行和列的概念。只有一个数据和保存多个数据的集合。

##### 3、sqlite

（1）概念

SQLite是一个**开源的轻量级关系数据库管理系统**，它的不同之处在于它是以库的形式提供的，这意味着它是一个零配置、无需安装和管理的数据库引擎（一个Sqlite数据库，就是一个单独的文件）。它不是一个独立的服务进程，而是直接集成到应用程序中。**SQLite存储整个数据库（定义、表、索引和数据）为单个跨平台的文件(.db文件)**，在多个系统和程序语言之间提供极致的可移植性。

**注意：sqlite所有操作都是在本地直接通过对数据库文件的读写来完成的**

##### 4、和其他数据库的区别

- **部署**：相比MySQL等传统关系数据库，SQLite不需要一个独立的服务器进程或系统。MySQL被设计为客户端/服务器架构的一部分，需要运行和管理数据库服务器。

- **配置**：SQLite不需要安装和配置，没有配置文件，一切都是即插即用，这使得它成为嵌入式应用和轻量级应用的理想选择。

- **资源需求**：SQLite消耗资源更少，尤其是在磁盘空间和内存使用方面。因此，它适用于移动应用、游戏、小型到中型应用等场景。

- **并发和锁定**：SQLite的并发能力不如MySQL等数据库。SQLite在进行写操作时会锁定整个数据库，这可能不适合高并发的应用场景。而MySQL等数据库使用更复杂的锁定机制，支持更高的并发处理能力。

- **事务处理**：SQLite支持完整的ACID事务，这与许多其他数据库系统一样。

  > 简单理解事务：要么全部成功，要么全部失败！不允许部份成功



##### 5、sqlite优缺点

**优点**：

1. **易于使用**：无需复杂的设置或配置。
2. **轻量级**：非常适合需要轻量级数据库解决方案的应用，如小型网站，嵌入式设备等等。
3. **跨平台**：支持多个操作系统和编程语言。
4. **自给自足**：不依赖于外部的服务器或服务。
5. **事务支持**：提供ACID兼容的事务特性。

**缺点**：

1. **写入操作的限制**：写入时锁定整个数据库，对于需要高并发写入的应用可能不是最佳选择。
2. **不适用于高并发场景**：高并发访问可能会成为性能瓶颈。
3. **不支持用户管理和复杂的权限设置**：没有内置的用户管理功能，权限管理需要在应用层实现。

#####  6、版本发展

（1）初始阶段

- **2000年8月**：SQLite的首个版本（1.0）发布。最初的设计目标是提供一个轻便、无配置、易于嵌入的事务性SQL数据库引擎。由个人开发者 D. Richard Hipp 独立开发。

（2）重要升级和功能增强

- 2004年6月

  ：SQLite 3.0发布。这是一个重大更新，引入了许多新特性，其中包括：

  - UTF-8和UTF-16的支持。
  - 引入了新的数据库文件格式，以支持更多的功能和更高效的存储。
  - 提升了性能和可靠性。
  - 增加了对可变长度记录的支持。

（3）持续改进和优化

从2004年至今，SQLite经历了持续的优化和功能增强。以下是一些显著的里程碑：

- **2010年**：引入了Write-Ahead Logging（WAL）模式，显著提高了并发写操作的性能。
- **2013年**：增加了对部分索引的支持。
- **2015年**：引入了JSON支持，使得处理JSON数据更加方便。
- **2018年**：增强了窗口函数和通用表达式（CTE）的支持。
- **2020年**：引入了生成列和DEFERRABLE INITIALLY DEFERRED约束的支持。

##### 7、应用场景

1. **桌面应用程序**：SQLite常用于单用户应用程序，如个人财务管理软件，需要本地存储数据但不需要网络访问的场景。
2. **移动应用**：SQLite是iOS和Android平台的默认数据库，用于存储联系人、日历、应用设置等信息。
3. **嵌入式设备**：在限制内存和处理能力的嵌入式系统中，如物联网设备，SQLite提供了数据存储和查询的能力。
4. **教育和测试**：由于它简单易用，SQLite常用于教学和学习SQL语言，以及进行软件开发的初期原型制作。
5. **磁盘文件格式**：一些应用使用SQLite作为其文件格式，利用数据库文件来存储和操作复杂的数据结构。
6. **网站**：适合小型网站和个人博客，不需承受大量并发访问的场景。



**总的来说**:SQLite在单用户应用或资源受限环境中表现出色，但在需要处理大量并发请求的、高可用性要求的、资源丰富的服务器环境中，MySQL和Oracle可能是更合适的选择。



#### 二、sqlite安装（linux下）

##### 1、 安装sqlite3

```c
sudo apt install sqlite3
```

##### 2、创建并访问或直接访问已存在数据库

```c
sqlite3 数据库名字.db
sqlite3 stu.db
--------------------------------------------
yujian@ubuntu:~/Desktop/sqllite$ sqlite3 wnnj25.db
SQLite version 3.31.1 2020-01-27 19:55:54
Enter ".help" for usage hints.
sqlite> 
```

![image-20241201225258118](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/yujian/20241201225258.png)

- 成功之后就会进入数据库 操作指令模式，这个时候就可以书写数据库的操作指令，就不是终端命令。

##### 3、退出数据库操作终端命令

```sql
ctrl +d 
或
输入 .quit 或  .exit
```

##### 4、关于数据库的一些核心概念

（1）数据库

- 安装的sqlite3本身是一个数据库软件，通过该软件可以创建和管理多个以二维表作为**数据存储手段**的数据库，比如学校数据库、迷宫数据库、电影院数据库

（2）表（二维表）

- 概念：二维表（简称表）是保存某一类数据的具体载体。一般一个数据库可以有多张二维表，每张二维表可以存储一类的数据。比如学生表（保存学生类的数据，一行数据就是一个学生），成绩表、老师表。

- 例子：迷宫数据库

  - 应该有那些表

    - buff表

    - 敌人表

    - 地图表

      | 地图编号   | row_index | col_index | value |
      | ---------- | --------- | --------- | ----- |
      | 1          | 0         | 0         | 1     |
      | 1          | 0         | 1         | 1     |
      | 1          | 0         | 2         | 1     |
      | 省略了17行 |           |           |       |
      | 1          | 1         | 0         | 1     |
      | 1          | 1         | 1         | 3     |
      | 1          | 1         | 2         | 0     |

      

    - 玩家表：

      | 玩家编号 | 玩家名称 | x    | y    | buff表 | 步数 | 地图编号 |
      | -------- | -------- | ---- | ---- | ------ | ---- | -------- |
      | 1        | 张三     | 12   | 13   |        | 23   | 1        |
      | 2        | 李四     | 15   | 3    |        | 45   | 3        |

      

（3）一行数据

- 我们一般会将一张表的一行作为完整的一个数据。



#### 三、表的操作

##### 1、创建一张表

```sql
语法:
CREATE TABLE 二维表名(
   列1名称 数据类型  该列的特点,
   列2名称 数据类型  该列的特点,
   ...
   列n名称 数据类型  该列的特点
);

--  表的最后一列末尾不加逗号
例子：构建一张学生表
create table student (
   id integer primary key autoincrement,
   name text not null,
   age integer,
   email text not null unique
);

-- 创建带时间的表
CREATE TABLE events (
    id INTEGER PRIMARY KEY,
    name TEXT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP
);
-- 插入带时间的数据
INSERT INTO events (name, created_at) VALUES ('Event 2', DATETIME('now'));
```

![image-20241201225803872](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/yujian/20241201225803.png)

其中：id为列的名称，primary key表示该列为主要列，一张表最多只有一列是主要列。一般表示该列是用于区分每一行内容的。比如每个人都有身份证号码，那么该号码就可以作为人这张表的primary key列。`AUTOINCREMENT`表示该列自动填充，从1开始依次递增。也就是第一行内容id为1，第二行内容id为2。`INTEGER`表示数据类型。数据库有很多类型。但大家只需要关注`INTEGER  TEXT REAL `整数、字符串、浮点数三种数据类型即可。**数据类型和关键字不区分大小写**。这几种只有浮点数确定是8个字节，其他数据内存大小是由数据的本身大小来决定的。

每列的特点（都是可选，根据实际需求来定）：

**PRIMARY KEY:**将该列作为该表的主要参考列（简称主键），一般我们会将编号列作为主键。该列的每一个数据不能重复，一般会配合`AUTOINCREMENT`来使用，会自动在给表插入新数据时，该列编号自动填写并为上一个数据编号+1

**NOT NULL** 表示该列数据不能为空。 

**UNIQUE**表示该列数据不能出现重复的。

DEFAULT 数据: 表示该列可以有一个默认数据，比如default 0  表示默认数据为0，前提是数据类型是 数字，如果是文本则需要加一对引号

##### 2、列出所有表

```sql
SELECT name FROM sqlite_master WHERE type='table' ORDER BY name;
```

![image-20241201225930526](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/yujian/20241201225930.png)

**注意**：

（1）sqlite-master

`sqlite_master`是SQLite数据库中的一个内置表，每个SQLite数据库文件都包含这个表。`sqlite_master`表存储了数据库的元数据，包括数据库中存在的所有表格、索引、视图以及触发器的定义信息。通常不需要更改这张表。也可以用sql语句来查看这张表里面的内容。比如`SELECT type, name, sql FROM sqlite_master WHERE type='table';`

`sqlite_master`表的结构大概如下：

- `type`: 对象的类型（例如，'table'、'index'、'view'、'trigger'）。
- `name`: 对象的名称。
- `tbl_name`: 对象相关联的表的名称（对于表本身，`name`和`tbl_name`字段将相同）。
- `rootpage`: 对象在数据库文件中的起始页码。
- `sql`: 创建该对象的原始SQL语句。

（2）sqlite_sequence

在SQLite数据库中，`sqlite_sequence`是一个内部系统表，用于跟踪自动增长（AUTOINCREMENT）字段的当前最大值。当你在表定义中为某个列使用了`INTEGER PRIMARY KEY AUTOINCREMENT`属性时，SQLite会使用`sqlite_sequence`表来存储该列最近分配的最大整数值。这样，当新记录被插入到表中时，SQLite就可以为带有`AUTOINCREMENT`属性的列自动分配一个比之前所有记录都大的唯一标识符。

`sqlite_sequence`表有两个字段：

- **name**：这一列存储的是表的名称，该表含有一个`AUTOINCREMENT`字段。
- **seq**：这一列存储的是该表中最后一个被分配的`AUTOINCREMENT`值。

##### 3、查看表结构

```sql
PRAGMA table_info(表名);
```

![image-20241201230116403](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/yujian/20241201230116.png)

##### 4、删除表clear

```sql
DROP TABLE IF EXISTS 表名;
```

![image-20241201233233643](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/yujian/20241201233233.png)



#### 四：使用工具连接sqlite3 -  SQLiteStudio

#### 1: **SQLiteStudio**

```c
下载地址：https://sqlitestudio.pl/

-- 修改安装文件的权限：
yujian@ubuntu:~/下载$ chmod 776 SQLiteStudio-3.4.8-linux-x64-installer.run 
    
-- 使用sudo安装（不然提示权限不足）：
yujian@ubuntu:~/下载$ sudo ./SQLiteStudio-3.4.8-linux-x64-installer.run 

```

![image-20241202002732393](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/yujian/20241202002732.png)

- 如果安装好之后，不能使用, 输入以下命令解决：

  ``` bash
  sudo apt update
  sudo apt install libxcb-xinerama0
  sudo apt install qt5-qmake qtbase5-dev qtchooser
  sudo apt install libqt5gui5 libqt5core5a libqt5widgets5
  ```

  

#### 2：SqliteBrowser

``` bash
sudo apt-get install libsqlite3-dev
step3:安装Sqlite3图形化管理界面DB Browser for SQLite（用户可选择性安装）：

sudo apt-get install sqlitebrowser
step4:检查是否安装成功，如果成功，输入以下命令可显示SQLite3版本信息。
```



#### 五、其他操作

##### 1、导出数据库

使用`.dump`命令导出整个数据库的SQL（终端命令，不进入sqlite3）：

注意：要切换到ubuntu系统下执行备份命令：

```sql
sqlite3 your_database.db .dump > dump.sql
```

![image-20241201235436951](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/yujian/20241201235437.png)

- back.sql内容：

![image-20241202000034639](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/yujian/20241202000034.png)



##### 2、导入数据库

使用SQLite3 CLI，你可以通过重定向来导入一个SQL文件。

```sql
sqlite> select * from student;
1|jack|22|abc@163.com
2|rose|21|bbb@163.com
3|lili|26|ccc@163.com
4|mike|26|ddd@163.com
5|张三|29|eee@163.com
-- 清空表的数据
sqlite> delete from student;
sqlite> select * from student;
-- 删除表
sqlite> drop table student;
sqlite> .exit
-- 导入备份的数据
yujian@ubuntu:~/Desktop/sqlite$ sqlite3 wnnj25.db < back.sql;
yujian@ubuntu:~/Desktop/sqlite$ 

```

##### 3、批量命令执行（.sql文件）

在Linux中，你可以将多条SQLite命令写入一个文本文件中，然后使用SQLite命令行工具批量执行这些命令。这个文件通常被称为SQL脚本文件：

- 1.创建一个以`.sql`结尾的文件，并书写你要执行的命令

```sql
-- 创建一张表
CREATE TABLE users (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  name TEXT NOT NULL,
  email TEXT NOT NULL UNIQUE
);
/*
这是一个多行注释
可以跨越多个行
非常适合解释复杂的SQL逻辑
*/
INSERT INTO users (name, email) VALUES ('Alice', 'alice@example.com');
INSERT INTO users (name, email) VALUES ('Bob', 'bob@example.com');
```

- 2.你可以使用以下命令在SQL shell中运行这个脚本

```bash
sqlite3 mydatabase.db < script.sql
```

- 	示多行注释

##### 4、查看和修改字符编码

```c
PRAGMA encoding;
```

sqlite并不能直接修改数据库文件的字符编码，实际上，你需要新建一个数据库文件并设置字符编码，然后再将旧文件内容放入到新文件中

```c
sqlite3 stu.db 
> PRAGMA encoding ='utf-8';
```

新建文件之前可以进行导出旧数据库内容到指定一个文件，再导入到新数据库文件中(**sqlite3 cli 中执行**)：

```c
.output dump.sql
.dump
.exit
```

导入数据库

```c
.read dump.sql
```



#### 六、数据的操作（CRUD）

sqlite推荐用单引号来包围字符串，双引号在不同版本中会有冲突

##### 1、插入数据

```sql
INSERT INTO 表名 (列名1,列名2,列名n) values('数据1','数据2','数据n');
-- 例子：id是自增的，所以可以不用写。
sqlite> insert into student (name,age,email) values ('jack',22,'abc@163.com');
sqlite> insert into student (name,age,email) values ('rose',21,'bbb@163.com');
sqlite> insert into student (name,age,email) values ('lili',26,'bbb@163.com');
-- 也可以带上id,要注意主键不能重复：
sqlite> insert into student (id, name,age,email) values (4,'mike',26,'ddd@163.com');
-- values前面可以省略，代表要跟所有的值：
sqlite> insert into student values (5,'张三',29,'eee@163.com');
```

##### 2、更新数据

```sql
-- 更新数据，将name为Alice所有数据里的email改成 newalice@example.com
UPDATE 表名 SET 列名 =新数据,列名2=新数据 where  列 =满足条件数据;
例子：将学生中名字为Alice的email改成newalice@example.com
UPDATE student SET email = 'newalice@example.com' WHERE name = 'Alice';
```

##### 3、删除数据

```sql
-- 删除所有name为Alice的一行数据
DELETE FROM student WHERE name = 'Alice'
DELETE FROM student WHERE id = 2;
-- 删除id为1同时name为admin的所有行数据
DELETE FROM student WHERE id = 1 AND name='admin';
-- 删除id为1或者name为admin的所有行数据
DELETE FROM student WHERE id = 1 OR name='admin';
```

- 如果不带where部分语句，那么就是删除表的所有数据。



- 练习：
  - 1：向employee表中插入6条件数据，应该有男有女，
  - 2：修改3号数据的性别为男，名字为：李强
  - 3：修改所有员工的电话号码为公司统一号码。88990000
  - 4：备份数据为 emp.sql 文件
  - 5：删除3到5号员工的数据
  - 6：跟据emp.sql文件，恢复原有的数据 ( 注意恢复之前，先清空原有数据)



##### 4、查询数据

- 示例：

  ``` sql
  -- 查询数据
  select * from employee
  select id, name,age from employee
  select * from employee where id = 4;
  select * from employee where id >= 4
  
  -- 注意 ：查询的时候 NULL 不等于 NULL 
  select * from employee where gender is NULL
  select * from employee where gender is not NULL
  
  -- 查询的结果，可以再处理
  select id, name,age+10, gender , phone from employee
  
  -- 范围查询：
  select * from employee where id >= 3 and id <= 6
  select * from employee where id between 3 and 5
  
  -- 模糊查询  %代表多个任意字符 ,  _ 代表一个任意字符
  --                         \_ 代表 把 _ 当成一个普通的字符
  select * from employee where name like '%\_%' escape '\'
  
  -- 查询多个指定id值的数据 1,3,5   使用 in 子句查询
  -- select * from employee where id = 1 or id = 3 or id = 5
  select * from employee where id in (1,3,5,8)
  
  ```

  练习：

  1：分别查询出男生的id,名字和女生的id,名字

  2：查询年龄大于20岁的人员信息

  3：查询出年龄在15-25之间的，女性的信息

  4：查询出id是 1，3， 5， 6，8 男性人员的信息

  5：查询出，联系电话为空的人员的信息

  6：查询出，所有的名字带 ‘丽’ 的人员的信息

  答案：

  ``` sql
  
  ```



##### 5：分页查询

> 分页查询我们使用 limit 关键字：

- 示例：

  ``` sql
  -- 分页
  select * from employee limit 0, 4           -- 第一页数据
  select * from employee limit 4,4            -- 第二页数据
  select * from employee limit 8,4            -- 第三页数据 
  
  select * from employee limit 4 offset 8     -- 分页的另一种写法
  
  /*
  limit x, y
  x : 代表的是忽略数（偏移量）
  y : 代表的是一次显示几条数据
  
  x 和 y 的值的求法：   当前页：currentPage         页大小：pageSize
  x = (currentPage - 1)*pageSize;
  y = pageSize;
  */
  ```


##### 6：查询结果排序：

> 当我们要对查询的结果进行排序时，使用 order by来进行排序：

- 示例：

  ``` sql
  -- 3: 查询性别为男的员工姓名和雇佣日期，并按雇佣日期降序排列    数字排序，默认是asc(升序<从小到大>)
  select first_name, last_name, hire_date from employees where gender = 'M' order by hire_date desc
  
  --                                            字母排序：默认是字典顺序
  select first_name, last_name, hire_date from employees where gender = 'M' order by first_name asc
  ```

  

## 七：进阶查询

> 当我们需要的数据，一张表不能满足我们的需求时，这个时候就涉及到了多表查询。

#### 1：多表联查

- 查询指定员工的部门信息（要有部门名称）

``` sql
-- 查询指定员工的部门信息（要有部门名称）
-- select * from dept_emp   -- 12条数据
-- select * from departments  -- 5条数据

-- 直接两表联查，会产成 迪卡尔积， 我们要避免它。
 select dept_emp.* , departments.dept_name 
 from dept_emp , departments  

-- 我们加一个条件，避免产生迪卡尔积
 select dept_emp.* , departments.dept_name 
 from dept_emp , departments  
 where dept_emp.dept_no = departments.dept_no and dept_emp.emp_no = 3

-- 习题：
-- 请查出d004号部门的所有员工号及部门名称

-- 1：先查出 d004号部门的所有员工号
--select * from dept_emp where dept_no = 'd004'

-- 2: 查出部门名称
-- select dept_name from departments where dept_no = 'd004'

-- 可以使用  as 给表或字段起 “别名”
select de.* , d.dept_name as 部门名称
from dept_emp de, departments d
where de.dept_no = d.dept_no and de.dept_no = 'd004';

```



#### 2：左连接：

> 当我们查询数据时，发现少了数据，这个时候，可以使用左连接（或右连接<需要版本支持>）来确保数据不会少：

- 查询每个员工的职位信息：（我们先新建一个员工，没有设置职位信息）

  - 按，前面多表联查的方式，查出的数据，是会少新员工的

  ``` sql
  select e.*, t.title from employees e , titles t where e.emp_no = t.emp_no
  ```

  - 使用左连接方式查询：

  ``` sql
  -- 查询所有员工的职位
  -- 左连接 （以 join 左边的表为基准）
  select e.*, t.title from employees e left join titles t on e.emp_no = t.emp_no
  ```

- 注意，还应该有相应的右连接（使用和左连接类似），但需要版本支持：

  - 我们目前使用的是3.22版本的sqlite，所以不能使用右连接

  ![image-20241219112745931](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/yujian/20241219112746.png)

#### 4：内连接：

> 直接使用 join  和 on  来替代 多表联查

``` sql
-- 内连接 （就和我们的多表联查是一样的）
select e.*, t.title from employees e  join titles t on e.emp_no = t.emp_no
```



#### 5：隐式连接和显式连接区别

隐式连接（Implicit Join）和显式连接（Explicit Join）都是 SQL 中用于关联多个表的方式，但它们有一些关键的区别：

- 隐式连接（Implicit Join）

> 隐式连接是通过在 `FROM` 子句中列出多个表，并在 `WHERE` 子句中通过条件来进行关联。在隐式连接中，你不使用 `JOIN` 关键字，而是直接在 `WHERE` 子句中指定连接条件。

​	示例：

```sql
SELECT e.emp_no, e.first_name, d.dept_name
FROM employees e, dept_emp de, departments d
WHERE e.emp_no = de.emp_no
  AND de.dept_no = d.dept_no;
```

**特点：**

> - 使用 `FROM` 子句列出多个表。
>
> - 在 `WHERE` 子句中指定连接条件。
> - 可以使用多个表的条件来描述表之间的关系。

- 显式连接（Explicit Join）

> 显式连接使用 `JOIN` 关键字明确地定义表之间的连接。它通过 `ON` 子句指定连接条件。显式连接可以使用不同类型的连接，如 `INNER JOIN`、`LEFT JOIN`、`RIGHT JOIN` 等，来表示表之间的不同连接方式。

示例：

```sql
SELECT e.emp_no, e.first_name, d.dept_name
FROM employees e
JOIN dept_emp de ON e.emp_no = de.emp_no
JOIN departments d ON de.dept_no = d.dept_no;
```

**特点：**

> - 使用 `JOIN` 来连接表，并使用 `ON` 子句指定连接条件。
> - 提高查询的可读性和可维护性。
> - 可以明确地指定不同类型的连接（`INNER JOIN`、`LEFT JOIN` 等），使查询逻辑更加清晰。

**主要区别：**

| 特性         | 隐式连接 (Implicit Join)                                     | 显式连接 (Explicit Join)                                     |
| ------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **语法**     | 使用 `FROM` 子句列出多个表，并在 `WHERE` 子句中指定连接条件。 | 使用 `JOIN` 和 `ON` 子句明确指定连接条件。                   |
| **可读性**   | 由于连接条件写在 `WHERE` 子句中，可能比较难以理解。          | 显式连接通过 `JOIN` 和 `ON` 子句提高了可读性。               |
| **功能限制** | 不容易表达不同类型的连接，如 `LEFT JOIN` 或 `RIGHT JOIN`。   | 可以清楚地使用不同类型的连接，如 `INNER JOIN`、`LEFT JOIN`、`RIGHT JOIN` 等。 |
| **历史**     | 早期的 SQL 语法（如 SQL-89）。                               | 现代 SQL 标准语法（SQL-92 及之后）。                         |
| **错误率**   | 在复杂查询中，容易漏掉连接条件，导致笛卡尔积或逻辑错误。     | 更清晰的连接逻辑，有助于减少错误。                           |

总结：

- **隐式连接**：较老的语法，通常不推荐使用，尤其在涉及多个表时容易导致查询逻辑不清晰。
- **显式连接**：现代SQL更推荐使用的方式, 使用 `JOIN` 和 `ON` 明确表示表之间的关系,易于理解,维护和调试。

显式连接通常更安全、更易于理解，并且在处理复杂的查询时更加灵活。如果可能，建议尽量使用显式连接。



练习：

- 把我们前面作业的第6 和 第9题 改成显示连接方式：

  ``` sql
  
  ```



## 八：组函数：

> 如果我们要做一些统计、计算、平均数等操作，这个时候，就需要使用了组函数：

#### 1：统计人数（个数）：

> count( 主键 )

``` sql
-- 1：统计员工个数
select count(emp_no) from employees
select count(*) from employees
```

####  2：求总和：

> sum()

``` sql
-- 算出所有的人工资总额
select sum(salary) from salaries
```

####  3：求平均值：

> avg()

``` sql
-- 计算出工资的平均数
select avg(salary) from salaries
```

####  4：求最大值：

> max()

``` sql
-- 查询出最大的工资数
select max(salary) from salaries
```

####  5：求最小值：

> min()

``` sql
-- 查询出，最小工资数
select min(salary) from salaries
```



## 九：子查询：

子查询是嵌套在另一个查询中的查询。它通常用于在 `SELECT`、`INSERT`、`UPDATE` 或 `DELETE` 语句中作为条件一部分。

子查询可以返回单个值、一组值或一个表。

#### 1：返回单个值的子查询

> 查询出最高工资员工的信息

``` sql
select emp_no from salaries where salary = (select min(salary) from salaries)
```

#### 2：返回多个值的子查询：

> 请查询出工资大于50000的员工信息，要有员工名称：

``` sql
select * from employees where emp_no in (select emp_no from salaries where salary > 50000)
```

练习：

- 请查询出大于平均工资的员工信息（只要员工号）
- 请统计d003号部门的员工人数
- 请计算出d004号部门员工的工资总数

参数答案：

``` sql

```



#### 3：查询后的分组

- 请统计各部门的员工人数

  ``` sql
  select dept_no, count(emp_no)
  from dept_emp group by dept_no
  ```



练习：

- 统计所有男员工和女员工的人数

  ``` sql
  
  ```



#### 4: 使用左连接，来确保数据不丢失

- 统计各部门的员工人数，要有部门名称 （部门不能少）

  ``` sql
  
  ```




#### 5：分组后的筛选

- 统计各部门的员工人数，要有部门名称 ，保留人数大于3大部门数据

  > 分组之后的数据筛选，要使用 having ，不能用where

  ``` sql
  
  ```



#### 6：子查询的结果当成一张表：

- 查询返回每个员工信息（名称）及其所在部门（有部门名）的平均工资

``` sql

```



	## 十：相关子查询：

相关子查询是依赖于外部查询中的值的子查询。它的执行依赖于外部查询的当前行。

- 查找工资高于其所在部门平均工资的员工

``` sql

```



### 注意事项

- **性能**：复杂的子查询，尤其是相关子查询，可能会对性能产生负面影响。在可能的情况下，考虑使用连接（`JOIN`）替代子查询，因为数据库引擎通常会对连接进行更高效的优化。

- **可读性**：复杂的查询可能会变得难以理解和维护。确保适当地注释和文档化你的查询。

  总的来说，SQLite 提供了强大的子查询功能，包括相关子查询，这使得它能够在各种复杂的数据检索任务中发挥作用。



## 十：表的外键

> sqlite中不支持直接修改表，设置外键。
>
> 只能在创建表的时候，就设置好外键。

示例：

``` sql
CREATE TABLE "student" ( 
    `id` INTEGER PRIMARY KEY AUTOINCREMENT, 
    `name` TEXT NOT NULL, 
    `age` INTEGER, `gender` TEXT, 
    `birthday` datetime, 
    `class_id` INTEGER,
    -- 添加外部的class_room.id 为当前class_id列的外键
	foreign key(class_id) references class_room(id)
 )
```

- 设置好外键之后，当前列的值，就不能随便设置，要依据引用的表的值来设置
- 当一个表，被别的表当外键引用时，被引用的表的值，不能随便删除。因为这个值，很可能被引用了。



## 十一：三大范式：

​		关系数据库中的关系必须满足一定的要求。满足不同程度要求的为不同范式。数据库的设计范式是数据库设计所需要满足的规范。只有理解数据库的设计范式，才能设计出高效率、优雅的数据库，否则可能会设计出错误的数据库.

​		目前，主要有六种范式：第一范式、第二范式、第三范式、BC范式、第四范式和第五范式。满足最低要求的叫第一范式，简称1NF。在第一范式基础上进一步满足一些要求的为第二范式，简称2NF。其余依此类推。

​		范式可以避免数据冗余，减少数据库的空间，减轻维护数据完整性的麻烦，但是操作困难，因为需要联系多个表才能得到所需要数据，而且范式越高性能就会越差。要权衡是否使用更高范式是比较麻烦的，一般在项目中，用得最多的也就是第三范式，一般使用到第三范式也就足够了，性能好而且方便管理数据。



#### 1：函数依赖:

-  如果一个表中某一个字段Y的值是由另外一个字段或一组字段X的值来确定的，就称为Y函数依赖于X。



#### 一：第一范式：

> 特点：**原子性，字段不可再分割**
>
> 定义：如果关系模式R的每个关系r的属性都是不可分的数据项，那么就称R是第一范式的模式。
>
> 简单的说，每一个属性都是原子项，不可分割。
>
> 1NF是关系模式应具备的最起码的条件，如果数据库设计不能满足第一范式，就不称为关系型数据库。关系数据库设计研究的关系规范化是在1NF之上进行的

- 例如(学生信息表)：

| 学生编号 | 姓名 | 性别 | 联系方式                        |
| -------- | ---- | ---- | ------------------------------- |
| 20080901 | 张三 | 男   | email:zs@126.com,phone:88886666 |
| 20080902 | 李四 | 女   | email:ls@126.com,phone:66668888 |

 以上的表就不符合，第一范式：联系方式字段可以再分，所以变更为正确的是：

| 学生编号 | 姓名 | 性别 | 联系方式          | 电话           |
| -------- | ---- | ---- | ----------------- | -------------- |
| 20080901 | 张三 | 男   | email:zs@126.com, | phone:88886666 |
| 20080902 | 李四 | 女   | email:ls@126.com, | phone:66668888 |



#### 二：第二范式（2NF）

> 特点：**属性完全依赖于主键; 没有部份依赖**
>
> 定义：如果关系模式R是1NF，且每个非主属性完全函数依赖于候选键，那么就称R是第二范式。
>
> 简单的说，第二范式要满足以下的条件：首先要满足第一范式，其次每个非主属性要完全函数依赖与候选键，或者是主键。也就是说，每个非主属性是由整个主键函数决定的，而不能由主键的一部分来决定。

- 例如(学生选课表):

| 学生 | 课程   | 教师   | 教师职称 | 教材             | 教室 | 上课时间 |
| ---- | ------ | ------ | -------- | ---------------- | ---- | -------- |
| 李四 | Spring | 张老师 | Java讲师 | Spring深入浅出   | 301  | 08:00    |
| 张三 | Struts | 杨老师 | Java讲师 | Struts in Action | 203  | 13:30    |

 这里通过（学生，课程）可以确定教师、教师职称，教材，教室和上课时间，所以可以把（学生，课程）作为主键。但是，教材并不完全依赖于（学生，课程），只拿出课程就可以确定教材，因为一个课程，一定指定了某个教材。这就叫不完全依赖，或者部分依赖。出现这种情况，就不满足第二范式。

- 修改后，

选课表：

| 学生 | 课程   | 教师   | 教师职称 | 教室 | 上课时间 |
| ---- | ------ | ------ | -------- | ---- | -------- |
| 李四 | Spring | 张老师 | Java讲师 | 301  | 08:00    |
| 张三 | Struts | 杨老师 | Java讲师 | 203  | 13:30    |

课程表：

| 课程   | 教材             |
| ------ | ---------------- |
| Spring | Spring深入浅出   |
| Struts | Struts in Action |

所以，第二范式可以说是消除部分依赖。第二范式可以减少插入异常，删除异常和修改异常。

#### 三：第三范式（3NF）

> 特点：**属性不依赖于其它非主属性; 没有传递依赖**
>
> 定义：如果关系模式R是2NF，且关系模式R（U，F）(u为属性集，F是U上的一组函数依赖)中的所有非主属性对任何候选关键字都不存在传递依赖，则称关系R是属于第三范式。
>
> 简单的说，第三范式要满足以下的条件：首先要满足第二范式，其次非主属性之间不存在函数依赖。由于满足了第二范式，表示每个非主属性都函数依赖于主键。如果非主属性之间存在了函数依赖，就会存在传递依赖，这样就不满足第三范式。

上表中, 教师依赖于（学生，课程），而教师职称又依赖于教师，这叫传递依赖。第三范式就是要消除传递依赖。

- 修改后

选课表：

| 学生 | 课程   | 教师   | 教室 | 上课时间 |      |
| ---- | ------ | ------ | ---- | -------- | ---- |
| 李四 | Spring | 张老师 | 301  | 08:00    |      |
| 张三 | Struts | 杨老师 | 203  | 13:30    |      |

​		上例中修改后的选课表中，一个教师能确定一个教师职称。

教师表：

| 教师   | 教师职称 |
| ------ | -------- |
| 张老师 | java讲师 |
| 张老师 | java讲师 |

 课程表：

这样，新教师的职称在没被选课的时候也有地方存了，没人选这个教师的课的时候教师的职称也不至于被删除，修改教师职称时只修改教师表就可以了。



## 十二：常用的一些函数：

#### 1: 时间相关：

``` sql
-- 得到当前年月日  --------------------------- 时间是比较常用的
select date()

-- 得到当前时间
select time();

-- 得到当前年月日 ,时分秒
select datetime()
```

#### 2：格式化时间：

> %Y		 代表年份
>
> %m		代表月份
>
> %d		 代表日期
>
> %H		代表小时
>
> %M		代表分钟
>
> %S		 代表秒

``` sql
-- 根据格式得到时间 
select   strftime(  '%Y' , datetime('now')) ;   -- 得到年份
select strftime(  '%m' , datetime('now'));   -- 得到月份
select strftime(  '%d' , datetime('now'));   -- 得到日期
-- %H   小时     %M  分钟   %S  秒
select strftime(  '%Y-%m-%d %H:%M:%S' , datetime('now'));   -- 得到年月日 ，时分秒

-- strftime()函数的结果是一个text ，可以和 100 (integer) 运算是因为它有一个隐式转换
select   strftime(  '%Y' , datetime('now'))  + 100 ;
```

#### 3：字符中相关函数

``` sql
-- 得到字符串的长度 
select length('hello,sqlite')

-- 截取字符串   substr(s, x, y)  从s 的x位置 开始截取y长度的字符串
select substr('hello,sqlite',7, 6)

-- 转换大写小写：
select upper('hello')
select lower('SQLITE')

-- 修空格
select trim('     hello      ') as str;
select ltrim('             hello') as str;
select rtrim('hello                                       ') as str;

-- 替换
select replace('hello,sqlite', 'sqlite', 'every one')
```

