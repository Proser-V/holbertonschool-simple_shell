#include "shell.h"

/**
 * is_builtin - A function helper to check if the passed command is a built-in
 *              function.
 *
 * Description: This function checks if the first element of the array of
 *              strings (the command) is in the implemented list. If yes
 *              the matching function is called.
 *
 * @args: Tokenized string passed by the user.
 *
 * Return: 1 if a builtin function was found, -1 if not.
 */

int is_builtin(char **args)
{
	builtin_t builtins[] = {
		{ "env", print_env },
		{ NULL, NULL }
	}; /* Array of structures containing the builtin function names */
	int index;

	for (index = 0; builtins[index].command != NULL; index++)
	{
		if (strcmp(args[0], builtins[index].command) == 0)
		{ /* Compare the text passed by the user to the correct input name */
			builtins[index].func(args[1]);
			return (0); /* Same name found, execute the matching function */
		}
	}
	return (-1); /* No matching name found */
}

/**
 * print_env - Built-in function to prints the current environment.
 *
 * Description: This function prints the current environment.
 *
 * @option: Argument pass to the function - Non-implemented.
 *
 * Return: nothing (void).
 */

void print_env(char *option)
{
	int index = 0;

	(void)option; /* Option non-implemeted yet */

	while (environ[index] != NULL) /* Print all the environnement variables */
	{
		printf("%s\n", environ[index]);
		index++;
	}
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
