#include "XL_main.h"

/**
 * split_cmd_line - splits the entered command line in "words" or "tokens"
 * separated by chosen delimeters
 * @lineptr: pointer to the string that contains the commands entered at the
 * system prompt
 * @n_ini_tokens: initial max number of tokensthat can be stored and treated
 * @delimiters: string with the delimiters to split the command line input with
 * Return: pointer to array of strings (pointers to chars)
 */

char **split_cmd_line(char *lineptr, size_t n_ini_tokens, char *delimiters)
{
	size_t idx;
	char **line_token;

	line_token = malloc(n_ini_tokens * sizeof(char *));
	if (!line_token)
	{
		fprintf(stderr, "ERROR: line_token malloc failure\n");
		exit(EXIT_FAILURE);
	}
	line_token[0] = strtok(lineptr, delimiters);
	if (line_token[0] != NULL)
		printf("line_token[%i] = %s\n", 0, line_token[0]);
	for (idx = 1; line_token[idx - 1] != NULL; ++idx)
	{
		if (idx >= n_ini_tokens)
		{
			fprintf(stderr, "ERROR: insufficient memory for command array\n");
			free(line_token);
			exit(EXIT_FAILURE);
		}
		line_token[idx] = strtok(NULL, delimiters);
		if (line_token[idx] != NULL)
			printf("line_token[%li] = %s\n", idx, line_token[idx]);
	}
	return (line_token);
}
