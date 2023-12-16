#include "shell.h"

/**
*main - the file descriptor
*return: 0 on success
*/

#define MAX_COMMAND_LENGTH 100

int main(void)
{
    char command[MAX_COMMAND_LENGTH];

    while (1)
    {
        printf("Enter a command: ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        /*Remove newline character from the command*/
        command[strcspn(command, "\n")] = '\0';

        /*Check if the command is a comment*/
        if (command[0] == '#')
        {
            continue;
        }

        /*Execute the command*/
        system(command);
    }

    return (0);
}
