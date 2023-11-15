#include "shell.h"

/**
 * myqui - exits the shell
 * @info: Structure containing potential arguments.
 *  Return: 0 or 1 or -2
 */
int myqui(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = errortoint(info->argv[1]);
		if (exitcheck == -1)
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
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = gettheenvi(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = gettheenvi(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
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
		chdir_ret = /* TODO: what shoulad this be as dasd? */
			chdir((dir = gettheenvi(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
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
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
