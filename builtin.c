#include "shell.h"

/**
 * _myexit - exits shell
 * @info: Structure
 * Return:exit status
 *
 */
int _myexit(info_t *info) {
    if (info->argv[1] != NULL) {
        char *endptr;
        long exitcheck = strtol(info->argv[1], &endptr, 10);

        if (*endptr != '\0' || exitcheck < INT_MIN || exitcheck > INT_MAX) {
            fprintf(stderr, "Invalid exit number: %s\n", info->argv[1]);
            return (1);
        }

        info->err_num = (int)exitcheck;
    } else {
        info->err_num = -1;
    }

    return (-2);
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
        return 0;
    }

    if (info->argv[1] == NULL)
    {
        dir = _getenv(info, "PWD=");
        dir = (dir == NULL) ? "/" : dir;
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (_getenv(info, "OLDPWD="))
            _puts(_getenv(info, "OLDPWD="));
        else
            _puts(buffer), _putchar('\n');

        if (_getenv(info, "OLDPWD="))
            chdir_ret = chdir(_getenv(info, "OLDPWD="));
        else
            chdir_ret = chdir("/");

        return (!_getenv(info, "OLDPWD=") ? 1 : 0);
    }
    else
    {
        chdir_ret = chdir(info->argv[1]);

        if (chdir_ret == -1)
        {
            print_error(info, "cannot cd to ");
            _eputs(info->argv[1]);
            _eputchar('\n');
        }
        else
        {
            _setenv(info, "OLDPWD", _getenv(info, "PWD="));
            _setenv(info, "PWD", getcwd(buffer, 1024));
        }
    }
    return 0;
}

/**
 * print_help_message - function to print message
 * 
 * Return: 0
*/
void print_help_message() {
    printf("Function not yet implemented.\n");
}

/**
 * print_argument - arg to print
 * @arg: argurment
 * Return: 0
 */

void print_argument(const char *arg) {
    printf("%s\n", arg);
}

/**
 * _myhelp - cd of the process
 * @info: Structure
 * Return: 0
 */

int _myhelp(info_t *info) {
    if (info->argv[0] != NULL) {
        print_help_message();
        print_argument(info->argv[0]); 
    }

    return (0);
}


