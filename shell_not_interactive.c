#include "shell.h"

/**
 * shell_not_interactive - unix command line interpreter
 *
 * Return: void
 */
void shell_not_interactive(void)
{
 char *line;
 char **args;
 int status = -1;

 do {
  line = read_stream();
  args = parse(line); /* tokenize line */
  status = execute(args);
  /* avoid memory leaks */
  free(line);
  free(args);
  /* exit with status */
  if (status >= 0)
  {
   exit(status);
  }
 } while (status == -1);
}