#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int num;

    printf("Input a integer: ");
    scanf("%d", &num);

    if(num <= 0){
        printf("Input must be a positive number!\n");
        exit(1);
    }

    pid_t pid = fork();

    if(pid == -1){
        perror("some problem happened! error!");//should ont enter this state
        exit(1);
    } 
    else if( pid == 0) {
        printf("%d ", num);
        while (num != 1){
            if (num % 2 == 0){//is even
                num = num / 2;
            } 
            else{//is odd
                num = 3 * num + 1;
            }
            printf("%d ", num);
        }
        printf("\n");
        exit(0);
    } 
    else{
        wait(NULL);//wait the child process to terminate
        printf("Child process completed.\n");
    }

    return 0;
}
