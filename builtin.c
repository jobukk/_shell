#include "shell.h"

/**
* _myexit - exit shell
* @info: Structure containing arguments
*  Return: (0) if info.argv[0] != "exit"
*/
int _erratoi(char *);
int _myexit(info_t *info)
{
return ((info->argv[1]) ?
((info->err_num = _erratoi(info->argv[1])) == -1 ?
((info->status = 2, print_error(info, "unwanted number: "),
_eputs(info->argv[1]), _eputchar('\n'), 1)
) : -2
) :
((info->err_num = -1, -2)
));
}

/**
* _mycd - changes directory of process
* @info: Structure containing arguments
*  Return: 0
*/
int _mycd(info_t *info)
{
char *s, *dir, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
_puts("write:>>getcwd failure msg <<\n");

if (!info->argv[1])
{
dir = _getenv(info, "Home=");
chdir_ret = chdir((dir ? dir : _getenv(info, "PWD=")) ? dir : "/");
}
else if (_strcmp(info->argv[1], "-") == 0)
{
dir = _getenv(info, "OldPWD=");
chdir_ret = (!dir ?
(_puts(s), _putchar('\n')) :
(_puts(dir), _putchar('\n')),
chdir((dir ? dir : _getenv(info, "OLDPWD=")) ? dir : "/"));
}
else
{
chdir_ret = chdir(info->argv[1]);
}

if (chdir_ret == -1)
{
print_error(info, "can't cd to ");
_eputs(info->argv[1]), _eputchar('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, 1024));
}

return (0);
}

/**
* _myhelp - help funct
* @info: Structure containing arguments
*  Return: 0
*/

int _myhelp(info_t *info)
{
char **arg_array;

arg_array = info->argv;
_puts("yet to be implemented \n");
if (0)
{
_puts(*arg_array);
}
return (0);
}
