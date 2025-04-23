#include "ss_shell.h"

/**
 * getpath - looks in the environment and returns an array of paths
 * @env: NULL-terminated array of environment variables
 * Return: array of paths (pointer array), or NULL if it doesn't find the PATH
 * evironment variable in envp
 */

char **getpath(char **env)
{
	char **paths;
	int i = 0, j;
	char *delimiter = "=:";
	size_t n_paths;
	char *path_key = "PATH=";
	char *tok;
	char *env_dup;

	while (env[i] != NULL)
	{
		if (strncmp(env[i], path_key, 5) == 0)
		{
			env_dup = strdup(env[i]);
			tok = strtok(env_dup, delimiter);
			for (n_paths = 0; tok != NULL; ++n_paths)
				tok = strtok(NULL, delimiter);
			free(tok);
			paths = malloc(n_paths * sizeof(char *));
			if (!paths)
			{
				perror("malloc: tokenized PATH");
				exit(EXIT_FAILURE);
			}
			env_dup = strdup(env[i]);
			paths[0] = strtok(env_dup, delimiter);
			paths[0] = strtok(NULL, delimiter);
			for (j = 1; paths[j - 1] != NULL; ++j)
				paths[j] = strtok(NULL, delimiter);
			return (paths);
		}
		++i;
	}
	return (NULL);
}
