#include "shell.h"

/**
 * split_line - A function that tokenize a line.
 *
 * Description: This function takes the line passed in the standard input
 *              and hatch it everytime we encounter specific delimiters
 *              while iterating in it. Every part is put in an array of
 *              strings.
 *
 * @line: String cotaining the full command passed by the user.
 *
 * Return: An array of strings.
 */

char **split_line(char *line)
{
	char **args;
	int index = 0;
	int token_buffer = SHELL_TOKEN_BUFFER;

	args = malloc(sizeof(char *) * token_buffer);
	if (args == NULL) /* Memory allocation for the array of strings */
	{
		fprintf(stderr, "Allocation failed\n");
		exit(EXIT_FAILURE);
	}
	line = strtok(line, SHELL_TOKEN_DELIM); /* Hatch the string when " \t\n" */
	while (line != NULL) /* The first " \t\n" is now '\0' */
	{
		args[index] = line; /* Save the token in the array of strings */
		index++;
		if (index >= token_buffer)
		{
			token_buffer += SHELL_TOKEN_BUFFER; /* Realloc if needed */
			args = realloc(args, sizeof(char *) * token_buffer);
			if (args == NULL)
			{
				fprintf(stderr, "Allocation failed\n");
				exit(EXIT_FAILURE);
			}
		} /* Hatching going on from the last '\0' put with strtok */
		line = strtok(NULL, SHELL_TOKEN_DELIM); /* For each " \t\n" -> '\0' */
	}
	args[index] = NULL; /* Put a NULL to end the array of strings */
	return (args);
}

