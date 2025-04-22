#include "XL_main.h"

/**
 * fork_wait_execve - executes the commans ls -l /tmp in 5 different child
 * processes, one after the other
 * Return: nothing
 */

void fork_wait_execve(void)
{
	int wait_status, i = 0;
	char *sub_cmd_argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	pid_t process_id = getpid(), parent_id = getppid(), child_pid = 1, wait_out;

	printf("Process ID is [%i]\n", process_id);
	printf("Parent process ID is [%i]\nBefore fork\n", parent_id);
	while (i < 5 && child_pid != 0)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork error:");
			exit(EXIT_FAILURE);
		}
		if (child_pid != 0)
		{
			/* wait_out = wait(&wait_status); */
			wait_out = waitpid(child_pid, &wait_status, 0);
			if (wait_out == -1)
			{
				perror("wait error");
				exit(EXIT_FAILURE);
			}
			++i;
		}
	}
	printf("After fork\n");
	if (child_pid == 0)
		printf("Current process is child\n");
	else if (child_pid != 0)
		printf("Current process is NOT child\n");
	process_id = getpid();
	parent_id = getppid();
	printf("Current process ID is [%i]\n", process_id);
	printf("Current parent process ID is [%i]\n", parent_id);
	printf("Before exercve\n");
	if (child_pid == 0 && execve(sub_cmd_argv[0], sub_cmd_argv, NULL) == -1)
	{
		perror("Error:");
		exit(EXIT_FAILURE);
	}
	printf("After execve (which will not happen if execve succeeds)\n");
	printf("or if execve is never called\n");
	process_id = getpid();
	parent_id = getppid();
	printf("Current process ID is [%i]\n", process_id);
	printf("Current parent process ID is [%i]\n", parent_id);
}
