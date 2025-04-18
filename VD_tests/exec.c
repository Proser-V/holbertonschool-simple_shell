#include "shell.h"

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
 * @cmd_count: The number of command passed to the program.
 * @nom_prog: The name of the program (Shell) from main.
 *
 * Return: 1 on succes execution, -1 on error.
 */

int execute(char **args, int cmd_count, char *nom_prog)
{
	pid_t pid; /* The ID of the process */
	char *command_path;
	int status;

	if (is_builtin(args) != -1) /* Check if the command is built-in */
		return (1); /* Built-in command executed */
	command_path = find_command_path(args[0]); /* Check if the command exist */
	if (command_path == NULL) /* Command not found */
	{
		fprintf(stderr, "%s: %d: %s: not found\n", nom_prog, cmd_count, args[0]);
		return (1);
	}
	pid = fork(); /* Command found, process duplication */
	if (pid == -1) /* Duplication error */
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0) /* The current process is the child */
	{
		if ((execve(command_path, args, environ)) == -1)
			perror(args[0]);

		exit(EXIT_FAILURE);
	}
	else /* The current process is the parent */
	{
		waitpid(pid, &status, 0); /* Wait for the child to ends */
		free(command_path);
	}
	return (1); /* Successfull execution */
}
