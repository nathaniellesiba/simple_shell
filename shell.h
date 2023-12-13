#ifndef SHELL_H
#define SHELL_H

/*---LIBRARIES---*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/*---Macros---*/
#define TOK_DELIM " \t\r\n\a\""
extern char **environ;

/*---PROTOTYPES---*/
/* main.c */
void interactive_shell(void);
void shell_not_interactive(void);

/* shell_interactive.c */
char *read_line(void);
char **parse(char *line);
int execute(char **args);

/* execute_args */
int new_process(char **args);

/* shell_no_interactive */
char *read_stream(void);

/*---Builtin func---*/
int own_cd(char **args);
int own_exit(char **args);
int own_env(char **args);
int own_help(char **args);

int main(int argc, char *argv[]);
int shell(info_t *info, char **av);
int builtin(info_t *info);
void cmd(info_t *info);
void forkc(info_t *info);


#endif
