#include "shell.h"

/**
 * clear_info - info_t struct init
 * @info: struct
 */
void clear_info(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}

/**
 * set_info - init info_t
 * @info: struct
 * @av: arg vector
 */
void set_info(info_t *info, char **av)
{
int a = 0;

info->fname = av[0];

if (info->arg)
{
char **temp_argv = strtow(info->arg, " \t");
info->argv = temp_argv ? temp_argv : (
(info->argv = malloc(sizeof(char *) * 2)) ?
(info->argv[0] = _strdup(info->arg), info->argv[1] = NULL, info->argv) :
NULL
);

while (info->argv && info->argv[a])
a++;

info->argc = a;

replace_alias(info);
replace_vars(info);
}
}


/**
 * free_info - frees info_t
 * @info: struct
 * @all: true
 */
void free_info(info_t *info, int all)
{
ffree(info->argv);
info->argv = NULL;
info->path = NULL;

if (all)
{
free(!info->cmd_buf ? info->arg : NULL);
free_list(&(info->env));
free_list(&(info->history));
free_list(&(info->alias));
ffree(info->environ);
info->environ = NULL;

bfree((void **)info->cmd_buf);

if (info->readfd > 2)
close(info->readfd);


_putchar(BUF_FLUSH);
}
}

