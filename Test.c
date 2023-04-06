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

int main(int argc, char* argv[]) {
    struct stat file_stat;
    char options[256];
    int i;

    return 0;
}