#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * stringcomp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 * Return: -v or +v or 0
 */
int stringcomp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * begwith - checks if needle starts with haystack
 * @haystack: string
 * @needle: the substring
 * Return: address or NULL
 */
char *begwith(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * stringconc - concatenates two strings
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *stringconc(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
