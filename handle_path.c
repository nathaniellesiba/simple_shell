#include "shell.h"

#define MAX_ARGS 64
#define MAX_PATH 1024

/**
**path_dirs - pointer to path
*@env_path: the environment path
*return: always 0
*/

char *path_dirs[MAX_ARGS];

void parse_path(char *env_path) {
    int i = 0;
    char *dir = strtok(env_path, ":");
    while (dir != NULL && i < MAX_ARGS) {
        path_dirs[i++] = dir;
        dir = strtok(NULL, ":");
    }
    path_dirs[i] = NULL;
}

char *get_command_path(char *command) {
    char *command_path = malloc(MAX_PATH);
    if (command[0] == '/') {
        // Absolute path provided
        strcpy(command_path, command);
        return command_path;
    }

    // Check command in each directory in PATH
    for (int i = 0; path_dirs[i] != NULL; i++) {
        snprintf(command_path, MAX_PATH, "%s/%s", path_dirs[i], command);
        if (access(command_path, X_OK) == 0) {
            return command_path;
        }
    }

    // Command not found
    free(command_path);
    return NULL;
}

int main() {
    char *input;
    char *args[MAX_ARGS];
    char *env_path = getenv("PATH");

    parse_path(env_path);

    while (1) {
        printf(":) ");
        fflush(stdout);

        input = NULL;
        size_t input_size = 0;
        getline(&input, &input_size, stdin);

        // Remove newline character from input
        input[strcspn(input, "\n")] = 0;

        // Split input into arguments
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            args[++i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] != NULL) {
            // Check if command exists
            char *command_path = get_command_path(args[0]);
            if (command_path == NULL) {
                printf("Command not found: %s\n", args[0]);
                continue;
            }

            pid_t pid = fork();
            if (pid == 0) {
                // Child process
                execv(command_path, args);
                perror("execv");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                // Parent process
                wait(NULL);
            } else {
                perror("fork");
            }

            free(command_path);
        }

        free(input);
    }

    return (0);
}
