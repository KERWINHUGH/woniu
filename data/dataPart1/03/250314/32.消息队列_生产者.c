#include <stdio.h>
#include <unistd.h>   
#include <stdlib.h>
#include <sys/msg.h> 
#include <string.h>

#define MSGKEY 1234L

struct msgbuf{ //消息结构体
    long mtype;
    char mtext[1024];
};

int main(int argc, char *argv[]){
    struct msgbuf msg;
    msg.mtype = 100;
    strcpy(msg.mtext, "aaaaaaaaaaaaaaaaaaa");

    int msgid = msgget(MSGKEY, IPC_CREAT|0666);  // 创建或者获取消息队列
    if(msgid < 0){
        perror("msgget error");
        exit(1);
    }

    // 发送消息到消息队列
    if(msgsnd(msgid, &msg, sizeof(msg.mtext), 0) < 0){
        perror("msgsnd error");
        exit(1);
    }
    
    msg.mtype = 200;
    strcpy(msg.mtext, "bbbbbbbbbbbbbbbbbbbbb");
    if(msgsnd(msgid, &msg, sizeof(msg.mtext), 0) < 0){
        perror("msgsnd error");
        exit(1);
    }
    return 0;

}