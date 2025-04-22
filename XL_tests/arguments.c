#include "XL_main.h"

/**
 * arguments_test - tests the argc and argv functionality of main
 * @argc: argument count
 * @argv: argument vector
 * Return: nothing
 */

void arguments_test(int argc, char **argv)
{
	int i;

	printf("argc = %i\n", argc);
	printf("Print the arguments using argc\n");
	for (i = 0; i < argc; ++i)
		printf("\targv[%i] = %s\n", i, argv[i]);
	printf("Print arguments without using argc\n");
	for (i = 0; argv[i] != NULL; ++i)
		printf("\targv[%i] = %s\n", i, argv[i]);
}
