#include <stdio.h>
#include <stdlib.h>

int main(){
    char name[20], buffer[100];
    printf("Enter your name: ");
    scanf("%s", name);
    snprintf(buffer, sizeof(buffer), "grep '%s' ./students.txt", name);
    system(buffer);
    return 0;
}