#include "shell.h"

/**
 * hsh - shell loop
 * @info: struct 
 * @av:  argument 
 *
 * Return: 0 
 */
int hsh(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    for (; r != -1 && builtin_ret != -2; clear_info(info))
    {
        interactive(info) ? _puts("$ ") : (void)0;
        _eputchar(BUF_FLUSH);
        r = get_input(info);
        if (r != -1)
        {
            set_info(info, av);
            builtin_ret = find_builtin(info);
            (builtin_ret == -1) ? find_cmd(info) : (void)0;
        }
        else
        {
            interactive(info) ? _putchar('\n') : (void)0;
        }
        free_info(info, 0);
    }
    write_history(info);
    free_info(info, 1);
    (interactive(info) && info->status) ? exit(info->status) : (void)0;
    (builtin_ret == -2) ? ((info->err_num == -1) ? exit(info->status) : exit(info->err_num)) : (void)0;

    return (builtin_ret);
}


/**
 * find_builtin - builtin command
 * @info:  struct
 *
 * Return: - 1
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

    while (builtintbl[i].type && (_strcmp(info->argv[0], builtintbl[i].type) != 0) ? i++ : 0)
        ;

    return (builtintbl[i].type) ? (info->line_count++, builtintbl[i].func(info), builtintbl[i].func(info)) : built_in_ret;
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

    k ? (path = find_path(info, _getenv(info, "PATH="), info->argv[0]), path ? (info->path = path, fork_cmd(info)) : ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]) ? fork_cmd(info) : (*(info->arg) != '\n' ? (info->status = 127, print_error(info, "not found\n")) : 0))) : 0;
}


/**
 * fork_cmd - forks an exec
 * @info:  info struct
 *
 * Return: void
 */


void fork_cmd(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    (child_pid == -1) ? (perror("Error:"), 0) : 0;

    if (child_pid == 0)
    {
        (execvp(info->path, info->argv) == -1) ? (perror("Error executing"), free_info(info, 1), (errno == EACCES ? exit(126) : exit(1))) : 0;
    }
    else
    {
        wait(&(info->status));
        (WIFEXITED(info->status)) ? (info->status = WEXITSTATUS(info->status), (info->status == 126 ? print_error(info, "Permission denied\n") : 0)) : 0;
    }
}
