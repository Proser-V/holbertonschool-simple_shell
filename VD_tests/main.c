#include "shell.h"

/**
 * main - Entry point - prints a prompt and initialize the loop.
 *
 * Description: This function takes the arguments passed with the program.
 *              Besides, the pshell loop is initialized in this function,
 *              printing the prompt, and calling the backbone functions of
 *              the program. The loop will continue until a 0 is returned
 *              for the status variable by the execution of a command.
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
	int status;
	char **args;
	char *line;
	int command_count = 0;

	(void)argc; /* argc unused */

	if (isatty(STDIN_FILENO) == 1) /* Check for interractive mode */
	{
		do { /* Interractive mode */
			printf("$ "); /* Prompt to print */
			fflush(stdout); /* Force immediate display of the prompt */

			line = read_line(); /* Get the line from the standard input */
			args = split_line(line); /* Tokenize the line */
			command_count++; /* Count the number of command passed */
			if (args != NULL && args[0] != NULL)
				status = execute(args, command_count, argv[0]);
			/* Execute the command if found */
			free(args);
			free(line);
		} while (status != 0);
	}
	else /* Same actions in non-interractive mode */
	{ /* No prompt */
		line = read_line();
		args = split_line(line);
		if (args != NULL && args[0] != NULL)
			execute(args, command_count, argv[0]);

		free(args);
		free(line);
	}
	return (0);
}
