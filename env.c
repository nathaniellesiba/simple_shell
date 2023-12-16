#include "shell.h"

/**
*env_builtin - access env variable
*return: always 0
*/

void env_builtin()
{
    extern char **environ; /*Access the environment variables*/

    /*Loop through each environment variable and print it*/
    for (int i = 0; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }
}

int main(void)
{
    char *command = "env"; /*Command entered by the user*/

    if (strcmp(command, "env") == 0)
    {
        env_builtin(); /*Call the env_builtin function*/
    }

    return (0);
}
