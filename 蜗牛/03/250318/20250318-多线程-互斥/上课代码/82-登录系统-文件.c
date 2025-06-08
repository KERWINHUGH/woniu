/***************************************************
# File Name:    84-登录系统-文件.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: 2024年11月06日 星期三 17时35分58秒
****************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>


#define BUFFER_SIZE 1024
// 初始的数组的长度：
int size = 10;
 
typedef struct User {
	char userName[32];
	char password[32];
	int age;
	char gender[32];
	// 代表登录的时间
	char *loginTime;
	//　状态：0 正常状态，　１：锁定状态　　２：删除状态
	int status;	
}User;

// 日志结构体
typedef struct Log{
	char userName[32];
	char operation[32];
	char currentTime[32];
}Log;


// 模拟数据库里面已经存有的用户信息．
User *users;
// 用户信息存放的文件
char *filename = "User.txt";
char *logname = "log.txt";


// 初始化存数据的数组（从文件读取数据，再写入到users数组中）
void init();
// 把用户数据，写入到文件中
void addUserToFile(char *userInfo);
// 根据用户名，找到数据的索引 
int findUserIndex(char name[]);
// 根据用户名和密码找到用户的位置　
int findIndexByUserName(char name[] , char password[] );
// 根据用户名，删除数据
int delUserByName(char name[]);
// 登录的函数：根据用户找到数据所在的索引：
int findIndexByUserName(char name[] , char password[] );
// 找到可以插入数据的索引处．
int findInsertIndex();
// 得到当前时间
char* getTime();
// 用来记录用户相关的操作日志（登录\增加\删除等操作）
void* recordLog(void* args){
	puts("---多线程执行日志添加---");

	Log *log = (Log*)args;
	// 1:
	FILE *fp = fopen(logname, "a+");
	// 2: 写入一行数据：
	char info[256]={0}; // "日志记录 => 用户：，操作：，时间：\n";
	
	// 按指定格式，拼接字符串
	sprintf(info,"日志记录 => 用户：%s ,  时间：%s  ,  操作：%s　\n", log->userName, log->currentTime, log->operation);

	printf("日志信息:%s", info);

	fputs( info , fp );

	// 3:
	fclose(fp);
}


// -----------------------------------------------------------------------------
int main() {
	//recordLog(log);

	// 一开始就应该初始化数组;
	init();

	
	int op ;
	while(true){
		char tempName[32]={0};
		char tempPass[32]={0};
		int tempAge;
		char tempGender[32]={0};
		puts("请选择操作：1．登录　2．注册　3．退出");
		scanf("%d",&op);
		if(op == 1){
			puts("请输入用户名:");
			scanf("%s", tempName);
			puts("请输入密码:");
			scanf("%s", tempPass);
			// 得到登录数据的索引
			int loginIndex = findIndexByUserName(tempName, tempPass);
			// 根据　loginIndex 变量，来判断是否已经登录成功
			if(loginIndex != -1){
				int op2;
				// 得到当前时间
				char *loginTime = getTime();
				// 得到上次的登录时间
				char *lastTime = users[loginIndex].loginTime;
				if(lastTime == NULL){
					printf("您是第一次登录！\n");
				}else {
					printf("您上次登录时间是：%s \n", lastTime);
				}
				// 把当前的登录时间，更新进上次登录时间
				users[loginIndex].loginTime = loginTime;
				puts("登录成功");
				
				// 记录登录日志：
				Log log = {0};
				strcpy(log.userName, tempName);				
				strcpy(log.currentTime, loginTime);				
				strcpy(log.operation, "login");				


				//recordLog(log);
				// 我们应该通过多线程去执行，添加日志的操作。
				pthread_t pid ;
				if(pthread_create( &pid , NULL, recordLog , &log ) != 0 ){
					perror("线程创建失败!");
					return 1;
				}


				bool ff = true;
				while(ff){
					printf("f的值是：%d \n", ff);
				puts("请选择：１：显示用户信息，２：显示所有用户，３：修改密码， 4:删除用户，5：返回上一级");
					scanf("%d",&op2);
					switch(op2){
						case 1:
							puts("---- 当前用户信息： ----");

							printf("姓名：%s，密码：%s，年龄：%d，性别：%s \n",
				users[loginIndex].userName, users[loginIndex].password, users[loginIndex].age, users[loginIndex].gender);
							break;
						case 2:
							puts("----　显示所有用户信息 ----");
							for(int i = 0; i < size; i++){
								if(users[i].age != 0 && strcmp(users[i].userName,"")!=0){
									printf("姓名：%s，密码：%s，年龄：%d，性别：%s \n",
										users[i].userName, users[i].password, users[i].age, users[i].gender);
								}
							}		
							break;
						case 3:
							puts("----　修改密码 ----");
							break;

						case 4:
							puts("请输入要删除的用户名:");
							scanf("%s", tempName);						
							int f = delUserByName(tempName);
							if(f>0){
								puts("恭喜，删除用户成功！");
							}else if(f==0){
								puts("对不起，删除失败！");
							}else {
								puts("对不起，用户名不存在！");
							}
							break;
						case 5:
							ff = 0;
							puts("----　返回上一级 ----");
							break;
						default:
							puts("----　请正确输入操作　----");
							break;
					}
				}
			}else {
				puts("用户名或密码错误！请重新输入.");
			}
		}else if(op == 2){
			puts("请输入新用户名:");
			scanf(" %s", tempName);
			// 应该检测新的用户名是否已经被使用．
			int f = findUserIndex(tempName);

			if(f == -1 ){
				puts("请输入新密码:");
				scanf(" %s", tempPass);
				puts("请输入新年龄:");
				scanf(" %d", &tempAge);
				puts("请输入性别:");
				scanf(" %s", tempGender);
				// 找可以插入数据的位置　
				int insertIndex = findInsertIndex();

				if(insertIndex >= 0){
					// 写入数据
					User temp;
					strcpy(temp.userName, tempName);
					strcpy(temp.password, tempPass);
					strcpy(temp.gender, tempGender);
					temp.age = tempAge;

					users[insertIndex] = temp;
				}else {
					int oldSize = size;
					// 否则就是没有了位置，需要扩容　					
					size = size * 2;					
					users = realloc(users, size * sizeof(User));

					if(users == NULL){
						printf( "扩容失败!" );
						return 1;
					}
						
					// 初始化新扩展的部分
					memset(users + oldSize, 0, (size - oldSize) * sizeof(User));

					// 写入数据
					User temp;
					strcpy(temp.userName, tempName);
					strcpy(temp.password, tempPass);
					strcpy(temp.gender, tempGender);
					temp.age = tempAge;

					users[size/2] = temp;

				}
					// 同时，还要把数据写到User.txt里面
					// 用户信息格式：userName-password/n
					char userInfo[64] = "";
								
					strcat(userInfo, tempName);
					strcat(userInfo, "-");
					strcat(userInfo, tempPass);
					strcat(userInfo, "\n");
					printf("新用户信息：%s", userInfo);
					// 写入到文件
					addUserToFile(userInfo);
			}else {
				puts("对不起，用户已经存在，请换一个.");
			}

		}else if(op == 3){
			break;
		}else {
			puts("对不起，请正确输入选项！");
		}
	}
	//　释放内存
	free(users);
	puts("-----end-----");
    return 0;
}
// ---------------------------------------------------------------
// 初始化存数据的数组（从文件读取数据，再写入到users数组中）
void init(){
	users = malloc( size * sizeof(User));
	// 将分配的内存置零,初始化
	memset(users, 0, size * sizeof(User)); 

	int readBytes = 0;
	char *username;
	char *password;
	char buffer[BUFFER_SIZE];
	char line[128];

	// 1:
	int fd = open(filename, O_RDONLY);
	if (fd < 0 ) {  
        perror("Failed to open file");  
        exit(EXIT_FAILURE);  
    }
	// 2: 一次性读取所有用户信息进来．
	if( ( readBytes = read( fd, buffer, BUFFER_SIZE ) )>0 ){
		// 确保缓冲区是以 '\0' 结束的字符串
		if (readBytes > 0) {
    		buffer[readBytes] = '\0';
		}

		char *line_ptr = buffer;
		// 用来判断当前的用户信息，写入到User结构体的哪个位置．
		int index = 0;
		while(*line_ptr){
			int i = 0;
			// 读取一行内容到line中
			// 从buffer中逐字符读取，直到遇到换行符\n或字符串结尾，
			while(*line_ptr && *line_ptr != '\n'){
				line[i++] = *line_ptr++;
			}
			// 手动补上 '\0'
			line[i] = '\0';
			if(*line_ptr){
				// 跳过换行符
				line_ptr++;
			}
			// 数组越界判断
			if (index >= size) {
				fprintf(stderr, "数据超过数组大小，停止读取\n");
				// 如果执行到这里，说明数组的容量不够，我们需要进行扩容．．．．
				// .......
			}

			// 得到用户名得密码：
			username = strtok(line, "-");
			password = strtok(NULL, "-");
			User temp = {0};
			strcpy(temp.userName, username);
			strcpy(temp.password, password);
			users[index] = temp;
			index ++;
		}
	}
	// 3:
	close(fd);
}
// 登录的函数：根据用户找到数据所在的索引：
int findIndexByUserName(char name[] , char password[] ){

	for(int i = 0; i < size; i++){
		if(strcmp(users[i].userName , name ) == 0 && strcmp(users[i].password , password) == 0){
			return i;
		}
	}
	return -1;
}
// 找到可以插入数据的位置 -----
int findInsertIndex(){

	int insertIndex = -1;

	for(int i = 0; i< size ; i++){
		if(strlen(users[i].userName) == 0){     // 通过字符串的长度来判断是否有数据
			insertIndex = i;
			break;
		}
	}
	return insertIndex ;
}
// 我们发现，删除用户时，本质就是根据用户找到数据在位置，再删除．
int findUserIndex(char name[]){

	for(int i = 0; i< size; i++){
		if(strcmp(users[i].userName, name) == 0 ){
			return i;
		}
	}
	return -1;
}

/*
	返回：１　代表删除成功
	返回：０　代表删除失败
	返回：-1　代表用户名不存在
*/
int delUserByName(char name[]){
	int index = findUserIndex(name);
	if(index == -1){
		return -1;
	}
	// 删除数据（把这个位置的数据置空）
	users[index].age = 0;
	strcpy(users[index].userName, ""); 
	strcpy(users[index].password, ""); 
	strcpy(users[index].gender, ""); 
	return 1;
}
// 得到当前的时间
char* getTime(){
	// １：存时间的字符串
	int length = 64;
	char *timeStr = malloc(length * sizeof(char));
	if(timeStr == NULL){
		fprintf(stderr, "内存分配失败!");
		exit(EXIT_FAILURE); // 退出程序	
	}
	// ２：得到时间
	time_t t = time(NULL);
	struct tm *now = localtime(&t);
	//printf("长度是：%ld \n", sizeof(timeStr));
	// 3: 格式化时间（把时间变成我们习惯的格式）
	strftime( timeStr, length, "%Y年%m月%d日  %H:%M:%S", now );
	return timeStr;
}

// 把用户数据，写入到文件中
void addUserToFile(char *userInfo){
	// １：打开一个文件：（写入方式打开）
	int fd = open(filename, O_WRONLY );
	if(fd < 0){
		perror("文件打开失败!");
	}
	// 新增的数据，是尾部追加
	off_t offset =  lseek(fd, 0, SEEK_END);
	// ２：使用api
	ssize_t length = write(fd, userInfo, strlen(userInfo));
	printf("数据写入完成．写入%ld个字节．\n",length);
	// 3: 关闭打开的文件：
	close(fd);
}
















