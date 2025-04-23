#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
* main - check code
* Return: 0
*/
int main(void)
{
	pid_t pid = fork();
	int status;

	if (pid < 0)
	{
		perror("fork failed");
		exit(1);
	}
	else if (pid == 0)
	{
		printf("Child process\n");
		printf("Child process\n");
		printf("Child process\n");
		printf("Child process\n");
		exit(0);
	}
	else
	{
		printf("Parent process\n");
		printf("Parent process\n");
		printf("Parent process\n");
		printf("Parent process\n");
		printf("Parent process\n");
		printf("Parent process\n");
		printf("Parent process\n");
		wait(&status);
	}

	return (0);
}
