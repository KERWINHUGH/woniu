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
#include "json.h"

// 结构体数组转JSON字符串
char* employees_to_json(Employee* employees, int count) {
    cJSON* root = cJSON_CreateArray();
    
    for (int i = 0; i < count; i++) {
        cJSON* emp_obj = cJSON_CreateObject();
        
        cJSON_AddNumberToObject(emp_obj, "id", employees[i].id);
        cJSON_AddStringToObject(emp_obj, "name", employees[i].name);
        cJSON_AddStringToObject(emp_obj, "password", employees[i].password);
        cJSON_AddNumberToObject(emp_obj, "age", employees[i].age);
        cJSON_AddNumberToObject(emp_obj, "salary", employees[i].salary);
        cJSON_AddStringToObject(emp_obj, "genders", gender_to_string(employees[i].genders));
        cJSON_AddStringToObject(emp_obj, "departments", department_to_string(employees[i].departments));
        cJSON_AddStringToObject(emp_obj, "titles", title_to_string(employees[i].titles));
        cJSON_AddStringToObject(emp_obj, "roles", role_to_string(employees[i].roles));
        
        cJSON_AddItemToArray(root, emp_obj);
    }
    
    char* json_str = cJSON_Print(root);
    cJSON_Delete(root);
    return json_str;
}
// JSON字符串转结构体数组
Employee* json_to_employees(const char* json_str, int* count) {
    cJSON* root = cJSON_Parse(json_str);
    if (!root || !cJSON_IsArray(root)) {
        *count = 0;
        return NULL;
    }
    
    int array_size = cJSON_GetArraySize(root);
    Employee* employees = (Employee*)malloc(array_size * sizeof(Employee));
    if (!employees) {
        *count = 0;
        cJSON_Delete(root);
        return NULL;
    }
    
    for (int i = 0; i < array_size; i++) {
        cJSON* item = cJSON_GetArrayItem(root, i);
        if (!cJSON_IsObject(item)) continue;
        
        Employee emp = {0};
        
        // 解析各个字段
        cJSON* id = cJSON_GetObjectItem(item, "id");
        if (cJSON_IsNumber(id)) emp.id = id->valueint;
        
        cJSON* name = cJSON_GetObjectItem(item, "name");
        if (cJSON_IsString(name) && name->valuestring)
            strncpy(emp.name, name->valuestring, USER_LENGTH-1);
        
        cJSON* password = cJSON_GetObjectItem(item, "password");
        if (cJSON_IsString(password) && password->valuestring)
            strncpy(emp.password, password->valuestring, USER_LENGTH-1);
        
        cJSON* age = cJSON_GetObjectItem(item, "age");
        if (cJSON_IsNumber(age)) emp.age = age->valueint;
        
        cJSON* salary = cJSON_GetObjectItem(item, "salary");
        if (cJSON_IsNumber(salary)) emp.salary = (float)salary->valuedouble;
        
        cJSON* genders = cJSON_GetObjectItem(item, "genders");
        if (cJSON_IsString(genders) && genders->valuestring)
            emp.genders = string_to_gender(genders->valuestring);
        
        cJSON* departments = cJSON_GetObjectItem(item, "departments");
        if (cJSON_IsString(departments) && departments->valuestring)
            emp.departments = string_to_department(departments->valuestring);
        
        cJSON* titles = cJSON_GetObjectItem(item, "titles");
        if (cJSON_IsString(titles) && titles->valuestring)
            emp.titles = string_to_title(titles->valuestring);
        
        cJSON* roles = cJSON_GetObjectItem(item, "roles");
        if (cJSON_IsString(roles) && roles->valuestring)
            emp.roles = string_to_role(roles->valuestring);
        
        employees[i] = emp;
    }
    
    *count = array_size;
    cJSON_Delete(root);
    return employees;
}/*
// 示例用法
int main() {
    // 创建测试数据
    Employee employees[2] = {
        {1, "Alice", "pass123", 30, 5000.0f, FEMALE, DEPT_MARKETING, TITLE_MANAGER, ROLE_ADMIN},
        {2, "Bob", "bobpass", 25, 4000.0f, MALE, DEPT_SALES, TITLE_SALES, ROLE_EMPLOYEE}
    };
    
    // 转换为JSON
    char* json = employees_to_json(employees, 2);
    printf("JSON:\n%s\n", json);
    
    // 转换回结构体
    int count;
    Employee* parsed = json_to_employees(json, &count);
    printf("\nParsed %d employees:", count);
    for (int i = 0; i < count; i++) {
        printf("\nEmployee %d: %s, %s, %d, %.1f, %s, %s, %s, %s",
               parsed[i].id,
               parsed[i].name,
               parsed[i].password,
               parsed[i].age,
               parsed[i].salary,
               gender_to_string(parsed[i].genders),
               department_to_string(parsed[i].departments),
               title_to_string(parsed[i].titles),
               role_to_string(parsed[i].roles));
    }
    
    // 释放内存
    free(json);
    free(parsed);
    return 0;
}
*/
// Employee结构体转JSON
char* Employee_to_json(const Employee* p) {
	// 创建JSON对象
    cJSON* root = cJSON_CreateObject();  

    // 添加字段
    cJSON_AddNumberToObject(root, "id", p->id);
    cJSON_AddStringToObject(root, "name", p->name);
    cJSON_AddStringToObject(root, "password", p->password);
    cJSON_AddNumberToObject(root, "age", p->age);
    cJSON_AddNumberToObject(root, "salary", p->salary);
    
    cJSON_AddStringToObject(root, "gender", gender_to_string( p->genders ));//枚举
    cJSON_AddStringToObject(root, "department", department_to_string(p->departments));//
    cJSON_AddStringToObject(root, "title", title_to_string(p->titles));//
    cJSON_AddStringToObject(root, "role", role_to_string(p->roles));// 
    
    // 生成JSON字符串
    //char* json_str = cJSON_Print(root);
    // 生成无格式化的JSON字符串（紧凑格式）
    char* json_str = cJSON_PrintUnformatted(root);    
    
    cJSON_Delete(root);  // 释放JSON对象内存

    return json_str;  // 需调用者手动 free(json_str)
}

