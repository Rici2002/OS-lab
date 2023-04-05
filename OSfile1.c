#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define NUM_OF_COMANDS 20

void display_regular_file(){
    printf("--- MENU ---\n");
    printf("Name: -n\n");
    printf("Size: -d\n");
    printf("Hard link count: -h\n");
    printf("Time of last modification: -m\n");
    printf("Access rights: -a\n");
    printf("Create symbolic link: -l\n");
    printf("Insert the desired options: ");
}

void display_directory() {
    printf("--- MENU ---\n");
    printf("Name: -n\n");
    printf("Size: -d\n");
    printf("Time of last modification: -m\n");
    printf("Access rights: -a\n");
    printf("Insert the desired options: ");
}

void display_symbolic_link() {
   printf("--- MENU ---\n");
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

void reg_files(char *name, char commands[NUM_OF_COMANDS]) {
    struct stat st;
    stat(name, &st);

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

void sym_links(char *name, char commands[NUM_OF_COMANDS]) {
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

/*int main(int argc, char* argv[]) {
    struct stat file_stat;
    char options[256];
    int i;

    for (i = 1; i < argc; i++) {
        if (lstat(argv[i], &file_stat) == -1) {
            perror("lstat");
            continue;
        }

        if (S_ISREG(file_stat.st_mode)) {
            display_regular_file(argv[i]);
        } else if (S_ISDIR(file_stat.st_mode)) {
            display_directory(argv[i]);
        } else if (S_ISLNK(file_stat.st_mode)) {
            display_symbolic_link(argv[i]);
        } else {
            printf("Unknown file type: %s\n", argv[i]);
        }

        printf("Enter options for %s: ", argv[i]);
        fgets(options, 256, stdin);

        // Process options here

        printf("File: %s\n", argv[i]);
        printf("Options: %s\n", options);
    }

    return 0;
}*/

int main(int argc, char **argv) {
    if(argc==1) {
        printf("Too few arguments\n");
        exit(1);
    }

    struct stat st;
    char commands[NUM_OF_COMANDS];

    for(int i=1;i<argc;i++) {
        if(lstat(argv[i], &st) == 0) {
            printf("%s - SYMBOLIC LINK\n", argv[i]);
            display_symbolic_link();
            scanf("%s", commands);
            sym_links(argv[i], commands);
        }

        if(stat(argv[i], &st)==0) {
            printf("%s - SYMBOLIC LINK\n", argv[i]);
            display_regular_file();
            scanf("%s", commands);
            reg_files(argv[i], commands);
        }
        
    }

    return 0;
}
