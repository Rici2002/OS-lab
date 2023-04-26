#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    pid=fork();
    if(pid==0){
        printf("Child process id is %d\n", getpid());
        exit(0);
    }
    else{
        
        printf("Parent process id is %d\n", getpid());
    }
}