#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
文件students.txt内容如下，每一行保存了学生的语文、数学、英语成绩，现要求计算出每个学生的总成绩，
并且按总成绩从高到低排序，并输出到文件students_sort.txt中（第1行为列名：序号，姓名，语文，数学，英语，总成绩）。
1   张三        87      89      90
2   李四        88      89      90
3   王五        76      78      79
4   赵六        45      67      66
5   孙七        78      77      88
*/
struct student{
    char name[20];
    int chinese;
    int math;
    int english;
    int total;
};

int main(){
    struct student stu[5];   // 结构体数组，保存每个学生的信息
    FILE *fp = fopen("students.txt", "r");
    if(fp == NULL){
        perror("打开文件失败");
        exit(1);
    }
    char name[20];
    int id, chinese, math, english, total, index = 0;
    // 读取到文件中的每一行数据，将姓名、语文、数学、英语成绩，保存到变量中计算后再将所有信息（包括总分）保存到结构体数组中
    while(fscanf(fp, "%d %s %d %d %d", &id, name, &chinese, &math, &english) != EOF){
        total = chinese + math + english; // 计算总分
        strcpy(stu[index].name, name);
        stu[index].chinese = chinese;
        stu[index].math = math;
        stu[index].english = english;
        stu[index].total = total;
        index++;
    }

    // 对结构体数组元素根据总分从高到低排序（冒泡排序）
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5 - i; j++){
            if(stu[j].total < stu[j + 1].total){
                struct student temp = stu[j];
                stu[j] = stu[j + 1];
                stu[j + 1] = temp;
            }
        }
    }
    // 将排序后的内容写入到文件
    FILE *fp1 = fopen("students_sort.txt", "w");
    // 写入第一行，：序号，姓名，语文，数学，英语，总成绩
    fprintf(fp1, "序号\t姓名\t\t语文\t数学\t英语\t总成绩\n");
    for(int i = 0; i < 5; i++){
        fprintf(fp1, "%d\t\t%s\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, stu[i].name, stu[i].chinese, stu[i].math, stu[i].english, stu[i].total);
    }

    fclose(fp);
    fclose(fp1);
    return 0;
    
}