#ifndef MAIN_H
#define MAIN_H

#include <stdio.h> /* printf, getline */
#include <string.h> /* strtok */
#include <unistd.h> /* execve */
#include <stdlib.h> /* malloc */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* wait */
#include <sys/stat.h> /* stat */

void pid_ppid_test(void);
void arguments_test(int argc, char **argv);
char *read_line_test(size_t buff_bytes);
char **split_cmd_line(char *lineptr, size_t n_ini_tokens, char *delimiters);
void read_split_line(void);
void execute_prog_test(void);
void fork_exe_prog_test(void);
void wait_child_exe_test(void);
void fork_wait_execve(void);
void file_stat(int argc, char *argv[]);

extern char **environ;

void printenv_environ_test(char **envp);
char **getpath(char **envp);

#endif
