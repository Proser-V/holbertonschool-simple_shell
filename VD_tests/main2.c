#include "shell.h"

int exit_built(char *line, char **args, int cmd_count, char *nom_prog)
{
	int code = 0;

	code = _atoi(args[1]);
	if (code == 0 && args[1] != NULL)
	{
		fprintf(stderr, "%s: %d: %s: Illegal number: %s\n"
			, nom_prog, cmd_count, args[0], args[1]);
		code = 2;
		free(args);
		free(line);
		return (code);
	}
	free(args);
	free(line);
	exit(code);
}

/**
 * main - Entry point - prints a prompt and initialize the loop.
 *
 * Description: This function takes the arguments passed with the program.
 *              Besides, the pshell loop is initialized in this function,
 *              printing the prompt, and calling the backbone functions of
 *              the program. The loop will continue until a 0 is returned
 *              for the exit_status variable by the execution of a command.
 *              Finaly, this function works if a command is passed in a
 *              non-interractive or interractive way.
 *
 * @argc: Number of arguments passed to the program.
 * @argv: Array of string containing the arguments passed to the program.
 *
 * Return: Always 0 (success).
 */

int main(int argc, char *argv[])
{
	int exit_status = 0, command_count = 0;
	char **args;
	char *line;

	(void)argc; /* argc unused */
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1) /* Check for interractive mode = yes */
		{
			printf("$ "); /* Prompt to print */
			fflush(stdout); /* Force immediate display of the prompt */
		}
		line = read_line(); /* Get the line from the standard input */
		if (line == NULL && isatty(STDIN_FILENO == 1)) /* EOF (Ctrl+D) */
			break;
		command_count++; /* Count the number of command passed */
		args = split_line(line); /* Tokenize the line */
		if (args != NULL && args[0] != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				if (args[1] == NULL)
				{
					free(args);
					free(line);
					return (exit_status); /* Exit the loop if exit command called */
				}
				exit_status = exit_built(line, args, command_count, argv[0]);
				continue;
			}
			execute(args, command_count, argv[0], &exit_status);
		}
		free(args);
		free(line);
		if (isatty(STDIN_FILENO) == 0)
			break;
	}
	return (exit_status);
}
