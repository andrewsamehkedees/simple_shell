#include "shell.h"

/**
 * deshistofil - gets the history file
 * @info: parameter struct
 * Return: allocated string containg history file
 */

char *deshistofil(info_t *info)
{
	char *buf, *dir;

	dir = gettheenvi(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	stringcp(buf, dir);
	stringconc(buf, "/");
	stringconc(buf, HIST_FILE);
	return (buf);
}

/**
 * sethistofil - creates a file, or appends to an existing file
 * @info: the parameter struct
 * Return: 1 or -1
 */
int sethistofil(info_t *info)
{
	ssize_t fd;
	char *filename = deshistofil(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		putesfed(node->str, fd);
		putefed('\n', fd);
	}
	putefed(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * getthehisto - reads history from file
 * @info: the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int getthehisto(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = deshistofil(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			makethehisto(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		makethehisto(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delthenodeatind(&(info->history), 0);
	arrangethehiso(info);
	return (info->histcount);
}

/**
 * makethehisto - adds entry to a history linked list
 * @info: Structure containing potential arguments.
 * @buf: buffer
 * @linecount: the history linecount
 * Return: Always 0
 */
int makethehisto(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	addthenodeend(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * arrangethehiso - renumbers the history linked list after changes
 * @info: Structure containing potential arguments.
 * Return: the new histcount
 */
int arrangethehiso(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
