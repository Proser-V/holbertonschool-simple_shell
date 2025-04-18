#ifndef _SHELL_H_
#define _SHELL_H_

/* Librairies */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
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
int execute(char **args, int cmd_count, char *nom_prog);
char *find_command_path(char *command);

/* Built-in command prototypes */
void shell_exit(char *option);
void print_env(char *option);

/* Helpers */
int is_builtin(char **args);
int _atoi(char *s);

#endif
