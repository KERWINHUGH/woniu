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
    int msgid = msgget(MSGKEY, IPC_CREAT|0666);  // 创建或者获取消息队列
    if(msgid < 0){
        perror("msgget error");
        exit(1);
    }

    // 从队列中获取消息
    if(msgrcv(msgid, &msg, sizeof(msg.mtext), 200, 0) < 0){
        perror("msgrcv error");
        exit(1);
    }
    printf("receive message: %s\n", msg.mtext);

    // 删除队列
    struct msqid_ds buf;
    if(msgctl(msgid, IPC_RMID, &buf) < 0){
        perror("msgctl error");
        exit(1);
    }
    printf("队列中的消息数量: %ld\n", buf.msg_qnum);

    return 0;
}