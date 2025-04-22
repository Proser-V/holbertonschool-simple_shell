#include "shell.h"

/**
 * exit_built - A built-in command for exit.
 *
 * @line: Pointer to the input string.
 * @args: Tokenized string passed by the user.
 * @cmd_count: The number of commands passed to the program.
 * @nom_prog: The name of the program (Shell) from main.
 *
 * Return: 1 on succes execution, -1 on error.
 */

int exit_built(char *line, char **args, int cmd_count, char *nom_prog)
{
	int code = 0;
/* args[1] not NULL (see in main function) */
	if (strcmp(args[1], "0") == 0)
	{
		free(args);
		free(line);
		exit(code);
	}
	code = _atoi(args[1]); /* Get a number from argument passed with exit */
	if (code == 0) /* If no number in the argument */
	{
		fprintf(stderr, "%s: %d: %s: Illegal number: %s\n"
			, nom_prog, cmd_count, args[0], args[1]);
		free(args);
		free(line);
		return (2); /* error code 2 returned */
	}
	free(args);
	free(line);
	exit(code); /* exit with the code passed by the user */
}
