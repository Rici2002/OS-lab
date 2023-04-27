#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(){
    pid_t pid, w;
    pid=fork();
    int wstatus;

    if(pid<0){
        printf("Error");
        exit(1);
    }

    if(pid==0){
        printf("Child process id is %d\n", getpid());
        exit(0);
    }
    else{
        if(pid>0){
            printf("Parent process\n");
            w=wait(&wstatus);
            if(WIFEXITED(wstatus)){
                printf("The process with pid %d, exited, status=%d\n", w, WEXITSTATUS(wstatus));
            }
        }
    }
}