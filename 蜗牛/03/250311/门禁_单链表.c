#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// 定义结构体，标识链表的节点
typedef struct user {
    char username[20];
    char password[20];
    char realname[20];
    char phone[12]; 
    char address[50];
    int status;   // 状态，0表示正常，1表示异常
    int type;     // 类型，0表示普通用户，1表示管理员
    int lock_status;  // 锁定状态，0表示正常，1表示锁定
    long lock_time;   // 锁定时间，时间戳标识
}User;

typedef struct node {
    User *data;              // 节点数据域
    struct node *next;     // 节点指针域
}Node;

//Node *temp = NULL;

Node *initList(){
    // 初始化链表，添加管理员账号
    Node *node = (Node *)malloc(sizeof(Node));  // 申请内存空间
    User *user = (User *)malloc(sizeof(User));  // 申请内存空间，保存用户信息
    strcpy(user->username, "admin");
    strcpy(user->password, "admin123");
    strcpy(user->realname, "管理员"); 
    strcpy(user->phone, "13512345678");
    strcpy(user->address, "中国");
    user->status = 0;
    user->type = 1;
    user->lock_status = 0;
    user->lock_time = 0;
    node->data = user;
    node->next = NULL;    // 为节点指针域赋值
    return node;
}

Node *searchUser(Node *head, char *username){
    // 查找链表中包含指定数据的节点
    Node *temp = head;
    while(temp != NULL){
        if(strcmp(temp->data->username, username) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void change_node(Node *head, User *old_username, User *new_username){
    // 修改链表中包含指定数据的节点的数据域
    Node *temp = search_node(head, old_username->username);  // 查找包含修改数据的节点
    if(temp == NULL){
        printf("链表中没有找到包含数据%d的节点\n", old_username->username);
        return;
    }
    strcpy(temp->data->username , new_username->username);   // 修改节点数据
}

void printList(Node *head){
    // 打印链表
    Node *temp = head;
    while(temp != NULL){
        printf("%s ", temp->data->username);
        temp = temp->next;
    }
    printf("\n");
}

Node *login(Node *head){
    // 登录功能，登录成功返回用户节点，登录失败返回0
    char username[20],password[20],flag0='1',flag1='0';
    Node *temp;
    int error = 0;   // 记录密码连续错误次数
    while(flag0=='1'){
        printf("请输入用户名：");
        scanf("%s",username);
        temp = searchUser(head,username);
        if(temp == NULL){
            printf("用户名不存在，请重新输入\n");
            printf("继续输入请按1，结束请按其他键: ");
            scanf(" %c",&flag0);
            continue;
        }
        flag0 = '0';
        flag1 = '1';
    }

    while(flag1=='1'){
        printf("请输入密码：");
        scanf("%s",password);
        // 检查密码是否正确
        if(strcmp(password,temp->data->password)==0){
            // 检查状态是否正常，为0
            if(temp->data->status==0){
                // 检查账户是否为锁定状态，如果是继续检查锁定时间是否已达到5分钟
                if(temp->data->lock_status == 1 && temp->data->lock_time + 300 > time(NULL)){
                    printf("账户已被锁定，请稍后再试\n");
                    return temp;
                }
                printf("登录成功\n");
                return temp;
            }else{
                printf("账户状态异常，请联系管理员\n");
                return 0;
            }
        }
        error += 1;
        // 检查连续错误次数是否达到3次，达到则将账号锁定5分钟
        if(error == 3){
            printf("密码连续错误3次，账号锁定5分钟！\n");
            temp->data->lock_status = 1;
            temp->data->lock_time = time(NULL);
            return 0;
        }
        printf("密码错误，请重新输入！\n");
        printf("继续输入请按1，结束请按其他键: ");
        scanf(" %c",&flag1);
        if(flag1 != '1'){
            return 0;
        }
    }
}

int main(){
    Node *head = initList();    // 初始化链表
    printList(head);
    int choice,suc_choice;
    while(1){
        printf("-------欢迎使用用户管理系统----------\n");
        printf("1.登录\n2.注册\n3.退出\n");
        printf("请选择服务: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                Node *temp = login(head);
                printf("1.查询账户信息\n2.修改账户信息\n3.退出账户\n");
                scanf("%d",suc_choice);
                switch(suc_choice){
                    case 1:
                        break;
                    case 2:
                    if(temp != NULL){
                        //修改用户名
                        Node *new = login(head);
                        printf("请输入用户名");
                        sancf(" %s",new->data->username);
                        change_node(head->data, temp->data->username, new->data->username);
                    }
                        break;
                    case 3:
                        break;
                }
                break;
            case 2:
                break;
            case 3:
                return 0;
                break;
            default:
                printf("输入错误，请重新输入！\n");
                break;
        }
    }
    return 0;
}