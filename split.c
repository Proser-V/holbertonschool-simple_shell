#include "shell.h"

/**
 * split_line - A function that tokenize a string.
 *
 * Description: This function takes a string as argument and replaces each
 *              delimiter by a null-byte. Pointers to the beginning of each
 *              substring are returned in a null-terminated pointer array.
 *
 * @line: String containing the full command passed by the user.
 *
 * Return: An array of strings, or NULL if no character different from
 * delimiters.
 */

char **split_line(char *line)
{
	char **args;
	int index = 0;
	int token_number = 1;

	char *line2;
	char *line2_ptr;

	line2 = strdup(line); /* Count the number of tokens to store */
	line2_ptr = strtok(line2, SHELL_TOKEN_DELIM);
	for (token_number = 1; line2_ptr != NULL; ++token_number)
		line2_ptr = strtok(NULL, SHELL_TOKEN_DELIM);
	free(line2);

	args = malloc(sizeof(char *) * token_number);
	if (args == NULL) /* Memory allocation for the array of strings */
	{
		perror("allocation failed");
		exit(errno);
	}
	line = strtok(line, SHELL_TOKEN_DELIM); /* point to first non-delimiter */
											/* character of the string and */
											/* replace first delimiter by \0 */
	while (line != NULL)
	{
		args[index] = line; /* store pointer to current delimited sub-string */
		index++;
		line = strtok(NULL, SHELL_TOKEN_DELIM); /* point to next sub-string */
	}
	args[index] = NULL; /* Put a NULL at end of the array of strings */
	return (args);
}

