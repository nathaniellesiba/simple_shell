#include "shell.h"


#define MAX_INPUT_LENGTH 100

/**
*parseInput - check user entered exit cmd
*@input: the cmd
*return: always 0
*/

void parseInput(char* input)
{
    /*Remove newline character from input*/
    input[strcspn(input, "\n")] = '\0';

    /*Check if the user entered the exit command*/
    if (strcmp(input, "exit") == 0)
    {
        exit(0); /*Exit the shell*/
    }

    /*Process other commands here*/
    // ...
}

int main()
{
    char input[MAX_INPUT_LENGTH];

    while (1)
    {
        printf("shell> ");
        fgets(input, sizeof(input), stdin);

        parseInput(input);
    }

    return (0);
}
