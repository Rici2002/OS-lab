#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define NUM_COMANDS 20

void show_regular_file(){
    printf(" Menu \n");
    printf("Name: -n\n");
    printf("Size: -d\n");
    printf("Hard link count: -h\n");
    printf("Time of last modification: -m\n");
    printf("Access rights: -a\n");
    printf("Create symbolic link: -l\n");
    printf("Insert the desired options: ");
}

void show_directory() {
    printf(" Menu \n");
    printf("Name: -n\n");
    printf("Size: -d\n");
    printf("Total number of files with the .c extension: -c\n");
    printf("Access rights: -a\n");
    printf("Insert the desired options: ");
}

void show_symbolic_link() {
    printf(" Menu \n");
    printf("Name: -n\n");
    printf("Delete symbolic link: -l\n");
    printf("Size of symbolic link: -d\n");
    printf("Size of targeted file: -t\n");
    printf("Access rights: -a\n");
    printf("Insert the desired options: ");
}

void access_rights(mode_t mode) {
    printf("User:\n");
    printf("Read - %s\n", ((mode & 0b100000000)!=0) ? "Yes" : "No");
    printf("Write - %s\n", ((mode & 0b10000000)!=0) ? "Yes" : "No");
    printf("Exec - %s\n", ((mode & 0b1000000)!=0) ? "Yes" : "No");
    printf("Group:\n");
    printf("Read - %s\n", ((mode & 0b100000)!=0) ? "Yes" : "No");
    printf("Write - %s\n", ((mode & 0b10000)!=0) ? "Yes" : "No");
    printf("Exec - %s\n", ((mode & 0b1000)!=0) ? "Yes" : "No");
    printf("Others:\n");
    printf("Read - %s\n", ((mode & 0b100)!=0) ? "Yes" : "No");
    printf("Write - %s\n", ((mode & 0b10)!=0) ? "Yes" : "No");
    printf("Exec - %s\n", ((mode & 0b1)!=0) ? "Yes" : "No");
}

void reg_files(char name[], char commands[NUM_COMANDS]) {
    struct stat st;
    stat(name, &st);

    if(stat(name, &st)==-1){
        printf("Error");
        exit(1);
    }



    for(int i=1;i<strlen(commands);i++) {
        switch(commands[i]) {
            case 'n': 
                printf("Name of the file: %s\n", name);
                break;
            case 'd': 
                printf("Size: %ld\n", st.st_size);
                break;
            case 'h': 
                printf("Hard link count: %ld\n", st.st_nlink);
                break;
            case 'm':
                printf("Time of last modification: %d\n", ctime(&st.st_mtime));
                break;
            case 'a': 
                access_rights(st.st_mode);
                break;
            case 'l': 
                printf("Please enter the name of the link: ");
                char *link_name;
                scanf("%s", link_name);
                symlink(name, link_name);
                break;
            default:
                printf("Unknown command\n");

        }
    }
}

void sym_links(char *name, char commands[NUM_COMANDS]) {
    struct stat link, targeted_file;
    lstat(name, &link);
    for(int i=1;i<strlen(commands);i++) {
        switch(commands[i]) {
            case 'n':
                printf("Name of the symbolic link: %s\n", name);
                break;
            case 'l':
                printf("Delete the symbolic link\n");
                unlink(name);
                break;
            case 'd':
                printf("Size of the symbolic link: %ld\n", link.st_size);
                break;
            case 't':
                stat(name, &targeted_file);
                printf("Size of the targeted file: %ld\n", targeted_file.st_size);
                break;
            case 'a':
                access_rights(link.st_mode);
                break;
            default:
                printf("Unknown command\n");
        }
        if(commands[i]=='l') {
            printf("The rest of the commands will not be performed\n");
            break;
        }
    }
}

void processes(char *name, char [NUM_COMANDS]){
    pid_t pid, w;
    int wstatus1, wstatus2;
    if(reg_files()){
        pid=fork();
        int wstatus1;

        if(pid<0){
        printf("Error");
        exit(1);
        }

        if(pid==0){
        printf(show_regular_file);
        exit(0);
        }
        else{
            if(pid>0){
                printf("Parent process\n");
            }
        }
   }

   if(directory()){
        pid=fork();
        int wstatus2;

        if(pid<0){
            printf("Error");
            exit(1);
        }
        if(pid==0){
            printf(show_directory);
            exit(0);
        }
        else{
            if(pid>0){
                printf("Child process");
            }
        }
   }
    w=wait(&wstatus1);
    if(WIFEXITED(wstatus1)){
        printf("The process with pid %d, exited, status=%d\n", w, WEXITSTATUS(wstatus1));
    }

    w=wait(&wstatus2);
    if(WIFEXITED(wstatus2)){
        printf("The process with pid %d, exited, status=%d\n", w, WEXITSTATUS(wstatus2));
    }
}

int main(int argc, char* argv[]) {
    struct stat st;
    char commands[NUM_COMANDS];
    
    if(argc==1){
        printf("Not enough arguments.\n");
        exit(1);
    }

    return 0;
}