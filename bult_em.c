#include "shell.h"

/**
 * myqui - exits the shell
 * @info: Structure containing potential arguments.
 *  Return: 0 or 1 or -2
 */
int myqui(info_t *info)
{
	int testexit;

	if (info->argv[1])
	{
		testexit = errortoint(info->argv[1]);
		if (testexit == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = errortoint(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * myloca - changes the current directory of the process
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int myloca(info_t *info)
{
	char *s, *x, buffer[1024];
	int changx;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		x = gettheenvi(info, "HOME=");
		if (!x)
			changx = chdir((x = gettheenvi(info, "PWD=")) ? x : "/");
		else
			changx = chdir(x);
	}
	else if (stringcomp(info->argv[1], "-") == 0)
	{
		if (!gettheenvi(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(gettheenvi(info, "OLDPWD=")), _putchar('\n');
		changx = chdir((x = gettheenvi(info, "OLDPWD=")) ? x : "/");
	}
	else
		changx = chdir(info->argv[1]);
	if (changx == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		setmyeenvir(info, "OLDPWD", gettheenvi(info, "PWD="));
		setmyeenvir(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * mysupp - changes the current directory
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int mysupp(info_t *info)
{
	char **arguarr;

	arguarr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arguarr);
	return (0);
}
