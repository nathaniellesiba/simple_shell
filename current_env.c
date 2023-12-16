#include "shell.h"

#define MAX_ARGS 10
#define MAX_BUFFER 1024

/**
*print_environmemt - env name
*@envp - array of strings passed as env to new program
*/

void print_environment(char* envp[]) 
{
    char** env = envp;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}

/**
*main - env name
*@envp - array of strings passed as env to new program
*@argv - argument vector
*@argv - argument count
*return: 0 on sucess
*/

int main(int argc, char* argv[], char* envp[])
{
    char buffer[MAX_BUFFER];
    char* args[MAX_ARGS];
    char* token;
    int status;

    while (1) 
    {
        printf(">> ");
        fgets(buffer, MAX_BUFFER, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; /*Remove trailing newline character*/

        /*Tokenize input*/
        int i = 0;
        token = strtok(buffer, " ");
        while (token != NULL) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        /*Handle built-in commands*/
        if (strcmp(args[0], "env") == 0) 
        {
            print_environment(envp);
            continue;
        }

        /*Fork and execute command*/
        pid_t pid = fork();
        if (pid == 0) 
        {
            /*Child process*/
            execvp(args[0], args);
            printf("Command not found: %s\n", args[0]);
            exit(1);
        } 
        else 
        {
            /*Parent process*/
            waitpid(pid, &status, 0);
            printf("Exit status: %d\n", status);
        }
    }

    return (0);
}
