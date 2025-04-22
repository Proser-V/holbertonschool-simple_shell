#include "shell.h"

/**
 * find_command_path - A function that find if a command exist.
 *
 * Description: This function checks if the command passed is in the "PATH"
 *              directories and if it is executable.
 *
 * @command: The first argument from the input - the command passed.
 *
 * Return: A pointer to a string containing the absolute path of the command
 *         to execute. The command if an absolute path or an executable was
 *         passed in the input. Or NULL if the command was not found.
 */

char *find_command_path(char *command)
{
	char *path, *path_cpy = NULL, *dir;
	char buff[1024];
	int index = 0;

	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
		return (command);
	/* Return the command if the command passed already have an absolute path */
	/* or if it is already an executable */
	path = "PATH="; /* getenv rewrite */
	while (strncmp(environ[index], path, 5) != 0)
		index++;

	path = environ[index];
	for (index = 0; index < 5; index++)
		path++;
	path_cpy = strdup(path); /* getenv end */

	dir = strtok(path_cpy, ":"); /* Tokenize the PATH directories */

	while (dir != NULL) /* Check if the command is found in each directory */
	{
		strcpy(buff, dir);
		strcat(buff, "/");
		strcat(buff, command);
		errno = 0; /* errno set to 0 in loop to avoid making a false error */
		if (access(buff, F_OK | X_OK) == 0) /* Command found */
		{
			free(path_cpy);
			return (strdup(buff));
		}
		dir = strtok(NULL, ":");
	}
	free(path_cpy);
	return (NULL); /* Command not found */
}
