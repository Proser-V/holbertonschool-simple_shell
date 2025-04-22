#include "XL_main.h"

/**
 * read_split_line - tests reading command line and splitting it
 * Return: nothing
 */

void read_split_line(void)
{
	int i;
	char *lineptr;
	char **line_token;
	size_t n_ini_tokens = 16;
	size_t buff_bytes = 64;
	char *delimiters = " \t\v\n";

	if (n_ini_tokens < 2)
	{
		fprintf(stderr, "ERROR: allocate memory for minimum two tokens");
		exit(EXIT_FAILURE);
	}
	lineptr = read_line_test(buff_bytes);
	printf("lineptr is normally: %s\n", lineptr);
	line_token = split_cmd_line(lineptr, n_ini_tokens, delimiters);
	for (i = 0; line_token[i] != NULL; ++i)
	{
		if (i > 0)
			printf(" | ");
		printf("line_token[%i]", i);
	}
	printf("\n");
	for (i = 0; line_token[i] != NULL; ++i)
	{
		if (i > 0)
			printf(" | ");
		printf("%13s", line_token[i]);
	}
	printf("\n");
	printf("lineptr, after strtok, is: %s\n", lineptr);
	free(line_token);
	free(lineptr);
}
