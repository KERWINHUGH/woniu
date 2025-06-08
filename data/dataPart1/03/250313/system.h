typedef struct User{
    char password[32];  //用户密码
    char realname[32];  //用户姓名
    char phone[16];     //用户电话
    char address[32];   //用户地址
    int  type;          //0为管理员，1为普通用户
    int status;         //0为正常，1为异常
    int lock_status;    //0表示正常，1表示锁定
    int lock_time;      //锁定时间时间戳
}User;

extern char *dir_path = "./users";    //当前登录路径
extern char username[32];    //当前登录用户名
extern int role;        //当前登录用户类型

int login();
int addUser();
void dispalyAllUserInfo();
void dispalyUserInfo();
int deleteUser();
int modifyUserInfo();