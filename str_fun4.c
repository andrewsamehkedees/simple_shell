#include "shell.h"

/**
 * **strintowor - splits a string into words. Repeat delimiters are ignored
 * @str: the string
 * @d: the delimeter string
 * Return: pointer or NULL
 */

char **strintowor(char *str, char *d)
{
	int i, j, k, m, worlen = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!isdel(str[i], d) && (isdel(str[i + 1], d) || !str[i + 1]))
			worlen++;

	if (worlen == 0)
		return (NULL);
	s = malloc((1 + worlen) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < worlen; j++)
	{
		while (isdel(str[i], d))
			i++;
		k = 0;
		while (!isdel(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strintowor2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer
 */
char **strintowor2(char *str, char d)
{
	int i, j, k, m, worlen = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			worlen++;
	if (worlen == 0)
		return (NULL);
	s = malloc((1 + worlen) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < worlen; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
