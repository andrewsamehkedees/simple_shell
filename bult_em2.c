#include "shell.h"

/**
 * myhisto - displays the history list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int myhisto(info_t *info)
{
	despthelist(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: 0 or 1
 */
int unset_alias(info_t *info, char *str)
{
	char *x, c;
	int ret;

	x = stringchar(str, '=');
	if (!x)
		return (1);
	c = *x;
	*x = 0;
	ret = delthenodeatind(&(info->alias),
		thenodeloc(info->alias, thenodstar(info->alias, str, -1)));
	*x = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: 0 or 1
 */
int set_alias(info_t *info, char *str)
{
	char *x;

	x = stringchar(str, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (addthenodeend(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: 0 or 1
 */
int print_alias(list_t *node)
{
	char *x = NULL, *a = NULL;

	if (node)
	{
		x = stringchar(node->str, '=');
		for (a = node->str; a <= x; a++)
			_xutchar(*a);
		_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * myali - mimics the alias builtin
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int myali(info_t *info)
{
	int i = 0;
	char *x = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		x = stringchar(info->argv[i], '=');
		if (x)
			set_alias(info, info->argv[i]);
		else
			print_alias(thenodstar(info->alias, info->argv[i], '='));
	}

	return (0);
}
