## 一、JSON安装

方式一、双击老师提供的MDK-Packs.cJSON.1.0.0 .pack，即可安装cJSON到ｋｅｉｌ中。

![image-20241109090445632](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202411090904771.png)

方式二：如果不在ｋｅｉｌ中使用ｃｊｓｏｎ， 也可以直接使用我发的两个cJSON.c,CJSON.h文件。



## 二、解析

### 修改系统配置

按照如下位置，设置堆和栈的大小，因为解析JSON，需要的空间较大，因为文件是只读文件，需要先去掉只读状态：

![image-20241109090841272](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202411090908397.png)

![image-20241109090709323](https://gitee.com/zhangshoudao/pic_bed/raw/master/img/202411090907532.png)



### 解析简单的json

````c
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

int main() { 
    // JSON 字符串
    const char *json_string = "{\"name\":\"zhangsan\",\"age\":19,\"address\":\"nanjing\"}";
    // 解析 JSON 字符串
    cJSON *root = cJSON_Parse(json_string);
	 if (root ==NULL)
     {
         return;
     }
    // 获取 "name" 字段
    cJSON *name_item = cJSON_GetObjectItem(root, "name");
    if (cJSON_IsString(name_item) && (name_item->valuestring != NULL)) {
        printf("Name: %s\n", name_item->valuestring);
    } else {
        printf("Name not found or is not a string.\n");
    }

    // 获取 "age" 字段
    cJSON *age_item = cJSON_GetObjectItem(root, "age");
    if (cJSON_IsNumber(age_item)) {
        printf("Age: %d\n", age_item->valueint);
    } else {
        printf("Age not found or is not a number.\n");
    }

    // 获取 "address" 字段
    cJSON *address_item = cJSON_GetObjectItem(root, "address");
    if (cJSON_IsString(address_item) && (address_item->valuestring != NULL)) {
        printf("Address: %s\n", address_item->valuestring);
    } else {
        printf("Address not found or is not a string.\n");
    }

    // 释放内存
    cJSON_Delete(root);

    return 0;
}

````





### 带有数组的json

````c
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

int main() {
    // JSON 字符串
    const char *json_string = "{\"name\":\"zhangsan\",\"age\":19,\"address\":[\"nanjing\",\"beijing\"]}";

    // 解析 JSON 字符串
    cJSON *root = cJSON_Parse(json_string);
    if (root == NULL) {
        printf("Error parsing JSON.\n");
        return -1;
    }
    
    // 获取 "address" 字段（它是一个数组）
    cJSON *address_array = cJSON_GetObjectItem(root, "address");
    if (address_array == NULL || !cJSON_IsArray(address_array)) {
        printf("Address is not found or is not an array.\n");
        cJSON_Delete(root);
        return -1;
    }

    // 遍历数组并获取每个元素的值
    int array_size = cJSON_GetArraySize(address_array);
    for (int i = 0; i < array_size; i++) {
        cJSON *address_item = cJSON_GetArrayItem(address_array, i);
        if (cJSON_IsString(address_item) && (address_item->valuestring != NULL)) {
            printf("Address[%d]: %s\n", i, address_item->valuestring);
        } else {
            printf("Address item %d is not a string or is NULL.\n", i);
        }
    }

    // 释放内存
    cJSON_Delete(root);

    return 0;
}

````



keil5

````c
OLED_Init(); // 初始化 OLED

     // JSON 字符串
    const char *json_string = "{\"name\":\"zhangsan\",\"age\":19,\"address\":[\"nanjing\",\"beijing\"]}";

    // 解析 JSON 字符串
    cJSON *root = cJSON_Parse(json_string);
	
    // 获取 "address" 字段（它是一个数组）
    cJSON *address_array = cJSON_GetObjectItem(root, "address");

    // 遍历数组并获取每个元素的值
    int array_size = cJSON_GetArraySize(address_array);
	
    for (int i = 0; i < array_size; i++) {
        cJSON *address_item = cJSON_GetArrayItem(address_array, i);
        OLED_ShowString(i+1, 1, address_item->valuestring);
    }

    // 显示字符串到 OLED
    

    // 释放内存
    cJSON_Delete(root);
````

### json数组对象

````c
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

int main() {
    // JSON 字符串
    const char *json_string = "[{ \"name\": \"zhangsan\", \"age\": 19, \"address\": [\"nanjing\", \"beijing\"] },"
                              "{ \"name\": \"lisi\", \"age\": 20, \"address\": [\"tianjing\", \"guangdong\"] }]";

    // 解析 JSON 字符串
    cJSON *root = cJSON_Parse(json_string);
    if (root == NULL) {
        printf("Error parsing JSON.\n");
        return -1;
    }

    // 获取 JSON 数组
    if (!cJSON_IsArray(root)) {
        printf("Root is not an array.\n");
        cJSON_Delete(root);
        return -1;
    }

    // 遍历数组并获取每个对象的 "name" 字段
    int array_size = cJSON_GetArraySize(root);
    for (int i = 0; i < array_size; i++) {
        cJSON *person_item = cJSON_GetArrayItem(root, i);
        if (cJSON_IsObject(person_item)) {
            cJSON *name_item = cJSON_GetObjectItem(person_item, "name");
            if (cJSON_IsString(name_item) && (name_item->valuestring != NULL)) {
                printf("Person[%d] Name: %s\n", i, name_item->valuestring);
            } else {
                printf("Name item for person[%d] is not a string or is NULL.\n", i);
            }
        } else {
            printf("Array item[%d] is not an object.\n", i);
        }
    }

    // 释放内存
    cJSON_Delete(root);

    return 0;
}

````



kile5

````c
	 OLED_Init(); // 初始化 OLED

    // JSON 字符串
    const char *json_string = "[{ \"name\": \"zhangsan\", \"age\": 19, \"address\": [\"nanjing\", \"beijing\"] },"
                              "{ \"name\": \"lisi\", \"age\": 20, \"address\": [\"tianjing\", \"guangdong\"] }]";

    // 解析 JSON 字符串
    cJSON *root = cJSON_Parse(json_string);

    // 遍历数组并获取每个对象的 "name" 字段
    int array_size = cJSON_GetArraySize(root);
    for (int i = 0; i < array_size; i++) {
        cJSON *person_item = cJSON_GetArrayItem(root, i);
        
            cJSON *name_item = cJSON_GetObjectItem(person_item, "name");
            
			OLED_ShowString(i+1,1,name_item->valuestring);
    }
    

    // 释放内存
    cJSON_Delete(root);
````



### chatGPT4

https://platform.openai.com/docs/api-reference/chat/create

````c
{
  "id": "chatcmpl-123",
  "object": "chat.completion",
  "created": 1677652288,
  "model": "gpt-4o-mini",
  "system_fingerprint": "fp_44709d6fcb",
  "choices": [{
    "index": 0,
    "message": {
      "role": "assistant",
      "content": "\n\nHello there, how may I assist you today?",
    },
    "logprobs": null,
    "finish_reason": "stop"
  }],
  "usage": {
    "prompt_tokens": 9,
    "completion_tokens": 12,
    "total_tokens": 21
  }
}

````



````c
const char *json_string = "{"
                              "  \"id\": \"chatcmpl-123\","
                              "  \"object\": \"chat.completion\","
                              "  \"created\": 1677652288,"
                              "  \"model\": \"gpt-4o-mini\","
                              "  \"system_fingerprint\": \"fp_44709d6fcb\","
                              "  \"choices\": [{"
                              "    \"index\": 0,"
                              "    \"message\": {"
                              "      \"role\": \"assistant\","
                              "      \"content\": \"Hello there, how may I assist you today?\""
                              "    },"
                              "    \"logprobs\": null,"
                              "    \"finish_reason\": \"stop\""
                              "  }],"
                              "  \"usage\": {"
                              "    \"prompt_tokens\": 9,"
                              "    \"completion_tokens\": 12,"
                              "    \"total_tokens\": 21"
                              "  }"
                              "}";

    // 解析 JSON 字符串
    cJSON *root = cJSON_Parse(json_string);

    // 获取 "choices" 数组
    cJSON *choices_array = cJSON_GetObjectItem(root, "choices");

    // 获取 "message" 对象下的 "content" 字段
    cJSON *first_choice = cJSON_GetArrayItem(choices_array, 0);

    cJSON *message_item = cJSON_GetObjectItem(first_choice, "message");

    cJSON *content_item = cJSON_GetObjectItem(message_item, "content");

    // 输出 content
    
	OLED_ShowString(1,1,content_item->valuestring);

    // 释放内存
    cJSON_Delete(root);
````



````
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: gcc.exe 生成活动文件",
            "command": "D:\\software\\mingw64\\bin\\gcc.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${fileDirname}\\*.c",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-fexec-charset=GBK"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "调试器生成的任务。"
        }
    ],
    "version": "2.0.0"
}
````



