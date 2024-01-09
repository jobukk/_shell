#include "shell.h"

/**
* get_environ - returns copy of our environ
* @info: Struct contain arguments.
* Return:  0
*/
char **get_environ(info_t *info)

{
return ((!info->environ || info->env_changed)
? (
info->environ = list_to_strings(info->env),
info->env_changed = 0,
info->environ
)
: info->environ);

}


/**
* _unsetenv - Remove env variable
* @info: Strut containing potential arguments.
*
* @var: the string env var property
* Return: 1 delete or 0
*/

int _unsetenv(info_t *info, char *var)
{
size_t i;
list_t *node = info->env;
char *p;

if (!node || !var)
return (0);

for (i = 0; node; node = node->next, i++)
{
p = starts_with(node->str, var);
info->env_changed = (p && *p == '=')
? (
delete_node_at_index(&(info->env), i),
i = 0,
node = info->env,
1
)
: info->env_changed;

}

return (info->env_changed);
}



/**
* _setenv - Init new env variable or do modification.
* @info: Struct with arguments.
* @var: the str env var property
* @value: the str env var value
*  Return: 0
*/


int _setenv(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);

_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);

for (node = info->env; node; node = node->next)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
}

add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}
