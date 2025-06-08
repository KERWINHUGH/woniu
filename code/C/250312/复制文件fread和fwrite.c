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
 
int main(int argc, char *argv[]) {

//使用多个函数将文件整个复制
	FILE *fp = fopen("student.txt","r");
	FILE *fp1 = fopen("new.tex","w");
	if(fp==NULL){
		perror("打开文件失败");
		exit(1);
	}
	fseek(fp,0,SEEK_END);
	long filsesize=ftell(fp);
	rewind(fp);
	char buffer[filsesize];
	fread(buffer,1,sizeof(buffer),fp);
	fwrite(buffer,1,sizeof(buffer),fp1);
	fclose(fp);
	fclose(fp1);

/*
//获取文件的字节数，命令行可以使用统计命令wc实现
	FILE *fp = fopen("student.txt","r");
	if(fp==NULL){
		perror("打开文件失败");
		exit(1);
	}
	printf("fseek前：%c\n",fgetc(fp));
	fseek(fp,-2,SEEK_END);
	printf("fseek后：%c\n",fgetc(fp));
	
	fseek(fp,0,SEEK_END);
	long filesize = ftell(fp);
	printf("文件长度为:%ld\n",filesize);
	fclose(fp);
*/
/*
//使用fgets逐行输出复制
	FILE *fp1 = fopen("student.txt","r");
	FILE *fp2 = fopen("new.tex","w");
	if((fp1==NULL)||(fp2==NULL)){
		perror("打开文件失败");
		return -1;
	}
	char buffer[100];
	
	while(fgets(buffer,sizeof(buffer),fp1)!=NULL){
		fputs(buffer,fp2);
	}
*/

    return 0;
}
