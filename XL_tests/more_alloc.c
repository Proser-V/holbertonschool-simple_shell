#include "shell.h"

/**
 * more_alloc - allocates memory for an array of pointers, copies the array's
 * data into it, and frees previously occupied memory
 * @array_ptr: pointer to initialy allocated memory
 * @oldsize: number of elements of the array
 * @newsize: memory to allocate for new array
 * Return: pointer to the new array
 */

void **more_alloc(void **array_ptr, size_t oldsize, size_t newsize)
{
	void **new_ptr;
	size_t i;

	if (newsize > oldsize)
	{
		new_ptr = malloc(sizeof(char *) * newsize);
		if (new_ptr == NULL)
		{
			perror("malloc failure");
			exit(errno);
		}
		for (i = 0; i < oldsize; ++i)
			new_ptr[i] = array_ptr[i];
		free(array_ptr);

		return (new_ptr);
	}
	else
	{
		fprintf(stderr, "more_alloc needs newsize > oldsize");
		exit(EXIT_FAILURE);
	}
}
