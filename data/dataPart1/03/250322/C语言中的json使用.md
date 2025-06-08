# C语言中的json使用：

> 在 C 语言中使用 JSON 需要借助第三方库，常用库如:
>
> -  **cJSON**（轻量级）
>
> - **jansson**: 更严格的类型检查，适合复杂场景。
> - **json-c**: 支持 JSON 合并和修改，适合动态数据操作。



## 一：cJSON

> 轻量级，简单好用

#### 1：安装cJSON

``` bash
git clone https://github.com/DaveGamble/cJSON.git

cd cJSON
make
sudo make install  # 安装到系统目录

```

- 如果安装好之后，还会提示找不到cJSON

```bash
# 修改makefile文件如下：
# 定义生成的可执行文件  
CFLAGS += -I/usr/local/include/cjson
LDFLAGS += -L/usr/local/lib -lcjson
 
all: thread  
  
normal:   
	@gcc $(n).c -o $(n)
	@./$(n)
    @rm -f $(n)
    
thread:   
    @gcc $(CFLAGS) $(n).c -o $(n) -lpthread $(LDFLAGS)                      
    @./$(n)
    @rm -f $(n)
# 清理生成的文件  
clean:  
    rm -f $(n)
```

![image-20250318215157376](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/yujian/20250318215157.png)

- 修改好后， 如果还不行，还需要 **更新动态链接库缓存**

``` bash
# 更新动态库缓存
yujian@ubuntu:~/文档/net$ sudo ldconfig
[sudo] yujian 的密码：

# 执行：
yujian@ubuntu:~/文档/net$ make n=PersonToJson
JSON: [{
		"name":	"Alice",
		"age":	25,
		"height":	1.65,
		"is_student":	true
	}, {
		"name":	"Bob",
		"age":	30,
		"height":	1.8,
		"is_student":	false
	}]
yujian@ubuntu:~/文档/net$ 

```



#### 2：使用示例：

``` c
/***************************************************
# File Name:    PersonToJson.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Tue 18 Mar 2025 08:52:38 PM CST
****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

// 定义结构体
typedef struct {
    char name[32];
    int age;
    double height;
    int is_student;
} Person;

// 结构体转JSON
char* person_to_json(const Person* p) {
	// 创建JSON对象
    cJSON* root = cJSON_CreateObject();  

    // 添加字段
    cJSON_AddStringToObject(root, "name", p->name);
    cJSON_AddNumberToObject(root, "age", p->age);
    cJSON_AddNumberToObject(root, "height", p->height);
    cJSON_AddBoolToObject(root, "is_student", p->is_student);

    // 生成JSON字符串
    char* json_str = cJSON_Print(root);
    
    cJSON_Delete(root);  // 释放JSON对象内存

    return json_str;  // 需调用者手动 free(json_str)
}

// JSON转结构体
Person* json_to_person(const char* json_str) {
	// 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);  
    if (!root) {
        fprintf(stderr, "JSON解析失败: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    Person* p = (Person*)malloc(sizeof(Person));
    memset(p, 0, sizeof(Person));

    // 提取字段（需检查字段是否存在且类型正确）
    cJSON* item = cJSON_GetObjectItem(root, "name");
    if (item && cJSON_IsString(item)) {
        strncpy(p->name, item->valuestring, sizeof(p->name) - 1);
    }

    item = cJSON_GetObjectItem(root, "age");
    if (item && cJSON_IsNumber(item)) {
        p->age = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "height");
    if (item && cJSON_IsNumber(item)) {
        p->height = item->valuedouble;
    }

    item = cJSON_GetObjectItem(root, "is_student");
    if (item && cJSON_IsBool(item)) {
        p->is_student = cJSON_IsTrue(item);
    }

    cJSON_Delete(root);  // 释放JSON对象内存
    return p;  // 需调用者手动 free(p)
}

// Person数组转JSON
char* person_array_to_json(const Person* persons, int count) {
	// 创建JSON数组
    cJSON* array = cJSON_CreateArray();
     
    // 把结构体数组里的数据，转换成到json数组里面去
    for (int i = 0; i < count; i++) {
    	
    	// 创建每个Person的JSON对象
        cJSON* person_obj = cJSON_CreateObject();  

        // 添加字段
        cJSON_AddStringToObject(person_obj, "name", persons[i].name);
        cJSON_AddNumberToObject(person_obj, "age", persons[i].age);
        cJSON_AddNumberToObject(person_obj, "height", persons[i].height);
        cJSON_AddBoolToObject(person_obj, "is_student", persons[i].is_student);
		
		// 将Person对象添加到数组中
        cJSON_AddItemToArray(array, person_obj);  
    }

	// 转成字符串
    char* json_str = cJSON_Print(array);
    cJSON_Delete(array);  // 释放JSON数组内存
    return json_str;  // 需调用者手动 free(json_str)
}

int main() {
	puts("---------------结构体转json-----------------");
	Person p = {"李四", 33, 178.8 , 1};
	char *json = person_to_json(&p);
	printf("json:%s \n", json);

	puts("---------------json转结构体-----------------");
	Person *p2 = json_to_person(json);
	printf("姓名：%s , 年龄：%d , 身高：%f , 是否学生：%d \n", p2->name, p2->age, p2->height, p2->is_student);

	puts("---------------测试数组-----------------");
    Person persons[] = {
        {"Alice", 25, 1.65, 1},
        {"Bob", 30, 1.80, 0}
    };
    int count = sizeof(persons) / sizeof(persons[0]);

    char* json_str = person_array_to_json(persons, count);
    if (json_str) {
        printf("JSON: %s\n", json_str);
        free(json_str);
    }

    return 0;
}    
```

