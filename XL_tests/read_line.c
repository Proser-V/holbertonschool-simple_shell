#include "ss_shell.h"

/**
 * read_line - reads a line and store it in a buffer
 * Return: on success, pointer to the buffer. On failure, it terminated the
 * process
 */

char *read_line(void)
{
	size_t buff_bytes = 64; /* buffer for input line */
	char *line; /* pointer to stored input line */
	ssize_t got_chars; /* number of chracters in the input line */
	int errno_tmp;

	line = malloc(buff_bytes * sizeof(char));
	if (!line)
	{
		perror("malloc: input line buffer");
		exit(EXIT_FAILURE);
	}
	errno_tmp = errno;
	errno = 0;
	got_chars = getline(&line, &buff_bytes, stdin);
	if (errno != 0 && got_chars == -1)
	{
		perror("getline: input line");
		free(line);
		exit(EXIT_FAILURE);
	}
	if (errno == 0 && got_chars == -1)
	{
		errno = errno_tmp;
		free(line);
		printf("\n");
		exit(EXIT_SUCCESS);
	}
	return (line);
}
