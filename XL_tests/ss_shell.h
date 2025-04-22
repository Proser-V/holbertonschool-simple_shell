#ifndef SS_SHELL_H
#define SS_SHELL_H

#include <stdio.h> /* printf, getline */
#include <string.h> /* strtok, strcmp */
#include <unistd.h> /* execve */
#include <stdlib.h> /* malloc */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* wait */

#include <sys/stat.h> /* stat */
#include <errno.h> /* errno */

char *read_line(void);
char **tokenize(char *line);
int yes_exit(char *first_token);
char **getpath(char **env);
char *find_file(char *, char **envp);

#endif
