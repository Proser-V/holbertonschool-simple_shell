#include "shell.h"

/**
 * read_line - read the line from the standard input.
 *
 * Description: This function get the line from the standard input and put
 *              it in a buffer.
 *
 * Return: A string containing the user's input.
 */

char *read_line(void)
{
	char *line;
	size_t buff_size = SHELL_READ_BUFFER;

	line = malloc(sizeof(char) * buff_size); /* Buffer memory allocation */
	if (line == NULL)
	{
		fprintf(stderr, "Allocation failed\n");
		exit(EXIT_FAILURE);
	}
	errno = 0; /* Set errno to 0 to isolate EOF management from getline */
	if (getline(&line, &buff_size, stdin) == -1) /* Put the line in a buffer */
	{ /* and checks for errors */
		if (errno != 0) /* If (getline = -1 and errno = 0) -> EOF */
		{
			perror("getline failed");
		}
		else
			printf("\n");
		free(line);
		exit(EXIT_FAILURE);
	}
	return (line);
}
