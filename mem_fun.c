#include "shell.h"

/**
 **memoset - fills memory with a constant byte
 *@s: pointer
 *@b: byte
 *@n: amount of bytes
 *Return: (s) a pointer to the memory area s
 */
char *memoset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * frfree - frees a string of strings
 * @pp: strings
 */
void frfree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * therealo - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: previous block
 * @new_size: new block
 * Return: pointer to da ol'block nameen.
 */
void *therealo(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