// JSON转Employee结构体
Employee* json_to_Employee(const char* json_str) {
	//Employee employee = {0};
	
	// 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);  
    if (!root) {	
        fprintf(stderr, "JSON解析失败: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }
	//确保解析成功
    Employee* p = (Employee*)malloc(sizeof(Employee));
    //memset(p, 0, sizeof(Employee));

    // 提取字段（需检查字段是否存在且类型正确）
    cJSON* item = cJSON_GetObjectItem(root, "id");
    
    if (item && cJSON_IsNumber(item)) {
        p->id = item->valueint;
    }
    
    item = cJSON_GetObjectItem(root, "name");
    if (item && cJSON_IsString(item)) {
        strncpy(p->name, item->valuestring, sizeof(p->name) - 1);
    }

    item = cJSON_GetObjectItem(root, "password");
    if (item && cJSON_IsString(item)) {
        strncpy(p->password, item->valuestring, sizeof(p->password) - 1);
    } 

    item = cJSON_GetObjectItem(root, "age");
    if (item && cJSON_IsNumber(item)) {
        p->age = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "salary");
    if (item && cJSON_IsNumber(item)) {
        p->salary = item->valuedouble;
    }

    item = cJSON_GetObjectItem(root, "gender");
    if (item && cJSON_IsString(item)) {
        p->genders = string_to_gender( item->valuestring ) ;//枚举
    }
    
    item = cJSON_GetObjectItem(root, "department");
    if (item && cJSON_IsString(item)) {
         p->departments = string_to_department( item->valuestring ) ;//枚举
    }
    
    item = cJSON_GetObjectItem(root, "title");
    if (item && cJSON_IsString(item)) {
         p->titles = string_to_title( item->valuestring ) ;//枚举
    }
     
    item = cJSON_GetObjectItem(root, "role");
    if (item && cJSON_IsString(item)) {
         p->roles = string_to_role( item->valuestring ) ;//枚举
    }
    cJSON_Delete(root);  // 释放JSON对象内存
    return p;  // 需调用者手动 free(p)
}


// Employee数组转JSON字符串
char* Employee_array_to_json(const Employee* Employees, int count) {
	// 创建JSON数组
    cJSON* array = cJSON_CreateArray();
     
    // 把结构体数组里的数据，转成到json数组里面去
    for (int i = 0; i < count; i++) {
    	
    	// 创建每个Employee的JSON对象
        cJSON* Employee_obj = cJSON_CreateObject();  

        // 添加字段
        cJSON_AddNumberToObject(Employee_obj, "id", Employees[i].id);
        cJSON_AddStringToObject(Employee_obj, "name", Employees[i].name);
        cJSON_AddStringToObject(Employee_obj, "password", Employees[i].password);
    	cJSON_AddNumberToObject(Employee_obj, "age", Employees[i].age);
    	cJSON_AddNumberToObject(Employee_obj, "salary", Employees[i].salary);
    
    	cJSON_AddStringToObject(Employee_obj, "gender", gender_to_string( Employees[i].genders ));//枚举
    	cJSON_AddStringToObject(Employee_obj, "department", department_to_string(Employees[i].departments));//
    	cJSON_AddStringToObject(Employee_obj, "title", title_to_string(Employees[i].titles));//
   		cJSON_AddStringToObject(Employee_obj, "role", role_to_string(Employees[i].roles));// 
		
		// 将Employee对象添加到数组中
        cJSON_AddItemToArray(array, Employee_obj);  
    }

	// 数据转成字符串
    char* json_str = cJSON_Print(array);
    cJSON_Delete(array);  // 释放JSON数组内存
    return json_str;  // 需调用者手动 free(json_str)
}

// JSON转Employee结构体数组
/*
**参数：json_str：输入的JSON字符串，需要符合特定格式；count：输出参数，返回解析出的管理员数量
**返回值：成功时返回Employee数组指针，需要调用者使用free()释放内存；失败时返回NULL，并通过count返回0
*/
Employee* json_to_Employee_array(const char* json_str, int* count) {
    // 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);
    if (!root) {
        return NULL; // 解析失败
    }

    // 验证根节点是否为数组
    if (!cJSON_IsArray(root)) {
        cJSON_Delete(root);
        return NULL;
    }

    // 获取数组大小并分配内存
    *count = cJSON_GetArraySize(root);
    Employee* Employees = (Employee*)malloc(sizeof(Employee) * (*count));
    if (!Employees) {
        cJSON_Delete(root);
        return NULL;
    }

    // 遍历数组元素
    for (int i = 0; i < *count; i++) {
        cJSON* item = cJSON_GetArrayItem(root, i);
        if (!cJSON_IsObject(item)) {
            free(Employees);
            cJSON_Delete(root);
            *count = 0;
            return NULL;
        }

        // 提取各字段
        cJSON* id_item = cJSON_GetObjectItem(item, "id");
        cJSON* name_item = cJSON_GetObjectItem(item, "name");
        cJSON* password_item = cJSON_GetObjectItem(item, "password");
		cJSON* age_item = cJSON_GetObjectItem(root, "age");
		cJSON* salary_item = cJSON_GetObjectItem(root, "salary");
		cJSON* gender_item = cJSON_GetObjectItem(item, "gender");
		cJSON* department_item = cJSON_GetObjectItem(item, "department");
		cJSON* title_item = cJSON_GetObjectItem(item, "title");
		cJSON* role_item = cJSON_GetObjectItem(item, "role");
	
        // 验证字段存在性和类型
        if (!cJSON_IsNumber(id_item) || 
            !cJSON_IsString(name_item) || 
            !cJSON_IsString(password_item)) {
            free(Employees);
            cJSON_Delete(root);
            *count = 0;
            return NULL;
        }

        // 赋值到结构体
        Employees[i].id = id_item->valueint;
        strncpy(Employees[i].name, name_item->valuestring, sizeof(Employees[i].name)-1);
        Employees[i].name[sizeof(Employees[i].name)-1] = '\0';
        strncpy(Employees[i].password, password_item->valuestring, sizeof(Employees[i].password)-1);
        Employees[i].password[sizeof(Employees[i].password)-1] = '\0';
        Employees[i].age = age_item->valueint;
        Employees[i].salary = salary_item->valueint;
        Employees[i].genders = string_to_gender( gender_item->valuestring );
        Employees[i].departments = string_to_department( department_item->valuestring );
        Employees[i].titles = string_to_title( title_item->valuestring );
 		Employees[i].roles = string_to_role( role_item->valuestring );
    }

    cJSON_Delete(root);
    return Employees;
}

/*
// Employee数组转JSON字符串
char* Employee_array_to_json(const Employee* employees, int count) {
	// 创建JSON数组
    cJSON* array = cJSON_CreateArray();
     
    // 把结构体数组里的数据，转换成到json数组里面去
    for (int i = 0; i < count; i++) {
    	
    	// 创建每个Employee的JSON对象
        cJSON* employee_obj = cJSON_CreateObject();  

        // 添加字段
		
		cJSON_AddNumberToObject(employee_obj, "id", employees[i].id);
    	cJSON_AddStringToObject(employee_obj, "name", employees[i].name);
    	cJSON_AddStringToObject(employee_obj, "password", employees[i].password);
    	cJSON_AddNumberToObject(employee_obj, "age", employees[i].age);
    	cJSON_AddNumberToObject(employee_obj, "salary", employees[i].salary);
    
		cJSON_AddStringToObject(employee_obj, "gender", gender_to_string( p->genders ));//枚举----?
    	cJSON_AddStringToObject(employee_obj, "department", department_to_string(p->departments));//
    	cJSON_AddStringToObject(employee_obj, "title", title_to_string(p->titles));//
    	cJSON_AddStringToObject(employee_obj, "role", role_to_string(p->roles));// 
		
		
		
		// 将Employee对象添加到数组中
        cJSON_AddItemToArray(array, employee_obj);  
    }

	// 数据转成字符串
    char* json_str = cJSON_Print(array);
    cJSON_Delete(array);  // 释放JSON数组内存
    return json_str;  // 需调用者手动 free(json_str)
}
*/

/*
// JSON转Employee结构体数组
Employee* json_to_Employee_array(const char* json_str ,int count) {
	// 解析JSON字符串
    cJSON* root = cJSON_Parse(json_str);  
    if (!root) {
        fprintf(stderr, "JSON解析失败: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    Employee* p = (Employee*)malloc(sizeof(Employee));
    memset(p, 0, sizeof(Employee));

    // 提取字段（需检查字段是否存在且类型正确）
    item = cJSON_GetObjectItem(root, "id");
    if (item && cJSON_IsNumber(item)) {
        p->id = item->valueint;
    }
    
    cJSON* item = cJSON_GetObjectItem(root, "name");
    if (item && cJSON_IsString(item)) {
        strncpy(p->name, item->valuestring, sizeof(p->name) - 1);
    }

     cJSON* item = cJSON_GetObjectItem(root, "password");
    if (item && cJSON_IsString(item)) {
        strncpy(p->password, item->valuestring, sizeof(p->password) - 1);
    } 

    item = cJSON_GetObjectItem(root, "age");
    if (item && cJSON_IsNumber(item)) {
        p->age = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "salary");
    if (item && cJSON_IsNumber(item)) {
        p->salary = item->valuedouble;
    }

    item = cJSON_GetObjectItem(root, "gender");
    if (item && cJSON_IsBool(item)) {
        p->gender = item->valueint;//?
    }
    
    item = cJSON_GetObjectItem(root, "department");
    if (item && cJSON_IsBool(item)) {
        p->department = item->valueint;
    }
    
    item = cJSON_GetObjectItem(root, "title");
    if (item && cJSON_IsBool(item)) {
        p->title = item->valueint;
    }
     
    item = cJSON_GetObjectItem(root, "role");
    if (item && cJSON_IsBool(item)) {
        p->role = item->valueint;
    }
    cJSON_Delete(root);  // 释放JSON对象内存
    return p;  // 需调用者手动 free(p)
}
*/

/*
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
*/
