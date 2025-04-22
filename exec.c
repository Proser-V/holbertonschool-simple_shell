#include "shell.h"

/**
 * handle_builtin - Helper function to handle built-in commands.
 *
 * @args: Tokenized command arguments.
 * @exit_status: Pointer to the exit status to set.
 *
 * Return: 0 if no built-in command is found, else the exit status.
 */

int handle_builtin(char **args, int *exit_status)
{
	int builtin_status;

	builtin_status = is_builtin(args);
	if (builtin_status != -1) /* Check if the command is built-in */
	{
		*exit_status = builtin_status; /* 0 if execution with no error */
		return (*exit_status); /* New exit code passed to main */
	}
	return (-1);  /* No built-in found */
}

/**
 * execute - A function that execute the command passed.
 *
 * Description: This function checks if the command passed is in the "PATH"
 *              (pre-implemented commands) or if this is a built-in function
 *              to call. If this is a built-in, just call the function and
 *              come back to the main function. If not, create a child process
 *              to handle the command and arguments. Meanwhile, the main
 *              process wait for the child to return a finish signal to
 *              continue.
 *
 * @args: Tokenized string passed by the user.
 * @cmd_count: The number of commands passed to the program.
 * @nom_prog: The name of the program (Shell) from main.
 * @exit_status: Pointer to the exit status to set.
 *
 * Return: 1 on succes execution, -1 on error.
 */

void execute(char **args, int cmd_count, char *nom_prog, int *exit_status)
{
	pid_t pid; /* The ID of the process */
	char *command_path;
	int pid_status;

	if (handle_builtin(args, exit_status) != -1)
		return; /* Executed built-in return to main */
	/* No built-in, go check for command path */
	command_path = find_command_path(args[0]); /* Check if the command exist */
	if (command_path == NULL) /* Command not found */
	{
		fprintf(stderr, "%s: %d: %s: not found\n", nom_prog, cmd_count, args[0]);
		*exit_status = 127; /* Set the value return of exit */
		return;
	}

	pid = fork(); /* Command found, process duplication */
	if (pid == -1) /* Duplication error */
	{
		perror("fork");
		*exit_status = 1; /* Standard error value */
		free(command_path);
		return;
	}
	if (pid == 0) /* The current process is the child */
	{
		if ((execve(command_path, args, environ)) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, &pid_status, 0); /* Wait for the child to ends */
	if (WIFEXITED(pid_status) == 1) /* Normal child ending is true? */
		*exit_status = WEXITSTATUS(pid_status); /* return child exit status */
	else
		*exit_status = 1; /* Else, standard error value */
	free(command_path);
	return; /* Successfull father process execution */
}
