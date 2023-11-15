#include "shell.h"

/**
 * befree - frees a pointer and NULLs the address
 * @ptr: pointer
 * Return: 1 or 0
 */
int befree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
