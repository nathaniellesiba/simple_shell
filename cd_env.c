#include "shell.h"

/*main - function name
*@argc - argument countname of programme to be executed
*@argv - array of ar
*return: 0 on success
*/

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (chdir(argv[1]) == -1)
    {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    return (0);
}i
