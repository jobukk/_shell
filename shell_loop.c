#include "shell.h"

/**
 * hsh - shell loop
 * @info: struct 
 * @av: argument 
 *
 * Return: 0 
 */
int hsh(info_t *info, char **av)
{
    ssize_t k = 0;
    int builtin = 0;

    for (; k != -1 && builtin != -2; clear_info(info))
    {
        if (interactive(info))
        {
            _puts("$ ");
            _eputchar(BUF_FLUSH);
        }

        k = get_input(info);

        if (k != -1)
        {
            set_info(info, av);
            builtin = find_builtin(info);
            if (builtin == -1)
            {
                find_cmd(info);
            }
        }
        else if (interactive(info))
        {
            _putchar('\n');
        }

        free_info(info, 0);
    }

    write_history(info);
    free_info(info, 1);

    if (interactive(info) && info->status)
    {
        exit(info->status);
    }

    if (builtin == -2)
    {
        if (info->err_num == -1)
        {
            exit(info->status);
        }
        else
        {
            exit(info->err_num);
        }
    }

    return builtin;
}


/**
 * find_builtin - builtin command
 * @info: struct
 *
 * Return: -1
 */
int find_builtin(info_t *info)
{
    int i;
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

    for (i = 0; builtintbl[i].type && _strcmp(info->argv[0], builtintbl[i].type) != 0; i++)
        ;

    return builtintbl[i].type ? (info->line_count++, builtintbl[i].func(info)) : built_in_ret;
}
/**
 * find_cmd - finds a command
 * @info: info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
    char *path = NULL;
    int i = 0, k = 0;

    info->path = info->argv[0];

    info->linecount_flag == 1 ? (info->line_count++, info->linecount_flag = 0) : 0;

    while (info->arg[i])
    {
        is_delim(info->arg[i], " \t\n") ? 0 : k++;
        i++;
    }

    if (k) {
        path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
        if (path) {
            info->path = path;
            fork_cmd(info);
        } else {
            if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0])) {
                fork_cmd(info);
            } else {
                if (*(info->arg) != '\n') {
                    info->status = 127;
                    print_error(info, "not found\n");
                }
            }
        }
    }
}

/**
 * fork_cmd - forks an exec
 * @info: info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("Error in fork:");
        return;
    }

    if (child_pid == 0)
    {
        if (execvp(info->path, info->argv) == -1)
        {
            perror("Error in execvp:");
            free_info(info, 1);
            if (errno == EACCES)
                exit(126);
            else
                exit(1);
        }
    }
    else
    {
        wait(&(info->status));
        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                print_error(info, "Permission is not accepted\n");
        }
    }
}
