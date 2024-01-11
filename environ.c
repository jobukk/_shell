#include "shell.h"

/**
 * _myenv - current env
 * @info: Structure
 * Return: 0
 */
int _myenv(info_t *info)
{
return (print_list_str(info->env));
}

/**
 * _getenv - value of an environ
 * @info: Structure
 * @name:var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
char *p;
list_t *node;
for (node = info->env; node; node = node->next)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
}
return (NULL);
}


/**
 * _mysetenv - Initialize a new env
 * @info: Structure
 * Return: 0
 */
int _mysetenv(info_t *info)
{
int result;
if (info->argc != 3)
return (_eputs("wrong number of arguments\n"), 1);

if (_setenv(info, info->argv[1], info->argv[2]))
result = 0;
else
{
_eputs("Setenv failed\n");
result = 1;
}
return (result);

}


/**
 * _myunsetenv - Remove an env
 * @info: Structure
 * Return: 0
 */
int _myunsetenv(info_t *info)
{
int i;    
if (info->argc == 1)
{
_eputs("Too few arguments.\n");
return (1);
}

for (i = 1; info->argv[i]; i++)
_unsetenv(info, info->argv[i]);

return (0);
}


/**
 * populate_env_list - populate env
 * @info: Structure
 * Return: 0
 */
int populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t i = 0;

while (environ[i])
add_node_end(&node, environ[i]);


info->env = node;
return (0);
}
