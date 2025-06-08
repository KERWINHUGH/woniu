/***************************************************
# File Name:    单链表练习1.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年03月16日 星期日 14时03分13秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <singleList.h>

//创建节点
Node *createNode(User user){
	Node *newNode = malloc(sizeof(user));
	newNode->data = user;
	newNode->next = NULL;
	return newNode;
}

//尾插
Node *addNode(Node *head ,User user){
	Node *tailNode = createNode(user);
	Node *current = head;
	while(current->next != NULL){
		current = current->next;
	}
	current->next =tailNode;
	return tailNode; 
}

//头插和中间插入
Node *insertNode(Node **head, char *acc,User user){
	Node *newNode = createNode(user);
	
	
		//中间插入,找到指定账户
		Node *current = *head;
		Node *prev = NULL;
		while(current->next != NULL && strcmp(current->data.acc, acc)!=0){
			prev = current;//找到指定账户前一个节点
			current = current->next;
		}
		//中间插入,在指定账户之前
		if(strcmp(current->data.acc, acc)==0){
			//头插,在指定账户之前
			if(strcmp((*head)->data.acc,acc) ==0){
				newNode->next = *head;
				*head = newNode;
			}else{
				newNode->next = current;
				prev->next = newNode; 
			}
		}else{
		//尾插,没找到指定账户，插到链表尾部
			addNode(*head,user);
		}
	
	return *head;
}
//删除
Node *delNode(Node **head, char *acc){
	if(head == NULL){
		return NULL;
	}
	
		Node *current = *head;
		Node *prev = NULL;
		while(current->next != NULL && strcmp(current->data.acc,acc) != 0){
			prev = current;
			current = current->next;
		}
		//头删节点
		
		if(strcmp(current->data.acc, acc) == 0){
			if(strcmp((*head)->data.acc,acc) == 0){
				//删除头结点，未释放头结点空间
				*head = (*head)->next; 
			}else{
				prev->next = current->next;	
			}
		}
		free(current);
		current->next =NULL;
	
	return *head;
}
//查找
Node *inquireNode(Node *head,char *acc){
	Node *current = head;
	while(current->next != NULL && strcmp(current->data.acc,acc) !=0){
		current = current->next;
	}
	if(strcmp(current->data.acc,acc) ==0){
		return current;
	}
	return NULL;
}

//修改
Node *modifyNode(Node *head,char *acc,User user){
	if(head == NULL){
		return NULL;
	}
	Node *current =head;
	while(current->next != NULL && strcmp(current->data.acc,acc) != 0){
		current = current->next;
	}
	if(strcmp(current->data.acc,acc) == 0){
		current->data = user;
	}else{
		return NULL;
	}
	return head;
}

//遍历打印
void print(Node *head){
	Node *current =head;
	while(current != NULL){
		printf("账户：%s，姓名：%s，密码：%s，电话：%s，地址：%s。\n",current->data.acc,current->data.name,current->data.pass,current->data.phone,current->data.addr);
		current = current->next;
	}
}
/*
int main(int argc, char *argv[]) {
	User u1 = {"No.01","admin1","1","123456","陕西西安"};
	User u2 = {"No.02","admin2","1","123456","陕西西安"};
	User u3 = {"No.03","admin3","1","123456","陕西西安"};
	User u4 = {"No.04","admin4","1","123456","陕西西安"};
	User u5 = {"No.05","admin5","1","123456","陕西西安"};
	User u6 = {"No.06","admin6","1","123456","陕西西安"};
	User u7 = {"No.07","admin7","1","123456","陕西西安"};
	User u8 = {"No.08","admin8","1","123456","陕西西安"};
	User u9 = {"No.09","admin9","1","123456","陕西西安"};
	Node *head = createNode(u1);
	addNode(head,u2);
	addNode(head,u3);
	addNode(head,u4);
	addNode(head,u5);
	puts("----------------------添加-----------------------");
	print(head);
	puts("----------------------插入-----------------------");
	insertNode(&head,u1.acc,u6);
	insertNode(&head,u3.acc,u7);
	insertNode(&head,"sc",u9);
	print(head);
	puts("----------------------删除-----------------------");
	delNode(&head,u6.acc);
	delNode(&head,u7.acc);
	print(head);
	puts("----------------------查找-----------------------");
	Node *inqu =inquireNode(head,u1.acc);
	
	if(inqu == NULL){
		puts("没找到");
		return 0;
	}else if(strcmp(inqu->data.acc ,u1.acc) ==0){
		puts("找到了");
	} 
	puts("----------------------修改-----------------------");
	modifyNode(head,u2.acc,u8);
	print(head);
	
    return 0;
}
*/

