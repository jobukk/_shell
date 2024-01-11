#include "shell.h"

/**
 * _myexit - exits shell
 * @info: Structure
 * Return:exit status
 *
 */
int _myexit(info_t *info)
{
int exitcheck = (info->argv[1] != NULL) ? _erratoi(info->argv[1]) : -1;

if (exitcheck == -1)
{
info->status = 2;
custom_print_error(info);
return (1);
}

info->err_num = exitcheck;
return ((info->argv[1] != NULL) ? -2 : -2);
}

/**
 * custom_print_error -  error message
 * @info: Structure
 * Return:  0
 */

void custom_print_error(info_t *info)
{
print_error(info, "not a good number: %s\n", info->argv[1]);
}





/**
 * _mycd - cd of the process
 * @info: Structure
 * Return:  0
 */
int _mycd(info_t *info)
{
char *dir, buffer[1024];
int chdir_ret;

if (!(getcwd(buffer, 1024)))
{
_puts("TODO: >>getcwd failure emsg here<<\n");
return (0);
}

if (info->argv[1] == NULL)
{
dir = _getenv(info, "HOME=");
dir = (dir == NULL) ? ((_getenv(info, "PWD=") ?: "/")) : dir;
chdir_ret = chdir(dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (_getenv(info, "OLDPWD="))
_puts(_getenv(info, "OLDPWD="));
else
_puts(buffer), _putchar('\n');
chdir_ret = chdir((_getenv(info, "OLDPWD=") ?: "/"));
return ((!_getenv(info, "OLDPWD=")) ? 1 : 0);
}
else
{
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
print_error(info, "can't cd to ");
_eputs(info->argv[1]);
_eputchar('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, 1024));
}
}
return (0);
}

/**
 * _myhelp - cd of the process
 * @info: Structure
 * Return: 0
 */
int _myhelp(info_t *info)
{
_puts("help call works. Function not yet implemented \n");
if (info->argv[0] != NULL)
_puts(info->argv[0]);
return (0);
}
