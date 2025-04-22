#include "XL_main.h"

/**
 * execute_prog_test - executes a program and ends the process
 * Return: nothing
 */

void execute_prog_test(void)
{
	char *sub_cmd_argv[] = {"/bin/ls", "-la", ".", NULL};
	pid_t process_id = getpid();
	pid_t parent_id = getppid();
	pid_t is_child;
	/* char *sub_cmd_argv[] = {"/bin/non_prog", "-la", ".", NULL}; */

	printf("Process ID is [%i]\n", process_id);
	printf("Parent process ID is [%i]\n", parent_id);
	printf("Before fork\n");
	is_child = fork();
	if (is_child == -1)
	{
		perror("Error:");
		exit(EXIT_FAILURE);
	}
	printf("After fork\n");
	if (is_child == 0)
		printf("Current process is child\n");
	else if (is_child != 0)
		printf("Current process is NOT child\n");
	process_id = getpid();
	parent_id = getppid();
	printf("Current process ID is [%i]\n", process_id);
	printf("Current parent process ID is [%i]\n", parent_id);
	printf("Before exercve\n");
	if (is_child == 0)
	{
		if (execve(sub_cmd_argv[0], sub_cmd_argv, NULL) == -1)
		{
			perror("Error:");
		}
	}
	printf("After execve (which will not happen if execve succeds)\n");
	process_id = getpid();
	parent_id = getppid();
	printf("Current process ID is [%i]\n", process_id);
	printf("Current parent process ID is [%i]\n", parent_id);
}
