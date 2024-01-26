#include <stdio.h>

int main (void){

    printf("What is your name? ");
    char name[50];
    scanf("%50s", name);
    printf("Hello, %s!\n", name);
    return 0;

}