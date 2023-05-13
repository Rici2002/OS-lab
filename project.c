#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>

#define NUM_COMMANDS 15

void print_access_rights(mode_t mode) {
    printf("User:\n");
    printf("Read - %s\n", ((mode & 0b100000000)!=0) ? "yes" : "no");
    printf("Write - %s\n", ((mode & 0b10000000)!=0) ? "yes" : "no");
    printf("Exec - %s\n", ((mode & 0b1000000)!=0) ? "yes" : "no");
    printf("\nGroup:\n");
    printf("Read - %s\n", ((mode & 0b100000)!=0) ? "yes" : "no");
    printf("Write - %s\n", ((mode & 0b10000)!=0) ? "yes" : "no");
    printf("Exec - %s\n", ((mode & 0b1000)!=0) ? "yes" : "no");
    printf("\nOthers:\n");
    printf("Read - %s\n", ((mode & 0b100)!=0) ? "yes" : "no");
    printf("Write - %s\n", ((mode & 0b10)!=0) ? "yes" : "no");
    printf("Exec - %s\n", ((mode & 0b1)!=0) ? "yes" : "no");
}

void print_regular_file_info(char* name, char options[]) {
    struct stat st;
    if (stat(name, &st) == -1) {
        perror("stat");
        return;
    }

    printf("Name: %s\n", name);
    printf("Type: Regular file\n");
    printf("Size: %ld bytes\n", st.st_size);
    printf("Hard Link Count: %ld\n", st.st_nlink);
    printf("Time of Last Modification: %ld\n", st.st_mtime);
    printf("Access Rights:\n");
    print_access_rights(st.st_mode);

    printf("Enter options: ");
    fgets(options, sizeof(options), stdin);

    if (strchr(options, 'n')) {
        printf("Name: %s\n", name);
    }

    if (strchr(options, 'd')) {
        printf("Size: %ld bytes\n", st.st_size);
    }

    if (strchr(options, 'h')) {
        printf("Hard Link Count: %ld\n", st.st_nlink);
    }

    if (strchr(options, 'm')) {
        printf("Time of Last Modification: %ld\n", st.st_mtime);
    }

    if (strchr(options, 'a')) {
        printf("Access Rights:\n");
        print_access_rights(st.st_mode);
    }

    if (strchr(options, 'l')) {
        char symlink_name[100];
        printf("Enter symbolic link name: ");
        fgets(symlink_name, sizeof(symlink_name), stdin);
        symlink_name[strcspn(symlink_name, "\n")] = 0;
        if (symlink(symlink_name, name) == -1) {
            perror("symlink");
            return;
        }
        printf("Symbolic link created: %s\n", symlink_name);
    }
}

void print_symlink_info(char* name, char options[]) {
    struct stat st;
    if (lstat(name, &st) == -1) {
        perror("lstat");
        return;
    }

    printf("Name: %s\n", name);
    printf("Type: Symbolic link\n");

    printf("Enter options: ");
    fgets(options, sizeof(options), stdin);

    if (strchr(options, 'n')) {
        printf("Name: %s\n", name);
    }

    if (strchr(options, 'l')) {
        printf("Deleting symbolic link: %s\n", name);
        if (unlink(name) == -1) {
            perror("unlink");
            return;
        }
    }

    if (strchr(options, 'd')) {
        printf("Size of Symbolic Link: %ld bytes\n", st.st_size);
    }

    if (strchr(options, 't')) {
        struct stat target_st;
        if (stat(name, &target_st) == -1) {
            perror("stat");
            return;
        }
        printf("Size of Target File: %ld bytes\n", target_st.st_size);
    }

    if (strchr(options, 'a')) {
        printf("Access Rights:\n");
        print_access_rights(st.st_mode);
    }

    if (strchr(options, 'p')) {
        printf("Changing permissions of symbolic link: %s\n", name);
        if (chmod(name, S_IRWXU | S_IRGRP | S_IWGRP) == -1) {
            perror("chmod");
            return;
        }
        printf("Permissions changed.\n");
    }
}

void print_directory_info(char* name, char options[]) {
    struct stat st;
    if (stat(name, &st) == -1) {
        perror("stat");
        return;
    }

    printf("Name: %s\n", name);
    printf("Type: Directory\n");
    printf("Size: %ld bytes\n", st.st_size);
    printf("Access Rights:\n");
    print_access_rights(st.st_mode);

    printf("Enter options: ");
    fgets(options, sizeof(options), stdin);

    if (strchr(options, 'n')) {
        printf("Name: %s\n", name);
    }

    if (strchr(options, 'd')) {
        printf("Size: %ld bytes\n", st.st_size);
    }

    if (strchr(options, 'a')) {
        printf("Access Rights:\n");
        print_access_rights(st.st_mode);
    }

    if (strchr(options, 'c')) {
        int count = 0;
        DIR* dir;
        struct dirent* entry;
        dir = opendir(name);
        if (dir == NULL) {
            perror("opendir");
            return;
        }

        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG && strstr(entry->d_name, ".c") != NULL) {
                count++;
            }
        }
        closedir(dir);
        printf("Total number of files with .c extension: %d\n", count);
    }

    if (strchr(options, 'f')) {
        char file_name[100];
        snprintf(file_name, sizeof(file_name), "%s/%s_file.txt", name, name);
        FILE* file = fopen(file_name, "w");
        if (file != NULL) {
            fprintf(file, "This is a file created for directory: %s\n", name);
            fclose(file);
            printf("File created: %s\n", file_name);
        } 
        else {
            perror("fopen");
        }
    }
}

