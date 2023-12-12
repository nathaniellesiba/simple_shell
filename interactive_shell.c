#include "shell.h"

/**
 * interactive_shell - UNIX cmd line interpreter
 *
 * Return: void
 */
void interactive_shell(void)
{
 char *line;
 char **args;
 int status = -1;

 do {
  printf("simple_prompt$ "); /* print prompt symbol */
  line = read_line(); /* read line from stdin */
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