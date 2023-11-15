#include "shell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 * Return: void
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character
 * Return: 1 or -1
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * putefed - writes the character c to given fd
 * @c: The character
 * @fd: The filedescriptor
 * Return: 1 or -1
 */
int putefed(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *putesfed - prints an input
 * @str: the string
 * @fd: the filedescriptor
 * Return: the number of chars put
 */
int putesfed(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += putefed(*str++, fd);
	}
	return (i);
}
