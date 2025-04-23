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