/***************************************************
# File Name:    蜗牛门禁.c
# Author:       ZhuDongdong
# Mail:         1660397971@qq.com.
# Created Time: Tue 11 Mar 2025 11:09:19 AM CST
****************************************************/

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

Node *initList();
Node *add_User(Node *head);
void del_User(Node *head);
Node *searchUser(Node *head, char *username);
void change_node(Node *head, Node *old, int choice);
void printList(Node *head);
Node *login(Node *head);
Node *login(Node *head);
void login_sec_menu( Node *head,Node *user);


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

Node *add_User(Node *head){
    
        // 新增用户信息
        Node *newUser = (Node *)malloc(sizeof(Node));  // 申请内存空间
        printf("请输入用户名：");
        scanf("%s",newUser->data->username);

        if( searchUser(head,newUser->data->username)!=NULL){
            printf("用户已存在");
            return NULL;
        }
        
		newUser = head;
        printf("请输入密码:");
        scanf("%s",newUser->data->password);

        strcpy(newUser->data->realname, "普通用户"); 

        printf("请输入手机号：");
        scanf("%s",newUser->data->phone);

        printf("请输入地址：");
        scanf("%s",newUser->data->address);

        newUser->data->status = 0;
        newUser->data->type = 0;
        newUser->data->lock_status = 0;
        newUser->data->lock_time = 0;

        newUser->next = head;    // 为节点指针域赋值
        head =newUser;
        return head;
}

void del_User(Node *head){
    Node *delUser = (Node *)malloc(sizeof(Node));  // 申请内存空间
    printf("请输入用户名");
    scanf("%s",delUser->data->username);
    if( searchUser(head,delUser->data->username)==NULL){
        printf("用户不存在");
        return;
    }
    strcpy(delUser->data->username, " ");
    strcpy(delUser->data->password, " ");
    strcpy(delUser->data->realname, " "); 
    strcpy(delUser->data->phone, " ");
    strcpy(delUser->data->address, " ");
    delUser->data->status = 0;
    delUser->data->type = 0;
    delUser->data->lock_status = 0;
    delUser->data->lock_time = 0;
    delUser->next = NULL;    // 为节点指针域赋值
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

void change_node(Node *head, Node *old, int choice){
    char newname[32],password[32],phone[32],adrress[32];
    //管理员修改指定账户信息
    if(old->data->type==1){
        printf("请输入想要修改的用户名");
        scanf("%s",newname);
        // 修改链表中包含指定数据的节点的数据域
        Node *temp = searchUser(head, newname);  // 查找包含修改数据的节点
        if(temp == NULL){
            printf("链表中没有找到包含数据%s的节点\n", newname);
            return;
        }
        if(choice=5){
            //修改指定账户密码
            printf("请输入想要修改的密码");
            scanf("%s",password);
            strcpy(temp->data->username ,password);   // 修改节点数据
        }else if(choice=5){
            //修改指定账户手机号
            printf("请输入想要修改的手机号");
            scanf("%s",phone);
            strcpy(temp->data->username ,phone);   // 修改节点数据
        }else if(choice=7){
            //修改指定账户地址
            printf("请输入想要修改的地址");
            scanf("%s",adrress);
            strcpy(temp->data->username ,adrress);   // 修改节点数据
        }
    //普通用户修改个人账户信息
    }else if(old->data->type==0){
        if(choice=2){
            //修改个人账户密码
            printf("请输入想要修改的密码");
            scanf("%s",password);
            strcpy(old->data->username ,password);   // 修改节点数据
        }else if(choice=3){
            //修改个人账户手机号
            printf("请输入想要修改的手机号");
            scanf("%s",phone);
            strcpy(old->data->username ,phone);   // 修改节点数据
        }else if(choice=4){
            //修改个人账户地址
            printf("请输入想要修改的地址");
            scanf("%s",adrress);
            strcpy(old->data->username ,adrress);   // 修改节点数据
        }
    }
}

void printList(Node *head){
    // 打印链表
    Node *temp = head;
    while(temp != NULL){
        printf("账户名：%s,账户密码：%s，账户类型：%d, 手机号：%s，地址：%s,账户状态：%d,锁定状态：%d,锁定时间：%ld", temp->data->username,temp->data->password,temp->data->type,temp->data->phone,temp->data->address,temp->data->status,temp->data->lock_status,temp->data->lock_time);
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

//二级菜单界面
void login_sec_menu( Node *head,Node *user){
    if(user==NULL){
        return ;
    }
    int choice;
    //普通用户登录
    if(user->data->type==0){
        printf("1.查询个人信息\n2.修改密码\n3.修改手机号\n4.修改地址\n5.退出账户\n");
        printf("请选择服务: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:searchUser(head,user->data->username);break;//查询指定用户信息
            case 2:change_node(head, user,choice); break;//修改用户密码
            case 3:change_node(head, user,choice); break;//修改用户手机号
            case 4:change_node(head, user,choice); break;//修改用户地址
            case 5: break;//退出二级菜单
        }
    }//管理员用户登录
    else if(user->data->type==1){
        printf("1.查询所有账户信息\n2.查询指定账户信息\n3.删除账户\n4.添加账户\n5.修改密码\n6.修改手机号\n7.修改地址\n8.退出账户\n");
        printf("请选择服务: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:printList(head);break;//查询所有用户信息
            case 2:searchUser(head,user->data->username);break;//查询指定用户信息
            case 3:del_User(head);break;//删除用户
            case 4:{Node *newUser = add_User(head);break;}//添加用户
            case 5:change_node(head, user,choice); break;//修改用户密码
            case 6:change_node(head, user,choice); break;//修改用户手机号
            case 7:change_node(head, user,choice); break;//修改用户地址
            case 8:break;//退出二级菜单
        }
    }
}


int main(){
    Node *head = initList();    // 初始化链表
    //printList(head);
    int choice;
    while(1){
        printf("-------欢迎使用用户管理系统----------\n");
        printf("1.登录\n2.注册\n3.退出\n");
        printf("请选择服务: ");
        scanf("%d",&choice);
        switch(choice){
            case 1://用户登录
                {Node *user = login(head);
                login_sec_menu(head,user);          
                break;}
            case 2:{Node *newUser = add_User(head);break;}//用户注册
            case 3:return 0;//退出系统
            default:printf("输入错误，请重新输入！\n");break;
        }
    }
    return 0;
}