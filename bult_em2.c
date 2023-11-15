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
	char *p, c;
	int ret;

	p = stringchar(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delthenodeatind(&(info->alias),
		thenodeloc(info->alias, thenodstar(info->alias, str, -1)));
	*p = c;
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
	char *p;

	p = stringchar(str, '=');
	if (!p)
		return (1);
	if (!*++p)
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
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = stringchar(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
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
	char *p = NULL;
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
		p = stringchar(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(thenodstar(info->alias, info->argv[i], '='));
	}

	return (0);
}
