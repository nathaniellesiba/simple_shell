#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGUMENTS];
    char *path = getenv("PATH");
    char *dir;
    int i = 0;

    /*Parse the command line*/
    printf("Enter a command: ");
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    /*Remove newline character from the command*/
    command[strcspn(command, "\n")] = 0;

    /*Tokenize the command line arguments*/
    args[0] = strtok(command, " ");
    while (args[i] != NULL && i < MAX_ARGUMENTS - 1)
    {
        i++;
        args[i] = strtok(NULL, " ");
    }
    args[i + 1] = NULL;

    /*Iterate over each directory in PATH*/
    dir = strtok(path, ":");
    while (dir != NULL)
    {
        char commandPath[MAX_COMMAND_LENGTH];
        pid_t pid;

        /*Construct the command path*/
        snprintf(commandPath, sizeof(commandPath), "%s/%s", dir, args[0]);

        /*Check if the command exists in the directory*/
        if (access(commandPath, X_OK) == 0)
        {
            /*Fork a child process*/
            pid = fork();

            if (pid == 0)
            {
                /*Child process*/
                execv(commandPath, args);
                exit(0);
            }
            else if (pid > 0)
            {
                /*Parent process*/
                wait(NULL);
                exit(0);
            }
            else
            {
                /*Forking failed*/
                perror("fork");
                exit(1);
            }
        }

        /*Move to the next directory in PATH*/
        dir = strtok(NULL, ":");
    }

    /*Command not found*/
    printf("Command not found\n");

    return (0);
}
