#ifndef SHELL_H
#define SHELL_H

/*---LIBRARIES---*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>


#define MAX_BUFFER 1024
#define MAX_CMD_LENGTH 100
#define MAX_PATH_LENGTH 100



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

/*print current environment*/
void print_environment(char* envp[]);
int main(int argc, char* argv[], char* envp[]);
void parse_path(char *env_path);
char *get_command_path(char *command);
void parseInput(char* input);
void env_builtin();




#endif
