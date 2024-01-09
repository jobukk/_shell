#include "shell.h"

/**
 * hsh - main shell iteration - loop
 * @info: param & return info struct
 * @av: arg vector from main()
 *
 * Return: 0 on success and 1 on error
 */
int hsh(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    for (; r != -1 && builtin_ret != -2; clear_info(info), _eputchar(BUF_FLUSH), r = get_input(info))
    {
        if (r != -1)
        {
            set_info(info, av);
            builtin_ret = find_builtin(info);
            if (builtin_ret == -1)
                find_cmd(info);
        }
        else if (interactive(info))
        {
            _putchar('\n');
        }

        free_info(info, 0);
    }

    write_history(info);
    free_info(info, 1);

    if (!interactive(info) && info->status)
    {
        exit(info->status);
    }

    if (builtin_ret == -2)
    {
        exit((info->err_num == -1) ? info->status : info->err_num);
    }

    return builtin_ret;
}


/**
 * find_builtin - find the builtin command
 * @info:param & return info struct
 *
 * Return: -1 not found,
 *			0 success,
 *			1 built fail,
 *			-2 signals exit()
 */

int find_builtin(info_t *info)
{
    int i = 0;
    int built_in_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}};

    while (builtintbl[i].type)
{
    if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
    {
        info->line_count++;
        built_in_ret = builtintbl[i].func(info);
        break;
    }
    i++;
}

return built_in_ret;

}

/**
 * find_cmd - find the command in PATH
 * @info:param & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
    char *path = NULL;
    int i = 0, k = 0;

    info->path = info->argv[0];
    while (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }

    while (info->arg[i])
    {
        if (!is_delim(info->arg[i], " \t\n"))
            k++;
        i++;
    }

    if (!k)
        return;

    path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

    if (path || interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/' || is_cmd(info, info->argv[0]))
    {
        if (path)
        {
            info->path = path;
        }
        fork_cmd(info);
    }
    else if (*(info->arg) != '\n')
    {
        info->status = 127;
        print_error(info, "not found\n");
    }
}


/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */

void fork_cmd(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return;
    }

    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environ(info)) == -1)
        {
            free_info(info, 1);
            exit((errno == EACCES) ? 126 : 1);
        }
    }
    else
    {
        wait(&(info->status));

        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);

            if (info->status == 126)
                print_error(info, "Permission not allowed\n");
        }
    }
}
