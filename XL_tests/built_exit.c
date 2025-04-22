#include "shell.h"

/**
 * built_exit - frees allocated memory and exits program
 * @args: tokenized input line
 * @cmd_n: command number (identifier of the current command line in
 * interactive mode)
 * @prog: name of the programm (of the shell)
 * @line: original input string that has had its delimiters replaced by \0
 * @status: address of variable containing the exit status to be used by exit
 * if no exit code is expicitly given
 */

void built_exit(char **args, int cmd_n, char *prog, char **line, int *status)
{
	if (args[1] == NULL)
	{
		free(args);
		free(line);
		exit(status);
	}	
	
	
	*status = args[1];
	
}
