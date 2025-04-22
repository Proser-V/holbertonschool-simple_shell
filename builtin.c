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
