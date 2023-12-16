#include "shell.h"

/**
 * main - function that checks if 
 * our shell is called
 * isatty determines if file 
 * descriptor is associated
 * with a terminal
 * Return: 0 on success
 */
int main(void)
{

 if (isatty(STDIN_FILENO) == 1)
 {
  interactive_shell();
 }
 else
 {
  shell_not_interactive();
 }
 return (0);
}