#### 3：结果：

``` bash
yujian@ubuntu:~/文档/net$ make n=PersonToJson
---------------结构体转json-----------------
json:{
	"name":	"李四",
	"age":	33,
	"height":	178.8,
	"is_student":	true
} 
---------------json转结构体-----------------
姓名：李四 , 年龄：33 , 身高：178.800000 , 是否学生：1 

---------------测试数组-----------------
JSON: [{
		"name":	"Alice",
		"age":	25,
		"height":	1.65,
		"is_student":	true
	}, {
		"name":	"Bob",
		"age":	30,
		"height":	1.8,
		"is_student":	false
	}]

```

#### 4：使用注意：

1. **内存管理**:

   - `cJSON_Print()` 返回的字符串需手动调用 `free()`。
   - `json_to_person()` 返回的结构体指针需手动调用 `free()`。

2. **错误处理**:

   - `cJSON_Parse()` 失败时返回 `NULL`，需检查错误。
   - 提取字段时应验证字段存在性和类型（如 `cJSON_IsString`/`cJSON_IsNumber`）。

3. **数据类型映射**:

   | C 类型         | cJSON 类型         |
   | :------------- | :----------------- |
   | `char[]`       | `cJSON_String`     |
   | `int`          | `cJSON_Number`     |
   | `double`       | `cJSON_Number`     |
   | `int` (布尔值) | `cJSON_True/False` |

4. **跨平台性**:

   - JSON 作为文本协议天然避免字节序问题，适合网络传输。

#### 5：发送 JSON 到网络

``` c
// 服务端发送 JSON
char* json_data = person_to_json(&alice);
send(client_socket, json_data, strlen(json_data), 0);
free(json_data);

// 客户端接收 JSON
char buffer[4096];
recv(server_socket, buffer, sizeof(buffer), 0);
Person* p = json_to_person(buffer);
```



## 二：jansson使用：

#### 1：安装

- Linux 系统（Debian/Ubuntu）

  ```bash
  # 更新包列表
  sudo apt-get update
  
  # 安装开发包（包含头文件和库）
  sudo apt-get install libjansson-dev
  ```

- 开发环境配置

  ``` c
  #include <jansson.h>
  ```

- 编译

  ``` bash
  # Linux/macOS
  gcc -o your_program your_program.c -ljansson
  ```

-  验证安装：

  ``` bash
  # Linux/macOS
  pkg-config --exists jansson && echo "Found" || echo "Not found"
  
  # 查看版本
  pkg-config --modversion jansson
  ```

  

#### 2：使用示例：

