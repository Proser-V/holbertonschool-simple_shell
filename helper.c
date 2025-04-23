#include "shell.h"

/**
 * _atoi - extract a number from a string
 * @s: source string
 * Return: the number value or 0 if no number in the string
 */

int _atoi(char *s)
{
	int i = 0;
	unsigned int num = 0;
	int sign = 1;
	int ok = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign = sign * -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			num = (num * 10) + (s[i] - '0');
			ok = 1;
		}
		else if (ok == 1)
			break;

		i++;
	}
	if (ok == 0)
		return (0);

	else
		return (num * sign);
}

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
 * isposnumber - determines if a string is a positive number
 * @num_str: input string to examine
 * Return: 0 if it is not a positive number, 1 if it is
 */

int isposnumber(char *num_str)
{
	size_t i = 0;

	while (num_str[i] >= '0' && num_str[i] <= '9' && num_str[i] != '\0')
		++i;
	if (strlen(num_str) == i)
		return (1);
	else
		return (0);
}
