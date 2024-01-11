#include "shell.h"

/**
 * _myhistory - the history list
 * @info: Structure
 * Return: 0
 */
int _myhistory(info_t *info)
{
return ((print_list(info->history)));
}

/**
 * unset_alias - alias to string
 * @info: struct
 * @str: string alias
 *
 * Return: 0 else 1
 */
int unset_alias(info_t *info, char *str)
{
char *p = _strchr(str, '=');

if (!p)
return (1);

*p = 0;
int index_to_delete = get_node_index(info->alias,
node_starts_with(info->alias, str, -1));
int ret = delete_node_at_index(&(info->alias), index_to_delete);
*p = '=';

return (ret);
}


/**
 * set_alias - sets alias
 * @info: struct
 * @str: string alias
 *
 * Return: 0 else 1
 */
int set_alias(info_t *info, char *str)
{
char *p;

p = _strchr(str, '=');
int ret = (!p) ? 1 : (!*++p) ? unset_alias(info, str) :
(unset_alias(info, str) || (add_node_end(&(info->alias), str, 0) == NULL));
return (ret);



}

/**
 * print_alias - alias string
 * @node: alias
 *
 * Return: 0 else 1
 */
int print_alias(list_t *node)
{
char *p = NULL, *a = NULL;
if (!node)
return (1);

p = _strchr(node->str, '=');
a = node->str;

while (a <= p)
_putchar(*a++);

_putchar('\'');
_puts(p + 1);
_puts("'\n");

return (0);
}

/**
 * _myalias - man alias
 * @info: Structure
 * Return:  0
 */
int _myalias(info_t *info)
{
char *p;
int i;
list_t *node;

if (info->argc == 1)
{
for (node = info->alias; node; node = node->next)
print_alias(node);
return (0);
}

for (i = 1; (p = info->argv[i]); i++)
{
p = _strchr(info->argv[i], '=');

if (p)
set_alias(info, info->argv[i]);
else
print_alias(node_starts_with(info->alias, info->argv[i], '='));
}

return (0);
}