``` c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

// 示例结构体
typedef struct {
    int id;
    char *name;
    int is_student;
    double height;
    int *tags;
    size_t tags_count;
} Person;

// 将Person结构体转换为JSON对象
json_t *person_to_json(const Person *p) {
    json_t *root = json_object();
    
    // 添加基本类型字段
    json_object_set_new(root, "id", json_integer(p->id));
    json_object_set_new(root, "name", json_string(p->name));
    json_object_set_new(root, "is_student", json_boolean(p->is_student));
    json_object_set_new(root, "height", json_real(p->height));

    // 处理数组
    json_t *tags = json_array();
    for(size_t i = 0; i < p->tags_count; i++) {
        json_array_append_new(tags, json_integer(p->tags[i]));
    }
    json_object_set_new(root, "tags", tags);

    return root;
}

// 从JSON解析Person结构体
int json_to_person(const json_t *root, Person *p) {
    json_t *obj;
    
    // 解析id
    if(!(obj = json_object_get(root, "id")) return -1;
    p->id = (int)json_integer_value(obj);

    // 解析name
    if(!(obj = json_object_get(root, "name")) || !json_is_string(obj)) return -1;
    p->name = strdup(json_string_value(obj)); // 需要自行释放

    // 解析is_student
    if(!(obj = json_object_get(root, "is_student"))) return -1;
    p->is_student = json_is_true(obj);

    // 解析height
    if(!(obj = json_object_get(root, "height")) || !json_is_real(obj)) return -1;
    p->height = json_real_value(obj);

    // 解析数组
    json_t *tags = json_object_get(root, "tags");
    if(!tags || !json_is_array(tags)) return -1;
    
    p->tags_count = json_array_size(tags);
    p->tags = malloc(p->tags_count * sizeof(int)); // 需要自行释放
    
    for(size_t i = 0; i < p->tags_count; i++) {
        json_t *item = json_array_get(tags, i);
        if(!json_is_integer(item)) {
            free(p->tags);
            return -1;
        }
        p->tags[i] = (int)json_integer_value(item);
    }

    return 0;
}

// 释放Person结构体内存
void free_person(Person *p) {
    free(p->name);
    free(p->tags);
}

int main() {
    // 初始化示例数据
    Person src = {
        .id = 123,
        .name = "Alice",
        .is_student = 1,
        .height = 1.65,
        .tags = (int[]){1, 2, 3},
        .tags_count = 3
    };

    // 转换为JSON
    json_t *json = person_to_json(&src);
    char *json_str = json_dumps(json, JSON_INDENT(2));
    printf("Generated JSON:\n%s\n", json_str);

    // 解析回结构体
    json_error_t error;
    json_t *parsed = json_loads(json_str, 0, &error);
    Person dest;
    if(json_to_person(parsed, &dest) != 0) {
        fprintf(stderr, "Parse failed!\n");
        return 1;
    }

    // 验证数据
    printf("\nParsed data:\n"
           "ID: %d\n"
           "Name: %s\n"
           "Is student: %d\n"
           "Height: %.2f\n"
           "Tags: ",
           dest.id, dest.name, dest.is_student, dest.height);
    for(size_t i = 0; i < dest.tags_count; i++) {
        printf("%d ", dest.tags[i]);
    }
    printf("\n");

    // 释放资源
    free(json_str);
    json_decref(json);
    json_decref(parsed);
    free_person(&dest);

    return 0;
}
```

#### 3：编译指令：

``` bash
gcc -o example example.c -ljansson
```

#### 4：注意和说明：

- 代码说明：

1. `person_to_json()` 使用jansson API构建JSON对象
2. `json_to_person()` 从JSON解析并填充结构体
3. 支持的数据类型包括：
   - 基础类型：整数、字符串、布尔值、浮点数
   - 数组类型：整数数组
4. 包含内存管理：
   - 使用`strdup()`复制字符串
   - 使用`malloc()`分配数组内存
   - `free_person()`用于释放动态内存

- 注意事项：

1. 需要处理可能的JSON解析错误（字段缺失或类型不匹配）
2. 字符串和数组需要深拷贝
3. JSON布尔值通过`json_is_true()`判断
4. 实际使用中需要更完善的错误处理





