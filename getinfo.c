#include "shell.h"

/**
* clear_info - init info_t struct
* @info: struct address
*/
void clear_info(info_t *info)
{
info->arg = NULL;
info->argv = NULL;
info->path = NULL;
info->argc = 0;
}

/**
* set_info - init info_t struct
* @info: struct address
* @av: arg vector
*/

void set_info(info_t *info, char **av)
{
int i = 0;

info->fname = av[0];
if (info->arg)
{
info->argv = strtow(info->arg, " \t");

if (!info->argv)
{
info->argv = malloc(sizeof(char *) * 2);

if (info->argv)
{
info->argv[0] = _strdup(info->arg);
info->argv[1] = NULL;
}
}

i = 0;
while (info->argv && info->argv[i])
{
i++;
}

info->argc = i;

replace_alias(info);
replace_vars(info);
}
}

/**
* free_info - free info_t struct field
* @info: struct address
* @all: true
*/
void free_info(info_t *info, int all)
{
int i = 0;
for (i = 0; info->argv && info->argv[i]; i++)
free(info->argv[i]);
ffree(info->argv);

info->path = NULL;

if (all)
{
if (!info->cmd_buf)
free(info->arg);

if (info->env)
free_list(&(info->env));

if (info->history)
free_list(&(info->history));

if (info->alias)
free_list(&(info->alias));



ffree(info->environ);
info->environ = NULL;

info->cmd_buf ? bfree((void **)info->cmd_buf) : 0;
info->readfd > 2 ? close(info->readfd) : 0;

_putchar(BUF_FLUSH);
}
}
