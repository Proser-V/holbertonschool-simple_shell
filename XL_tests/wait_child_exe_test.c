#include "XL_main.h"

/**
 * wait_child_exe_test - executes a program, waits for child when necessary,
 * and ends the process
 * Return: nothing
 */

void wait_child_exe_test(void)
{
	int wait_status;
	char *sub_cmd_argv[] = {"/bin/ls", "-la", ".", NULL};
	pid_t process_id = getpid(), parent_id = getppid(), is_child, wait_out;

	printf("Process ID is [%i]\n", process_id);
	printf("Parent process ID is [%i]\nBefore fork\n", parent_id);
	is_child = fork();
	if (is_child == -1)
	{
		perror("fork error:");
		exit(EXIT_FAILURE);
	}
	if (is_child != 0)
		wait_out = wait(&wait_status);
		/*wait_out = waitpid(is_child, &wait_status, 0);*/
	if (wait_out == -1)
	{
		perror("wait error");
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
	if (is_child == 0 && execve(sub_cmd_argv[0], sub_cmd_argv, NULL) == -1)
	{
		perror("Error:");
		exit(EXIT_FAILURE);
	}
	printf("After execve (which will not happen if execve succeds)\n");
	process_id = getpid();
	parent_id = getppid();
	printf("Current process ID is [%i]\n", process_id);
	printf("Current parent process ID is [%i]\n", parent_id);
}
