#include "shell.h"

/**
 * testchain - test if current char is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 or 0
 */
int testchain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * testthechain - checks if we should continue based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void testthechain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * reptheali - replaces an aliases in the string
 * @info: the parameter struct
 * Return: 1 or 0
 */
int reptheali(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = thenodstar(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = stringchar(node->str, '=');
		if (!p)
			return (0);
		p = stringdoub(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * repthevar - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 or 0
 */
int repthevar(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!stringcomp(info->argv[i], "$?"))
		{
			repthestr(&(info->argv[i]),
				stringdoub(convint(info->status, 10, 0)));
			continue;
		}
		if (!stringcomp(info->argv[i], "$$"))
		{
			repthestr(&(info->argv[i]),
				stringdoub(convint(getpid(), 10, 0)));
			continue;
		}
		node = thenodstar(info->env, &info->argv[i][1], '=');
		if (node)
		{
			repthestr(&(info->argv[i]),
				stringdoub(stringchar(node->str, '=') + 1));
			continue;
		}
		repthestr(&info->argv[i], stringdoub(""));

	}
	return (0);
}

/**
 * repthestr - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 or 0
 */
int repthestr(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
