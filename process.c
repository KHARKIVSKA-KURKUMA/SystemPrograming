#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

void copyFile(char* source, char* destination) {
    FILE *src, *dest;
    char ch;

    src = fopen(source, "r");
    if (src == NULL) {
        printf("Error opening source file.\n");
        exit(1);
    }

    dest = fopen(destination, "w");
    if (dest == NULL) {
        fclose(src);
        printf("Error opening destination file.\n");
        exit(1);
    }

    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);
    printf("File copied successfully.\n");
}

int main() {
    char* sourceFile = "source.txt";
    char* destFile = "destination.txt";

    // Method #1
    pid_t child_pid;
    clock_t start_time = clock();
    child_pid = fork();
    if (child_pid == 0) {
        copyFile(sourceFile, destFile);
        exit(0);
    } else if (child_pid > 0) {
        wait(NULL);
        clock_t end_time = clock();
        printf("Runtime of fork(): %f sec\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    } else {
        printf("Error calling fork()\n");
        return 1;
    }

    // Method #2
    start_time = clock();
    pid_t exec_child_pid = fork();
    if (exec_child_pid == 0) {
        char* const args[] = {"cp", sourceFile, destFile, NULL};
        execv("/bin/cp", args);
        printf("exec() execution error \n");
        exit(1);
    } else if (exec_child_pid > 0) {
        wait(NULL);
        clock_t end_time = clock();
        printf("Runtime of exec(): %f sec\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    } else {
        printf("Error calling fork()\n");
        return 1;
    }

    // Method #3
    start_time = clock();
    int status = system("cp source.txt destination.txt");
    if (status == -1) {
        printf("system() execution error\n");
        return 1;
    }
    clock_t end_time = clock();
    printf("Runtime of system(): %f sec\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}

