/***************************************************
# File Name:    单链表练习.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Sat 15 Mar 2025 10:13:11 AM CST
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/*
*单链表实现门禁系统（动态数组（顺序表）效果）
*1.定义结构体
*2.依次完成增删改查函数以及其他函数，如打印等
*3.可选择使用自定义头文件
*4.测试
**/

typedef struct User{
	char account[32];
	char username[32];
	char password[32];
	char phone[16];
	char address[128];
}User;

typedef struct Node{
	User userdata;
	struct Node *next;
}Node;

void printNode(Node *head);
Node *createNode(User userdata);
Node *addNode(Node *head,User data);
Node *insertNode(Node **head,char *user,User userdata);
Node *inquireNode(Node *head,char *account);
int delNode(Node **head,char *account);
Node *modifyNode(Node *head,char *oldccount,User newUser);

//创建
Node *createNode(User userdata){
	Node *newnode = malloc(sizeof(Node));
	newnode->userdata = userdata;
	newnode->next = NULL;
}
//增加节点------尾差法
Node *addNode(Node *head,User userdata){
	if(head == NULL){
		return NULL;
	}
	Node *newNode = createNode(userdata);
	Node *current = head;
	while(current->next != NULL){//找到链表尾部
		current = current->next;
	}
	current->next = newNode;//新节点放到链表最末尾

	return newNode;
}

//增加节点，头插法，中间插入
Node *insertNode(Node **head,char *account,User userdata){
	if(head == NULL){
		return NULL;
	}
	Node *newNode = createNode(userdata);
	Node *current = *head;
	Node *prev =NULL;
	if(strcmp((*head)->userdata.account ,account)==0){
		newNode->next = *head;
		*head = newNode;
	}else{
		while(current->next!=NULL && strcmp(current->userdata.account,account)!=0){
			prev = current;
			current = current->next;
		}
		if(strcmp(current->userdata.account,account)==0){
			newNode->next = current;//新节点放在当前节点之前
			prev->next =newNode;//当前节点的前一个节点指向新节点
		}else{
			//puts("insert erorr");
			addNode(*head,userdata);
		}
	}
}

//删除
int delNode(Node **head,char *account){
/*
	Node *delnode = inquireNode(head,userdata.account);
	if( delNode== NULL){
		puts("删除的用户不存在！");
		return -1;
	}
*/	
	Node *current = *head;
	Node *prev = NULL;
	while(current->next != NULL && strcmp(current->userdata.account,account)!=0){
		prev =current;
		current =current->next;
	}
	if(strcmp(current->userdata.account,account)==0){
	/*
		strcpy(current->userdata.account,"");
		strcpy(current->userdata.username,"");
		strcpy(current->userdata.password,"");
		strcpy(current->userdata.phone,"");
		strcpy(current->userdata.address,"");
		*/
		if(strcmp((*head)->userdata.account,account) == 0){
			*head = (*head)->next;
		}else{		
			prev->next = current->next;
		}
	}
	
	free(current); 
	current = NULL;
	
	return 0;
}

//查询
Node *inquireNode(Node *head,char *account){
	Node *current = head;
	while(current->next != NULL ){
		if(strcmp(current->userdata.account,account)==0){
			return current;
		}
		current = current->next;
	}
	return NULL;
	
}
//修改
Node *modifyNode(Node *head,char *oldccount,User newUser){
	Node *current = head;
	while(current->next != NULL && strcmp(current->userdata.account,oldccount)!=0){
		current = current->next;
	}
	if(strcmp(current->userdata.account,oldccount)==0){
			current->userdata = newUser;
			return current;
	}
	return NULL;
}
//打印
void printNode(Node *head){

	Node *print = head;
	while(print != NULL ){
		User *u = &print->userdata;
		printf("账户为：%s,用户名为：%s,用户密码为：%s，手机号为：%s，地址为：%s\n",print->userdata.account,print->userdata.username,print->userdata.password,print->userdata.phone,print->userdata.address);
		print = print->next;
	}
}

int main(int argc, char *argv[]) {

	User u1 ={"No.001","admin1","admin123","+8610011012013","湖北武汉"};
	User u2 ={"No.002","admin2","admin123","+8610011012013","湖北武汉"};
	User u3 ={"No.003","admin3","admin123","+8610011012013","湖北武汉"};
	User u4 ={"No.004","admin4","admin123","+8610011012013","湖北武汉"};
	User u5 ={"No.005","admin5","admin123","+8610011012013","湖北武汉"};
	User u6 ={"No.006","admin5","admin123","+8610011012013","湖北武汉"};
	User u7 ={"No.007","admin5","admin123","+8610011012013","湖北武汉"};
	Node *head = createNode(u1);
	
	addNode(head,u2);
	addNode(head,u3);
	addNode(head,u4);
	addNode(head,u5);
	puts("-------------------------添加-------------------------------------");
	printNode(head);
	
	
	insertNode(&head,u2.account,u7);
	puts("-------------------------charu-------------------------------------");
	printNode(head);
	
	
	delNode(&head,"No.001");
	puts("-------------------------删除-------------------------------------");
	printNode(head);
	
	modifyNode(head,u2.account,u6);
	puts("-------------------------修改-------------------------------------");
	printNode(head);
	
	puts("-------------------------查找-------------------------------------");
	Node *print =inquireNode(head,"No.008");
	if(print!=NULL){
		printf("账户为：%s,用户名为：%s,用户密码为：%s，手机号为：%s，地址为：%s\n",print->userdata.account,print->userdata.username,print->userdata.password,print->userdata.phone,print->userdata.address);	
	}else{
		puts("未查到该账户");	
	}
	
    return 0;
}


