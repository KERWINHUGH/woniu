#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

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

// JSON数组转Person结构体数组 (二级指针完成)
Person** json_array_to_person_two(const char* json_str, int* count) {
    // 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);
    if (!root) {
        fprintf(stderr, "JSON解析失败: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    // 检查是否是数组
    if (!cJSON_IsArray(root)) {
        fprintf(stderr, "JSON不是数组类型\n");
        cJSON_Delete(root);
        return NULL;
    }

    // 获取数组大小
    int array_size = cJSON_GetArraySize(root);
    if (array_size == 0) {
        fprintf(stderr, "JSON数组为空\n");
        cJSON_Delete(root);
        *count = 0;
        return NULL;
    }

    // 分配结构体数组指针
    Person** persons = (Person**)malloc(array_size * sizeof(Person*));
    if (!persons) {
        fprintf(stderr, "内存分配失败\n");
        cJSON_Delete(root);
        *count = 0;
        return NULL;
    }

    // 遍历JSON数组，解析每个元素
    for (int i = 0; i < array_size; i++) {
        cJSON* item = cJSON_GetArrayItem(root, i);
        if (!item || !cJSON_IsObject(item)) {
            fprintf(stderr, "JSON数组中的第%d个元素不是对象\n", i + 1);
            continue;
        }

        // 创建并初始化Person结构体
        Person* p = (Person*)malloc(sizeof(Person));
        memset(p, 0, sizeof(Person));

        // 提取字段（需检查字段是否存在且类型正确）
        cJSON* name_item = cJSON_GetObjectItem(item, "name");
        if (name_item && cJSON_IsString(name_item)) {
            strncpy(p->name, name_item->valuestring, sizeof(p->name) - 1);
        }

        cJSON* age_item = cJSON_GetObjectItem(item, "age");
        if (age_item && cJSON_IsNumber(age_item)) {
            p->age = age_item->valueint;
        }

        cJSON* height_item = cJSON_GetObjectItem(item, "height");
        if (height_item && cJSON_IsNumber(height_item)) {
            p->height = height_item->valuedouble;
        }

        cJSON* is_student_item = cJSON_GetObjectItem(item, "is_student");
        if (is_student_item && cJSON_IsBool(is_student_item)) {
            p->is_student = cJSON_IsTrue(is_student_item);
        }

        // 将Person结构体存入数组
        persons[i] = p;
    }

    *count = array_size;  // 返回数组大小
    cJSON_Delete(root);   // 释放JSON对象内存
    return persons;       // 需调用者手动 free(persons) 和 其中每个 Person
}

// JSON数组转Person结构体数组（使用一级指针）
Person* json_array_to_person_one(const char* json_str, int* count) {
    // 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);
    if (!root) {
        fprintf(stderr, "JSON解析失败: %s\n", cJSON_GetErrorPtr());
        *count = 0;
        return NULL;
    }

    // 检查是否是数组
    if (!cJSON_IsArray(root)) {
        fprintf(stderr, "JSON不是数组类型\n");
        cJSON_Delete(root);
        *count = 0;
        return NULL;
    }

    // 获取数组大小
    int array_size = cJSON_GetArraySize(root);
    if (array_size == 0) {
        fprintf(stderr, "JSON数组为空\n");
        cJSON_Delete(root);
        *count = 0;
        return NULL;
    }

    // 分配连续的内存块
    Person* persons = (Person*)malloc(array_size * sizeof(Person));
    if (!persons) {
        fprintf(stderr, "内存分配失败\n");
        cJSON_Delete(root);
        *count = 0;
        return NULL;
    }
	// 初始化操作
	memset(persons, 0,   array_size * sizeof(Person) );
	
    // 遍历JSON数组，解析每个元素
    for (int i = 0; i < array_size; i++) {
    
        cJSON* item = cJSON_GetArrayItem(root, i);
        
        if (!item || !cJSON_IsObject(item)) {
            fprintf(stderr, "JSON数组中的第%d个元素不是对象\n", i + 1);
            memset(&persons[i], 0, sizeof(Person));  // 初始化为默认值
            continue;
        }

        // 提取字段（需检查字段是否存在且类型正确）
        cJSON* name_item = cJSON_GetObjectItem(item, "name");
        if (name_item && cJSON_IsString(name_item)) {
            strncpy(persons[i].name, name_item->valuestring, sizeof(persons[i].name) - 1);
        }

        cJSON* age_item = cJSON_GetObjectItem(item, "age");
        if (age_item && cJSON_IsNumber(age_item)) {
            persons[i].age = age_item->valueint;
        }

        cJSON* height_item = cJSON_GetObjectItem(item, "height");
        if (height_item && cJSON_IsNumber(height_item)) {
            persons[i].height = height_item->valuedouble;
        }

        cJSON* is_student_item = cJSON_GetObjectItem(item, "is_student");
        if (is_student_item && cJSON_IsBool(is_student_item)) {
            persons[i].is_student = cJSON_IsTrue(is_student_item);
        }
    }

    *count = array_size;  // 返回数组大小
    cJSON_Delete(root);   // 释放JSON对象内存
    return persons;       // 需调用者手动 free(persons)
}


int main() {
	puts("---------------结构体转json-----------------");
	Person p = {"李四", 33, 178.8 , 1};
	char *json = person_to_json(&p);
	printf("json:%s \n", json);

	puts("---------------json转结构体-----------------");
	Person *p2 = json_to_person(json);
	printf("姓名：%s , 年龄：%d , 身高：%f , 是否学生：%d \n", p2->name, p2->age, p2->height, p2->is_student);

	puts("");
	puts("---------------测试结构体数组转json-----------------");
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


	// 假设我们有如下JSON字符串 ------------------------------------
	const char* json_array_str = "[{\"name\":\"Alice\",\"age\":25,\"height\":1.65,\"is_student\":true},"
								 "{\"name\":\"Bob\",\"age\":30,\"height\":1.80,\"is_student\":false}]";

	puts("");
	puts("---------------测试JSON数组转结构体数组（一级指针）-----------------");
	// 调用函数
	int person_count = 0;
	Person* persons_array = json_array_to_person_one(json_array_str, &person_count);

	if (persons_array) {
		printf("解析出的Person数组大小：%d\n", person_count);
		for (int i = 0; i < person_count; i++) {
			Person* p = &persons_array[i];
			printf("姓名：%s , 年龄：%d , 身高：%f , 是否学生：%d \n",
				   p->name, p->age, p->height, p->is_student);
		}
		free(persons_array);  // 释放整个数组
	} else {
		printf("JSON数组解析失败\n");
	}
	
	puts("");
	puts("---------------测试JSON数组转结构体数组(二级指针)-----------------");
	// 调用函数
	int person_count2 = 0;
	Person** persons_array2 = json_array_to_person_two(json_array_str, &person_count2);

	if (persons_array2) {
		printf("解析出的Person数组大小：%d\n", person_count2);
		
		for (int i = 0; i < person_count2; i++) {
			Person* p = persons_array2[i];
			printf("姓名：%s , 年龄：%d , 身高：%f , 是否学生：%d \n",
				   p->name, p->age, p->height, p->is_student);
			free(p);  // 释放每个Person结构体
		}
		free(persons_array2);  // 释放Person指针数组
	} else {
		printf("JSON数组解析失败\n");
	}
	
    return 0;
}   


















 
