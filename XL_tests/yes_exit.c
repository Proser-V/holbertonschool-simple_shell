#include "ss_shell.h"

/**
 * yes_exit - exits the interactive mode if first input word is exit
 * @first_token: first token of the input string
 * Return: 1 if it is exit, 0 otherwise
 */

int yes_exit(char *first_token)
{
	if (strcmp(first_token, "exit") == 0)
		return (0);
	return (1);
}
