#ifndef _SHELL_H_
#define _SHELL_H_

/* Librairies */
#include <stdio.h> /* printf, getline */
#include <string.h> /* strtok, strcmp, strdup, strcat */
#include <stdlib.h> /* malloc */
#include <unistd.h> /* execve, isatty, access */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* wait */
#include <errno.h> /* errno */
#include <fcntl.h>

/* External variables */
extern char **environ;

/* Macro definition */
#define SHELL_READ_BUFFER 1024
#define SHELL_TOKEN_BUFFER 64
#define SHELL_TOKEN_DELIM " \t\n"

/**
 * struct builtin - Structure containing built-in names and functions.
 *
 * @command: The command text to call for a built-in function.
 * @func: A pointer to the matching function to call.
 *
 */

typedef struct builtin
{
	char *command;
	void (*func)(char *option);
} builtin_t;

/* Backbone prototypes */
char *read_line(void);
char **split_line(char *line);
void execute(char **args, int cmd_count, char *nom_prog, int *exit_status);
char *find_command_path(char *command);

/* Built-in command prototypes */
void print_env(char *option);
int exit_built(char **args, int cmd_count, char *nom_prog);

/* Helpers */
int is_builtin(char **args);
int _atoi(char *s);
int handle_builtin(char **args, int *exit_status);

#endif