注意：

* 在使用cJSON_Parse()获取cJSON指针后，若不再使用了，则需要调用cJSON_Delete()对其释放，否则会导致内存泄漏。

## 三、创建JSON字符串

````c
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

char Json[1024] = { '\0' };


int main() {
    
    // 创建 JSON 对象
    cJSON* root = cJSON_CreateObject();

    // 添加基本键值对
    cJSON_AddStringToObject(root, "name", "John");
    cJSON_AddNumberToObject(root, "age", 30);

    // 添加嵌套的 JSON 对象（地址）
    cJSON* address = cJSON_CreateObject();//{}
    cJSON_AddStringToObject(address, "street", "123 Main St");
    cJSON_AddStringToObject(address, "city", "Anytown");
    cJSON_AddStringToObject(address, "postalCode", "12345");
    cJSON_AddItemToObject(root, "address", address);

    // 添加数组
    cJSON* interests = cJSON_CreateArray();//["reading,gardening,cooking"]
    cJSON_AddItemToArray(interests, cJSON_CreateString("Reading"));
    cJSON_AddItemToArray(interests, cJSON_CreateString("Gardening"));
    cJSON_AddItemToArray(interests, cJSON_CreateString("Cooking"));
    cJSON_AddItemToObject(root, "interests", interests);

    // 将 JSON 对象转为字符串
//    char* jsonString = cJSON_Print(root);
    char* jsonString = cJSON_PrintUnformatted(root);
    printf("JSON Object:\n%s\n", jsonString);

    // 释放内存
    cJSON_Delete(root);
    free(jsonString);

    return 0;
}

