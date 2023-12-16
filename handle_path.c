#include "shell.h"


/**
*descriptor - handle path
*return: 0 on success
*/


int main()
{
    char input[MAX_CMD_LENGTH];
    char path[MAX_PATH_LENGTH];

    /*Get the PATH environment variable*/
    char *env_path = getenv("PATH");

    while (1)
     {
        printf("shell> ");
        fgets(input, MAX_CMD_LENGTH, stdin);

        /*Remove the newline character*/
        input[strcspn(input, "\n")] = 0;

        /*Check if the command exists in any directory of the PATH*/
        char *dir = strtok(env_path, ":");
        int command_exists = 0;

        while (dir != NULL) 
        {
            /*Construct the full path to the command*/
            snprintf(path, sizeof(path), "%s/%s", dir, input);

            /*Check if the file exists*/
            if (access(path, F_OK) == 0)
            {
                command_exists = 1;
                break;
            }

            dir = strtok(NULL, ":");
        }

        if (command_exists) 
        {
            /*Fork and execute the command*/
            pid_t pid = fork();

            if (pid == 0) 
            {
                /*Child process*/
                execl(path, input, NULL);
                perror("exec failed");
                exit(1);
            } 
            else if (pid > 0) 
            {
                /*Parent process*/
                wait(NULL);
            } 
            else 
            {
                /*Fork failed*/
                perror("fork failed");
                exit(1);
            }
        }
        else
        {
            printf("Command not found: %s\n", input);
        }
    }

    return (0);
}
