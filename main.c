#include "shell.h"

/**
 * print_prompt - helper function to print a prompt
 *
 * Return: nothing (void)
 */

void print_prompt(void)
{
	if (isatty(STDIN_FILENO) == 1) /* Check for interactive mode = yes */
	{
		printf("$ "); /* Prompt to print */
		fflush(stdout); /* Force immediate display of the prompt */
	}
}

/**
 * no_inter - Handle non-interractive mode of shell.
 *
 * @args: Tokenized string passed by the user.
 * @line: String containing the full command passed by the user.
 * @cmd_cnt: The number of commands passed to the program.
 * @nom_cmd: The name of the program (Shell) from main.
 * @e_stat: Pointer to the exit status to set.
 *
 * Return: 0 if all commands succeeded, or the last error code if a command
 *			failed.
 */

int no_inter(char **args, char *line, char *nom_cmd, int cmd_cnt, int *e_stat)
{
	if ((isatty(STDIN_FILENO) == 0))
	{
		while (1)
		{
			line = read_line(); /* Get the line from the standard input */
			if (line == NULL)
				break;
			cmd_cnt++; /* Count the number of command passed */
			args = split_line(line); /* Tokenize the line */
			if (args != NULL && args[0] != NULL)
			{
				if (strcmp(args[0], "exit") == 0) /* Exit called ? */
				{
					if (args[1] == NULL) /* Exit without argument */
					{
						free(args);
						free(line);
						return (*e_stat);
					} /* Exit the loop if "exit" called without argument */
					*e_stat = exit_built(line, args, cmd_cnt, nom_cmd);
					break;
				}
				execute(args, cmd_cnt, nom_cmd, e_stat);
			}
			free(args);
			free(line);
		}
	}
	return (*e_stat);
}

/**
 * main - Entry point to a simple shell program.
 *
 * Description: This program can be used to interactively execute commands and
 *				display their outputs.
 *              It prints a prompt and initializes a loop that will execute the
 *              input command, display results, and print a new prompt.
 *				The loop will stop when a non-zero value is returned
 *              for the exit_status variable by the execution of a command.
 *              This program can also be executed in non-interactive mode if an
 *              input (a command) is passed directly to it (e.g., via a pipe).
 *
 * @argc: Number of arguments passed to the program.
 * @argv: Array of strings containing the arguments passed to the program.
 *
 * Return: 0 if all commands succeeded, or the last error code if a command
 *			failed.
 */

int main(__attribute__((unused)) int argc, char *argv[])
{
	int exit_status = 0;
	char **args = NULL;
	char *line = NULL;
	int command_count = 0;

	exit_status = no_inter(args, line, argv[0], command_count, &exit_status);
	if ((isatty(STDIN_FILENO) == 1))
		while (1)
		{
			print_prompt();
			line = read_line(); /* Get the line from the standard input */
			if (line == NULL) /* EOF (Ctrl+D) */
				break;
			command_count++; /* Count the number of command passed */
			args = split_line(line); /* Tokenize the line */
			if (args != NULL && args[0] != NULL)
			{
				if (strcmp(args[0], "exit") == 0) /* Exit called ? */
				{
					if (args[1] == NULL) /* Exit without argument */
					{
						free(args);
						free(line);
						return (exit_status);
					} /* Exit the loop if "exit" called without argument */
					exit_status = exit_built(line, args, command_count, argv[0]);
					continue; /* Continue the loop on exit error */
				}
				execute(args, command_count, argv[0], &exit_status);
			}
			free(args);
			free(line);
		}
	return (exit_status);
}
