#include "shell.h"

/**
 * testcmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 * Return: 1 or 0
 */
int testcmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * doubchar - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *doubchar(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * finpath - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH
 * @cmd: the cmd
 * Return: full path of cmd if found or NULL
 */
char *finpath(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, theposi = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && begwith(cmd, "./"))
	{
		if (testcmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = doubchar(pathstr, theposi, i);
			if (!*path)
				stringconc(path, cmd);
			else
			{
				stringconc(path, "/");
				stringconc(path, cmd);
			}
			if (testcmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			theposi = i;
		}
		i++;
	}
	return (NULL);
}
