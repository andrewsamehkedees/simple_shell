#include "shell.h"

/**
 * myeenvi - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int myeenvi(info_t *info)
{
	displistofstr(info->env);
	return (0);
}

/**
 * gettheenvi - gets the value of an environ variable
 * @info: Structure containing potential arguments.
 * @name: env var name
 * Return: the value
 */
char *gettheenvi(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = begwith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * setmyeenvi - Initialize a new environment variable or modify
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int setmyeenvi(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (setmyeenvir(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetmyeenvi - Remove an environment variable
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int unsetmyeenvi(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetmyeenvir(info, info->argv[i]);

	return (0);
}

/**
 * mosteenvilist - most env linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int mosteenvilist(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addthenodeend(&node, environ[i], 0);
	info->env = node;
	return (0);
}
