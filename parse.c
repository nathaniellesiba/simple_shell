#include "shell.h"

/**
 * parse - split a string into multiple strings
 * @line: string to be splited
 *
 * Return: pointer that points to the new array
 */
char **parse(char *line)
{
 int bufsize = 64;
 int i = 0;
 char **tokens = malloc(bufsize * sizeof(char *));
 char *token;

 if (!tokens)
 {
  fprintf(stderr, "allocation error in parse: tokens\n");
  exit(EXIT_FAILURE);
 }
 token = strtok(line, TOK_DELIM);
 while (token != NULL)
 {
  /* handle comments */
  if (token[0] == '#')
  {
   break;
  }
  tokens[i] = token;
  i++;
  if (i >= bufsize)
  {
   bufsize += bufsize;
   tokens = realloc(tokens, bufsize * sizeof(char *));
   if (!tokens)
   {
    fprintf(stderr, "reallocation error in parse: tokens");
    exit(EXIT_FAILURE);
   }
  }
  token = strtok(NULL, TOK_DELIM);
 }
 tokens[i] = NULL;
 return (tokens);
}