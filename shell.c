#include "shell.h"

char *get_command(void) {
    ssize_t read_size;
    char *input = NULL;
    size_t size = 0;

    printf(":$ ");
    read_size = getline(&input, &size, stdin);

    if (read_size == -1) {
        if (feof(stdin)) {
            return NULL;  
        } else {
            perror("getline");
            exit(EXIT_FAILURE);
        }
    }

    if (input[read_size - 1] == '\n') {
        input[read_size - 1] = '\0';
    }

    return input;
}

extern char **environ;

int execute_command(char *command) {
    char *args[256];
    int i = 0;
    pid_t pid;

    args[i++] = strtok(command, " ");

    while ((args[i] = strtok(NULL, " ")) != NULL && i < 255) {
        i++;
    }
    args[i] = NULL;

    if (strcmp(args[0], "exit") == 0) {
        printf("Exiting the shell\n");
        exit(0);
    } else if (strcmp(args[0], "env") == 0) {
        char **env = environ;
        while (*env != NULL) {
            printf("%s\n", *env);
            env++;
        }
        return 0;  
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            printf("Error: Command not found\n");
            return -1;  
    }

    return 0;  
    }
}