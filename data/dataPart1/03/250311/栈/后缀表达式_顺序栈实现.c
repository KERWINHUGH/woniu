#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// (3+4)*5 -> 34+5*
// 遍历字符串，当前字符为数字，则入栈，当前字符为运算符，则出栈两个数字，运算，入栈结果，
// 当遍历完字符串后，栈顶元素即为最终结果

#define MAXSIZE 5

int top = -1;

int push(int *stack, int data){
    // int *stack，顺序栈
    // int data，要入栈的数据
    // 检查栈是否已满
    if(top == MAXSIZE - 1){
        printf("栈已满\n");
        return top;
    }
    printf("入栈元素：%d\n", data);
    stack[++top] = data;  // 入栈，栈顶指针加1，栈顶元素赋值
    return data;
}

int pop(int *stack){
    // 检查栈是否为空
    if(top == -1){
        printf("栈为空\n");
        return 0;
    }
    return stack[top--];
}

void getResult(int *stack, char *exp){
    int len = strlen(exp);    // 获取表达式长度
    int num1,num2;
    for(int i = 0; i < len; i++){
        // isdigit()，检查指定的字符是否为数字
        if(isdigit(exp[i])){
            // exp[i] - '0'，将数字字符转换为对应的整数
            push(stack, exp[i]-'0');
        }else{
            // 不是数字，则出栈2个数字，进行运算，再将运算结果入栈
            num1 = pop(stack);
            num2 = pop(stack);
            switch(exp[i]){
                case '+':
                    push(stack, num2 + num1);
                    break;
                case '-':
                    push(stack, num2 - num1);
                    break;
                case '*':
                    push(stack, num2 * num1);
                    break;
                case '/':
                    push(stack, num2 / num1);
                    break;
            }
        }
    }
    printf("%s的计算结果为: %d\n", exp, stack[top]);
}

int main(){
    char exp[] = "34+5*";   // 后缀表达式
    int stack[MAXSIZE];
    getResult(stack, exp);
}