void wait2_wstatus(){
    int count=1;
    int wstatus;
    pid_t w;

    while(count<=2){
        w=wait(&wstatus);
        if(WIFEXITED(wstatus)){
            printf("The process with <%d> PID was terminated with exit code <%d>", w, WEXITSTATUS(wstatus));
        }
        count++;
    }
}

void wait1_wstatus(){
    int wstatus;
    pid_t w;
    w=wait(&wstatus);
    if(WIFEXITED(wstatus)){
        printf("The process with <%d> PID was terminated with exit code <%d>", w, WEXITSTATUS(wstatus));
    }
}

int execute_script(char name[]) {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } 
    else if (pid == 0) {
        // Child process
        close(pipe_fd[0]);

        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }

        execl("bash", "bash", "error.sh", name, NULL);
        perror("execl");
        exit(1);
    } 
    else {
        // Parent process
        close(pipe_fd[1]);

        int status;
        waitpid(pid, &status, 0);
        int exit_code = WEXITSTATUS(status);
        printf("The process with PID %d has ended with the exit code %d\n", pid, exit_code);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Script exited with status: %d\n", exit_status);

            char output[1000];
            int bytes_read = read(pipe_fd[0], output, sizeof(output) - 1);
            if (bytes_read > 0) {
                output[bytes_read] = '\0';
                printf("Script output:\n%s\n", output);

                int num_errors = 0;
                int num_warnings = 0;

                printf("Number of errors: %d\n", num_errors);
                printf("Number of warnings: %d\n", num_warnings);
            } 
            else {
                printf("Script output is empty.\n");
            }
        } 
        else {
            printf("Script did not exit normally.\n");
        }

        close(pipe_fd[0]);
    }

    return 0;
}

void check_file(char name[]){
    while(name[strlen(name)-1]=='c' && name[strlen(name)-2]=='.') {
        execute_script(name);
    }
}

void newFile(char name[]){
    pid_t pid;
    pid=fork();

    if(pid<0){
        printf("Error\n");
        exit(1);
    }

    else if(pid==0){
        char fileName[100];
        char path[200];

        strcpy(fileName, name);
        strcat(fileName, "_file.txt");

        strcpy(path, name);
        strcat(path, "/");
        strcat(path, fileName);

        int create=execlp("touch", "touch", path, NULL);
        if(create==-1){
            printf("error at creating");
            exit(2);
        }
        close(create);
    }

    else{
        wait2_wstatus();
    }
}

char* do_options(){
    char* options;
    options=(char*)malloc(NUM_COMMANDS*sizeof(char));
    if(options==NULL){
        printf("error for commands string\n");
        exit(1);
    }
    printf("Insert the options you want: ");
    scanf("%s", options);
    return options;
}

void do_regular_file(char name[]){
    char options[NUM_COMMANDS];
    strcpy(options, do_options());
    print_regular_file_info(name, options);
}

void do_symbolic_link(char name[]){
    char options[NUM_COMMANDS];
    strcpy(options, do_options());
    print_symlink_info(name, options);
}

void do_directory(char name[]){
    char options[NUM_COMMANDS];
    strcpy(options, do_options());
    print_directory_info(name, options);
}

int main(int argc, char* argv[]){
    if (argc==1) {
        printf("Not enough arguments\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        struct stat st;
        if (lstat(argv[i], &st) == -1) {
            perror("lstat");
            continue;
        }

        printf("File: %s\n", argv[i]);
        printf("Type: ");
        if (S_ISREG(st.st_mode)) {
            if (strstr(argv[i], ".c") != NULL) {
                execute_script(argv[i]);
            } 
            else {
                FILE* file = fopen(argv[i], "r");
                if (file != NULL) {
                    int num_lines = 0;
                    char ch;
                    while ((ch = fgetc(file)) != EOF) {
                        if (ch == '\n') {
                            num_lines++;
                        }
                    }
                    fclose(file);
                    printf("Number of lines: %d\n", num_lines);
                }
            }
        }

        else if (S_ISLNK(st.st_mode)) {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                continue;
            } 
            else if (pid == 0) {
                // Child process
                print_symlink_info(argc, argv[i]);
                exit(0);
            }
        } 

        else if (S_ISDIR(st.st_mode)) {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                continue;
            } 
            else if (pid == 0) {
                // Child process
                print_directory_info(argc, argv[i]);
                exit(0);
            }
        } 
        else {
            printf("Unsupported file type\n");
        }
    }

    while (wait(NULL) > 0) {
        continue;
    }

    return 0;
}



