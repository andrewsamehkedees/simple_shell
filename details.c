#include "shell.h"

/**
 * cleardetai - initializes info_t struct
 * @info: struct address
 */
void cleardetai(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setdetai - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void setdetai(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strintowor(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = stringdoub(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		reptheali(info);
		repthevar(info);
	}
}

/**
 * releasedetai - frees info_t struct fields
 * @info: struct address
 * @all: true if freed
 */
void releasedetai(info_t *info, int all)
{
	frfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			releasethelist(&(info->env));
		if (info->history)
			releasethelist(&(info->history));
		if (info->alias)
			releasethelist(&(info->alias));
		frfree(info->environ);
			info->environ = NULL;
		befree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
