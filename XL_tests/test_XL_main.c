#include "XL_main.h"

/**
 * main - check the code
 * @argc: argument count
 * @argv: argument vector
 * @envp: pointer to environment variables
 * Return: 0 if success
 */

int main(int argc, char *argv[], char *envp[])
{
	char **paths;
	int i;

	/* pid_ppid_test(); */
	/* arguments_test(argc, argv); */
	/* read_split_line(); */
	/* execute_prog_test(); */
	/* fork_exe_prog_test(); */
	/* wait_child_exe_test(); */
	/* fork_wait_execve(); */
	/* file_stat(argc, argv); */
	(void)argc;
	(void)argv;
	/* printenv_environ_test(envp); */
	paths = getpath(envp);
	if (!paths)
	{
		fprintf(stderr, "no PATH found");
		return (-1);
	}
	for (i = 0; paths[i] != NULL; ++i)
	{
		printf("path[%i] = %s\n", i, paths[i]);
	}
	return (0);
}
