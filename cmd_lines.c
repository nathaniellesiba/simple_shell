#include "shell.h"

#define MAX_COMMAND_LENGTH 100

/**
*descriptor - main file
*return: always o
*/

int main(void) 
{
    char command[MAX_COMMAND_LENGTH];
    char prompt[] = "simple_shell> ";

    while (1) 
    {
        printf("%s", prompt);

        if (fgets(command, sizeof(command), stdin) == NULL) 
        {
            /*Handle end of file condition (Ctrl+D)*/
            printf("\n");
            break;
        }

        /*Remove the newline character*/
        command[strcspn(command, "\n")] = '\0';

        /*Create a child process*/
        pid_t pid = fork();

        if (pid < 0)
        {
            /*Error handling*/
            perror("fork");
            exit(1);
        } 
        else if (pid == 0)
        {
            /*Child process*/

            /*Execute the command*/
            if (execlp(command, command, NULL) == -1) {
                /*Handle command not found error*/
                perror("execlp");
                exit(1);
            }
        } 
        else 
        {
            /*Parent process*/

            /*Wait for the child process to complete*/
            int status;
            waitpid(pid, &status, 0);

            /*Check if the child process exited normally*/
            if (WIFEXITED(status)) 
            {
                int exit_status = WEXITSTATUS(status);
                printf("Command exited with status %d\n", exit_status);
            } 
            else 
            {
                printf("Command did not exit normally\n");
            }
        }
    }

    return (0);
}
