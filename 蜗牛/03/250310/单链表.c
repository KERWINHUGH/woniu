#include <stdio.h>
#include <stdlib.h>

//定义结构体，标识链表的节点
typedef struct nod{
    int data;           //节点数据域
    struct nod *next;   //节点指针域
}Node;

Node *creat_node(int data){
    //创建并返回一个节点
    Node *node =(Node *)malloc(sizeof(Node));
    node->data =data;   //为节点数据域赋值
    node->next =NULL;   //为节点指针域赋值
    return node;
}

Node *add_node(Node *head,int data,int index){
    //Node *head,链表头指针
    //int data，要插入的数据
    //int index，要插入的位置
    if(index == 1){
        //在链表头部插入新节点----------头插法
        Node *node = ceate_node(data);
        node->next = head;  //将新节点的指针域指向原首元结点
        head = node;
        return head;
    }
    //在链表的中间或者末尾插入新节点
    Node *temp = head;
    //查找链表第idex-1个节点，即插入位置的直接前驱节点
    for(int i=1;i<index-1;i++){
        temp = temp->next;
        if(temp == NULL){
            printf("链表长度不够，无法插入\n");
            return head;
        }
    }
    Node *node = create_node(data); //创建新节点
    node->next = temp->next;    //将新节点的指针域指向直接后继节点，即插入位置处的原节点
    temp->next = node;   //将直接前驱节点的指针指向新节点
    return head;
}

void printf_list(Node *head){
    //打印链表
    Node *temp =head;
    while(temp!=NULL){
        printf("%d ",temp->data);
        temp = temp->next;
    }\
    printf("\n");
}

Node *search_node(Node *head,int data){
    //查找链表中包含指定数据的节点
    if(head==NULL){
        printf("链表为空\n");
        return NULL;
    }
    Node *temp = head;
    while(temp != NULL){
        if(temp->data==data){
            return temp;
        }
        temp = temp->next;
    }
}

void change_node(Node * head,int old_data,int new_data){
    //修改链表中包含指定数据的节点的数据域
    Node *temp = seach_node(head,old_data); //查找包含修改数据的节点
    if(temp == NULL){
        printf("链表中没有找到包含数据%d的节点\n",old_data);
        return;
    }
    temp->data = new_data;  //修改节点数据
}

void free_list(Node *head){
    //释放链表
    Node *temp = head;
    while(temp!=NULL){
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
}

Node *delete_node(Node *head,int data){
    if(search_node(head,data) == NULL){
        printf("链表中没有找到包含数据%d的节点\n",data);
        return head;
    }
    //删除首元结点
    if(head->data ==data){
        Node *temp =head;
        head =head->next;    //将头指针指向原首元结点的下一个节点
        free(temp);         //释放首元结点
        return head;
    }
    //删除中间或者末尾结点
    Node *temp = head;
    //查找包含删除数据节点的直接前驱节点
    while(temp->next !=NULL &&temp->next->data !=data){
        temp=temp->next;
    }
    Node *del =temp->next;
    temp->next =temp->next->next; //将要删除节点的直接前驱指向直接后继
    free(del);
    return head;
}

void recursion(Node *head){
    Node *temp = head;
    if(head == NULL){
        return;
    }
    //函数递归调用
    recursion(temp->next);  // 每次调用时都会传入当前节点的下一个节点
    printf("%d",temp->data);    //在递归结束时开始执行，链表开始从最后一个节点打印
}

int main()
{
    Node *head = NULL;  //定义头指针，并初始化为NULL


}

/*
int main(){
    Node *head =NULL;   //定义头指针，初始化为NULL
    head =creat_node(1);    //创建首元结点，保存数据1；并将头指针指向首元结点
    printf("%d \n",head->data);

    //在首元结点位置插入新节点  -------------------------------头插法
    Node *new_node = creat_node(2); //创建第二个节点
    new_node->next =head;   //  将新节点的指针指向原首元结点
    head = new_node;    //  将头指针指向新节点

    printf("%d\n",head->data);  //输出首元结点的数据域的值
    printf("%d\n",head->next->data);    //输出第二个节点的数据域的值

    //先创建一个新节点指向头指针，然后用循环找到尾结点  ----------尾插法
    Node *temp = head;
    while(temp->next !=NULL){
        temp=temp->next;
    }
    printf("最后一个节点的数据为：%d \n",temp->next);
    new_node = creat_node(3);   //创建新节点，保存数据3
    temp->next =new_node;   //将最后一个节点的指针域指向新节点

    //目前链表中有3个节点，分别保存的数据是2,1,3    ----------在指定位置插入
    //现在需要在第3个节点的位置插入新节点，新节点保存的数据是4
    //先要找到第3个节点的直接前驱节点
    Node *prior = head;
    int i=0;
    for(i=0;i<2;i++){
        prior =prior->next;
    }
    printf("%d \n",prior->data);
    new_node = creat_node(4);
    new_node->next =prior->next;    //将新节点的指针域指向第3个节点
    prior->next =new_node->next;    //将直接前驱节点的指针域指向新节点
    return 0;
}
*/