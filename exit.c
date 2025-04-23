#include "shell.h"

/**
 * isposnumber - determines if a string is a positive number
 * @num_str: input string to examine
 * Return: 0 if it is not a positive number, 1 if it is
 */

int isposnumber(char *num_str)
{
	size_t i = 0;

	while (num_str[i] >= '0' && num_str[i] <= '9' && num_str[i] != '\0')
		++i;
	if (strlen(num_str) == i)
		return (1);
	else
		return (0);
}

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
	if (isposnumber(args[1]) == 0) /* If it is not a positive number */
	{
		fprintf(stderr, "%s: %d: %s: Illegal number: %s\n"
			, nom_prog, cmd_count, args[0], args[1]);
		free(args);
		free(line);
		return (2); /* error code 2 returned */
	}
	code = _atoi(args[1]); /* Get a number from argument passed with exit */
	free(args);
	free(line);
	exit(code); /* exit with the code passed by the user */
}
