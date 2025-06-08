/***************************************************
# File Name:    1.两数之和.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: 2025年04月06日 星期日 16时57分39秒
****************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


struct ListNode {
      int val;
      struct ListNode *next;
};
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) ;
struct ListNode* createNode(int val);
struct ListNode* addNode(struct ListNode *head, int val);

struct ListNode* createNode(int val){
	struct ListNode* newNode = malloc(sizeof(struct ListNode*));
	newNode->val = val;
	newNode->next = NULL;
	return newNode;
}
struct ListNode* addNode(struct ListNode *head, int val){
	if(head == NULL){
		return NULL;
	}
	struct ListNode *cur = head;
	while(cur->next != NULL){
		cur = cur->next;
	}
	struct ListNode* newNode = createNode(val);
	cur->next = newNode;
	return head;
}

int main(int argc, char *argv[]) {
	struct ListNode *l1 = createNode(2);
	addNode(l1,4);
	addNode(l1,3);
	struct ListNode *l2 = createNode(5);
	addNode(l2,6);
	addNode(l2,4);
	struct ListNode *rp = addTwoNumbers(l1, l2);
	while(rp ->next != NULL)
	{
		printf("%d",rp->val);
		rp = rp->next;
	}
	printf("\n");
	free(rp);
	return 0;
}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    if(l1 == NULL || l2 == NULL)
    {
        return NULL;
    }
    struct ListNode* cur = l1;
    int i = 0,x = 1;  //求出链表节点数
    int sumL1 = 0;
    while(cur->next != NULL)
    {
        sumL1 = cur->val * x;
         x *= 10;
        cur = cur->next;
        i++;
    }
    cur = l2;
    int j = 0,y = 1;  //求出链表节点数
    int sumL2 = 0;
    while(cur->next != NULL)
    {
        sumL2 = cur->val * y;
        y *= 10;
        cur = cur->next;
        j++;
    }
    int sum = sumL1 + sumL2;
    int k = i > j ? i :j;
    //判断和是否进位
	if(k==0)
		printf("k=0\n");
    if(sum / k == 0)
    {
        k++;
    }
    struct ListNode *returnNode = malloc(sizeof(struct ListNode) * k);
    memset(returnNode , 0, sizeof(struct ListNode) * k );
    struct ListNode *newHead = returnNode;
    int a = 10;
    int b = 1;
    int d = k;
    while(k != 0)
    {
         a *= 10;
         b *= 10;
         k--;
    }
    /*
    for(int z = 0; z < d; z++, a /= 10, b /= 10)
    {
        int num = sum % a / b;
        cur->val = num;
        cur = cur->next;
    }
    */
    while(cur->next != NULL)
    {
        int num = sum % a / b;
        returnNode->val = num;
        a /= 10;
        b /= 10;
        returnNode = returnNode->next;
    }
    return newHead;
}
