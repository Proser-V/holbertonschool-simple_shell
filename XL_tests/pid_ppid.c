#include "XL_main.h"

/**
 * pid_ppid_test - tests the getpid system call
 * Return: nothing
 */

void pid_ppid_test(void)
{
	pid_t my_pid, my_p_pid;

	my_pid = getpid();
	my_p_pid = getppid();
	printf("Process ID: %u\n", my_pid);
	printf("Parent process ID: %u\n", my_p_pid);
}
