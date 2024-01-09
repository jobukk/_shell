#include "shell.h"

/**
* _myhistory - displays the history list, one command by line.
* @info: Structure containing  arguments..
*  Return: 0
*/
list_t *add_node_end(list_t **, const char *, int);
int _myhistory(info_t *info)
{
return (print_list(info->history), 0);
}

/**
* unset_alias -  alias to string
* @info: parameter struct
* @str: string alias
*
* Return:  0 success, 1 error
*/

int unset_alias(info_t *info, char *str)
{
char *p;
int ret;

p = _strchr(str, '=');

if (p != NULL)
{
char c = *p;
*p = 0;
ret = delete_node_at_index(
&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, str, -1))
);

*p = c;
return (ret);
}

return (1);
}


/**
* set_alias - alias to string
* @info:  struct
* @str:  string alias
*
* Return: 0 success else 1
*/
int set_alias(info_t *info, char *str)
{
char *p = _strchr(str, '=');

return ((p && *++p) ?
(unset_alias(info, str), add_node_end(&(info->alias), str, 0) == NULL) :
unset_alias(info, str));


}


/**
* print_alias - print alias string
* @node: alias node
*
* Return: 0 on success else 1
*/

int print_alias(list_t *node)
{
return ((node) ? (
_puts(_strchr(node->str, '=')),
_puts("'"),
_puts(_strchr(node->str, '=') + 1),
_puts("'\n"),
0
) : 1);

}

/**
* _myalias - man alias
* @info: Structure containing arguments
*  Return: 0
*/
int _myalias(info_t *info)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;

if (info->argc == 1)
{
node = info->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}

i = 1;
while (info->argv[i])
{
p = _strchr(info->argv[i], '=');
if (p)
set_alias(info, info->argv[i]);
else
print_alias(node_starts_with(info->alias, info->argv[i], '='));
i++;
}

return (0);
}


