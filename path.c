#include "shell.h"

/**
 * find_command_path - A function that find if a command exist.
 *
 * Description: This function checks if the command passed is in the "PATH"
 *              directories and if it is executable.
 *
 * @command: The first argument from the input - the command passed.
 * @exit_status: Pointer to the exit status to set.
 *
 * Return: A pointer to a string containing the absolute path of the command
 *         to execute. The command if an absolute path or an executable was
 *         passed in the input. Or NULL if the command was not found.
 */

char *find_command_path(char *command, int *exit_status)
{
	char *path, *dir;
	char buff[1024]; /* Local buffer */

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, F_OK) == 0) /* File found */
		{
			if (access(command, X_OK) == 0) /* Executable command found */
				return (strdup(command));
			*exit_status = 126; /* File found but permission denied */
			return (NULL);
		}
		else /* File not found */
		{
			*exit_status = 127;
			return (NULL);
		}
	}
	path = _getpath(); /* Get the PATH string */
	if (path == NULL || path[0] == '\0')
	{
		free(path);
		return (NULL);
	}
	dir = strtok(path, ":"); /* Tokenize the PATH directories */
	while (dir != NULL) /* Check if the command is found in each directory */
	{
		strcpy(buff, dir);
		strcat(buff, "/");
		strcat(buff, command);
		errno = 0; /* errno set to 0 in loop to avoid making a false error */
		if (access(buff, F_OK | X_OK) == 0) /* Command found */
		{
			free(path);
			return (strdup(buff)); /* Memory allocated dynamicaly for buff */
		} /* Return a copy of the full path of the command */
		dir = strtok(NULL, ":");
	}
	free(path);
	return (NULL); /* Command not found */
}
