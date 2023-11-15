#include "shell.h"

/**
 * gettheenvir - returns the string array copy of our environ
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
char **gettheenvir(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = thelisttostr(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unsetmyeenvir - Remove an environment variable
 * @info: Structure containing potential arguments.
 * @var: the string
 * Return: 0 or 1
 */
int unsetmyeenvir(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = begwith(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delthenodeatind(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * setmyeenvir - Initialize a new environment variable or modify
 * @info: Structure containing potential arguments
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int setmyeenvir(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	stringcp(buf, var);
	stringconc(buf, "=");
	stringconc(buf, value);
	node = info->env;
	while (node)
	{
		p = begwith(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addthenodeend(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
