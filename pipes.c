#include <stdio.h>

int main(){


    int pipe(filedes[2]);


    pid=fork();
    if(pid==0){
        //copil
        int count,lenght;
        for(int i=0; i<lenght; i++){
            count+=i;
        }
        
        close(filedes[1], 1);
        write(filedes[0], 0)
    }
    else{
        //parinte
        pid=fork();
        if(pid<0){
            printf("error");
            exit(1);
        }
        if(pid==0){
            //copil
        }
        else{
            //parinte
        }
    }
}