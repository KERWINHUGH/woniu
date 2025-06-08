/***************************************************
# File Name:    74-线程初识.c
# Author:       SuperYu
# Mail:         yujian001002@163.com.com
# Created Time: Mon 17 Mar 2025 10:56:00 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>   // sleep

int num = 100;

// 写一个线程函数，来卖票。
void* sale(void* args){
	char *name = (char*)args;
	
	int count = 0;

	while(true){
		if(num > 0){
			usleep(100000); // 模拟卖票需要的时间。
			
			num--; // 模拟卖1张票。
			
			count++; // 代表卖了几张票，
			
			printf("窗口：%s ,卖第%d张票，还余票：%d 张。\n" , name, count, num );
			
		}else {
			// 如果没有票了，就不卖了。
			break;		
		}
	}
	printf("%s窗口一共卖了%d张票。\n", name, count);
	return NULL;
}





int main(int argc, char *argv[]) {
	
	pthread_t one, two, three ;
	

	// 12306
	if(pthread_create( &one , NULL, sale , "12306" ) != 0 ){
		perror("线程创建失败!");
		return 1;
	}
	// 美团
	if(pthread_create( &two , NULL, sale , "美团抢票" ) != 0 ){
		perror("线程创建失败!");
		return 1;
	}
	// 拼多多
	if(pthread_create( &three , NULL, sale , "拼多多抢票" ) != 0 ){
		perror("线程创建失败!");
		return 1;
	}
	
	
	// 等待线程结束
	pthread_join(one, NULL);
	pthread_join(two, NULL);
	pthread_join(three, NULL);
	
	printf("最后的票数是：%d \n", num );
	
	puts("----end----");

    return 0;
}





