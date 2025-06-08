/***************************************************
# File Name:    IO.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Wed 12 Mar 2025 09:29:46 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>


#include <string.h>
#include <stdlib.h>
 
 /*
文件students.txt内容如下，要求读取每个学生的信息，并输出
1   张三    289
2   李四    234
3   王五    123
4   赵六    456
5   孙七    789
*/

int main(int argc, char *argv[]) {

	FILE *fp = fopen("./student.c","r");
		if(fp == NULL){
			perror("打开文件失败");
			return -1;
	}
	char name[20];
	int id,score;
	while(fscanf(fp,"%d %s %d",&id,name,&score)!=EOF){
		printf("姓名：%s,id：%d，总分：%d\n",name,id,score);
	}
	fclose(fp);
	
/*
	FILE *fp = fopen("./student.c","r");
	if(fp == NULL){
		perror("打开文件失败");
		return -1;
	}
	char buffer[1024];
	// fgets(buffer, sizeof(buffer), fp);  // 从fp文件中读取一行内容到buffer中，每调用1次光标会往下移动一行
    // printf("%s\n", buffer);
    // fgets(buffer, sizeof(buffer), fp);  
    // printf("%s\n", buffer);
    // 循环读取文件全部内容
    while(fgets(buffer,sizeof(buffer),fp)!=NULL){
    	printf("%s",buffer);
    }
	fclose(fp);
	*/

    return 0;
}
