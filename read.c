#include "shell.h"

/**
 * read_line - read a line from the standard input.
 *
 * Description: This function gets a line from the standard input and puts
 *              it in a buffer.
 *
 * Return: A string containing the user's input, or NULL if input is EOF.
 */

char *read_line(void)
{
	char *line;
	size_t buff_size = SHELL_READ_BUFFER;
	int errno_tmp;

	line = malloc(sizeof(char) * buff_size); /* Buffer memory allocation */
	if (line == NULL)
	{
		perror("allocation failed");
		exit(errno);
	}
	errno_tmp = errno;
	errno = 0; /* Set errno to 0 to isolate EOF management from getline */
	if (getline(&line, &buff_size, stdin) == -1) /* Put the line in a buffer */
	{ /* and checks for errors */
		if (errno != 0) /* If (getline = -1 and errno = 0) -> EOF */
		{
			perror("getline failed");
			free(line);
			exit(errno);
		}
		errno = errno_tmp;
		printf("\n");
		free(line);
		return (NULL);
	}
	errno = errno_tmp;
	return (line);
}