````

## 四、案例

#### 天气解析

````c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h" // 引入CJSON库

// 定义结构体
typedef struct {
    char name[50];
    char country[50];
    char weather_text[50];
    char temperature[10];
    char last_update[50];
} WeatherInfo;

int main8() {
    // JSON字符串
    const char *json_string = "{\"results\":[{\"location\":{\"id\":\"WT3Q0FW9ZJ3Q\",\"name\":\"Wuhan\",\"country\":\"CN\",\"path\":\"Wuhan,Wuhan,Hubei,China\",\"timezone\":\"Asia/Shanghai\",\"timezone_offset\":\"+08:00\"},\"now\":{\"text\":\"Sunny\",\"code\":\"0\",\"temperature\":\"28\"},\"last_update\":\"2024-04-26T15:04:17+08:00\"}]}";

    // 解析JSON
    cJSON *root = cJSON_Parse(json_string);
    if (root == NULL) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        return 1;
    }

    // 获取results数组
    cJSON *results = cJSON_GetObjectItem(root, "results");
    if (results == NULL) {
        printf("No results found.\n");
        cJSON_Delete(root);
        return 1;
    }

    // 获取第一个元素
    cJSON *result = cJSON_GetArrayItem(results, 0);
    if (result == NULL) {
        printf("No result found.\n");
        cJSON_Delete(root);
        return 1;
    }

    // 获取location对象
    cJSON *location = cJSON_GetObjectItem(result, "location");
    if (location == NULL) {
        printf("No location found.\n");
        cJSON_Delete(root);
        return 1;
    }

    // 获取now对象
    cJSON *now = cJSON_GetObjectItem(result, "now");
    if (now == NULL) {
        printf("No now found.\n");
        cJSON_Delete(root);
        return 1;
    }

    // 从JSON中提取所需信息并存储在结构体中
    WeatherInfo weather_info;
    strcpy(weather_info.name, cJSON_GetObjectItem(location, "name")->valuestring);
    strcpy(weather_info.country, cJSON_GetObjectItem(location, "country")->valuestring);
    strcpy(weather_info.weather_text, cJSON_GetObjectItem(now, "text")->valuestring);
    //weather_info.temperature = cJSON_GetObjectItem(now, "temperature")->valueint;
    strcpy(weather_info.temperature, cJSON_GetObjectItem(now, "temperature")->valuestring);
    strcpy(weather_info.last_update, cJSON_GetObjectItem(result, "last_update")->valuestring);

    // 打印信息
    printf("Name: %s\n", weather_info.name);
    printf("Country: %s\n", weather_info.country);
    printf("Weather Text: %s\n", weather_info.weather_text);
    printf("Temperature: %s\n", weather_info.temperature);
    printf("Last Update: %s\n", weather_info.last_update);

    // 释放JSON对象
    cJSON_Delete(root);

    getchar();


    

    return 0;
}

````



#### 生成GPTJSON

````json
{
  "created": 1589478378,//时间的表示 Long
  "data": [
    {
      "url": "https://..."
    },
    {
      "url": "https://..."
    }
  ]
}
````



````c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

int main() {
    // 创建根对象
    cJSON *root = cJSON_CreateObject();
    
    // 添加created字段
    cJSON_AddNumberToObject(root, "created", 1589478378);
    
    // 创建data数组
    cJSON *data = cJSON_CreateArray();
    
    // 创建第一个url对象
    cJSON *url1 = cJSON_CreateObject();
    cJSON_AddStringToObject(url1, "url", "https://...");
    
    // 创建第二个url对象
    cJSON *url2 = cJSON_CreateObject();
    cJSON_AddStringToObject(url2, "url", "https://...");
    
    // 将url对象添加到data数组中
    cJSON_AddItemToArray(data, url1);
    cJSON_AddItemToArray(data, url2);
    
    // 将data数组添加到根对象中
    cJSON_AddItemToObject(root, "data", data);
    
    // 打印JSON字符串
    char *json_string = cJSON_Print(root);
    printf("%s\n", json_string);
    
    // 释放内存
    cJSON_Delete(root);
    free(json_string);
    
    return 0;
}

````

