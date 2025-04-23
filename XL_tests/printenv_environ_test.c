#include "XL_main.h"

/**
 * printenv_environ_test - prints the environment variables using the global
 * variable environ
 * @envp: pointer to environment
 * Return: nothing
 */

void printenv_environ_test(char **envp)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		++i;
	}
	i = 0;
	while (i < 5 && environ[i] != NULL)
	{
		printf("address of envp[%i]: %p\n", i, envp[i]);
		printf("address of environ[%i]: %p\n", i, environ[i]);
		printf("------------------------------\n");
		++i;
	}
	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		++i;
	}
	printf("------------------------------\n");
	envp[0] = "hel";
	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		++i;
	}
	printf("%s\n", envp[0]);
	environ[0] = "XLELL=hello";
	printf("%s\n", environ[0]);
	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		++i;
	}
}
