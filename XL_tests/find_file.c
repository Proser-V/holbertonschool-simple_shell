#include "ss_shell.h"

/**
 * find_file - finds out if the file exists in the path
 * @file: file to be searched for
 * @env: environment
 * Return: if found, the absolute path of the file; NULL if not found
 */

char *find_file(char *file, char **env)
{
	char **paths;
	int stat_out = -1;
	char *new_path;
	int path_len;
	int cmd_len;
	int i;
	struct stat stat_st;

	paths = getpath(env);
	if (!paths)
	{
		fprintf(stderr, "PATH environment variable not found\n");
		return (NULL);
	}
	for (i = 0; stat_out == -1 && paths[i] != NULL; ++i)
	{
		if (i > 0)
			free(new_path);
		path_len = strlen(paths[i]);
		cmd_len = strlen(file);
		new_path = malloc((path_len + cmd_len + 1) * sizeof(char));
		if (!new_path)
		{
			perror("malloc new path");
			return (NULL);
		}
		strcpy(new_path, paths[i]);
		new_path = strcat(new_path, "/");
		new_path = strcat(new_path, file);
		stat_out = stat(new_path, &stat_st);
	}
	if (paths[i] != NULL)
		return (new_path);
	perror("stat");
	return (NULL);
}
