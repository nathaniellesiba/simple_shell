#include "shell.h"


#define MAX_COMMAND_LENGTH 100

int main(void)
{
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_COMMAND_LENGTH/2];
    int should_run = 1;

    while (should_run)
    {
        printf("shell> ");
        fflush(stdout);

        /*Read the command line*/
        fgets(command, MAX_COMMAND_LENGTH, stdin);
        command[strcspn(command, "\n")] = '\0'; /*Remove trailing newline*/

        /*Parse the command and arguments*/
        char *token = strtok(command, " ");
        int count = 0;
        while (token != NULL)
        {
            args[count] = token;
            token = strtok(NULL, " ");
            count++;
        }
        args[count] = NULL;

        /*Exit if the user enters the "exit" command*/
        if (strcmp(args[0], "exit") == 0)
        {
            should_run = 0;
            continue;
        }

        /*Fork a child process to execute the command*/
        pid_t pid = fork();

        if (pid < 0)
        {
            fprintf(stderr, "Fork failed\n");
            return (1);
        }
        else if (pid == 0)
        {
            /*Child process*/
            execvp(args[0], args);
            fprintf(stderr, "Command not found: %s\n", args[0]);
            return (1);
        }
        else
        {
            /*Parent process*/
            wait(NULL);
        }
    }

    return (0);
}
