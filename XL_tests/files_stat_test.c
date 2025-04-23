#include "XL_main.h"

/**
* file_stat - tests if files exist
* @argc: argument count
* @argv: argument vector
* Return: nothing
*/

void file_stat(int argc, char *argv[])
{
	unsigned int i;
	struct stat st;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s path_to_file ...\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	i = 1;
	while (argv[i])
	{
		printf("%s:", argv[i]);
		if (stat(argv[i], &st) == 0)
		{
			printf(" FOUND\n");
		}
		else
		{
			printf(" NOT FOUND\n");
		}
		i++;
	}
}
