#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100

void execute_command(char *command) {
    char *args[10]; // Assuming at most 10 arguments
    char *token = strtok(command, " \n");
    int i = 0;

    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        execvp(args[0], args);
        perror("Error");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);
    } else {
        perror("Error");
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        printf("SimpleShell> ");
        fgets(input, MAX_INPUT_LENGTH, stdin);

        if (strcmp(input, "exit\n") == 0) {
            break;
        }

        execute_command(input);
    }

    return 0;
}
