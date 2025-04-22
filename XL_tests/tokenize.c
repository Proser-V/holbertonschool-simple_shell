#include "ss_shell.h"

/**
 * tokenize - split a string into tokens according to a set of delimiters
 * (separators)
 * @line: pointer to the string
 * Return: array of pointers to each token IN the string (it does not copy the
 * string, it only substitutes the chosen separators by null-bytes and provides
 * pointers to each null-terminated sub-string)
 */

char **tokenize(char *line)
{
	char **tokens; /* array with the tokens in input line */
	size_t n_tokens = 1; /* number of allowed tokens */
	char *delimiters = " \t\n"; /* characters that delimit those token */
	size_t i;
	char *line_ptr;

	for (line_ptr = line; strtok(line_ptr, delimiters) != NULL; line_ptr = NULL)
		++n_tokens;
	tokens = malloc(n_tokens * sizeof(char *));
	if (!tokens)
	{
		perror("malloc: tokenized input line");
		free(line);
		exit(EXIT_FAILURE);
	}
	tokens[0] = strtok(line, delimiters);
	for (i = 1; tokens[i - 1] != NULL; ++i)
		tokens[i] = strtok(NULL, delimiters);
	return (tokens);
}
