#include "XL_main.h"

/**
 * read_line_test - tests the getline function
 * @buff_bytes: size of the buffer in bytes
 * Return: pointer to input line as a string
 */

char *read_line_test(size_t buff_bytes)
{
	char *lineptr;
	ssize_t gotten_chars;

	lineptr = malloc(buff_bytes * sizeof(char));
	if (!lineptr)
	{
		fprintf(stderr, "ERROR: malloc failure\n");
		exit(EXIT_FAILURE);
	}
	printf("$ ");
	gotten_chars = getline(&lineptr, &buff_bytes, stdin);
	if (gotten_chars < 0)
	{
		fprintf(stderr, "ERROR: getline failure\n");
		free(lineptr);
		exit(EXIT_FAILURE);
	}
	printf("%s", lineptr);
	printf("gotten_chars (including newline) = %li\n", gotten_chars);
	printf("lineptr = %s", lineptr);
	printf("buff_bytes = %li\n", buff_bytes);
	return (lineptr);
}
