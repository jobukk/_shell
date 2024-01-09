#include "shell.h"


/**
* _myenv - ouput the current env
* @info: Struct containing potential arg.
* Return:  0
*/
int _myenv(info_t *info)
{
return (print_list_str(info->env));
}

/**
* _getenv - get value of an env variable
* @info: Struct containing  arg
* @name: env variable name
*
* Return: value
*/
char *_getenv(info_t *info, const char *name)
{
list_t *node;

for (node = info->env; node; node = node->next)
{
if (starts_with(node->str, name) && *starts_with(node->str, name))
return (starts_with(node->str, name));
}

return (NULL);
}


/**
* _mysetenv - Init a new environ variable or modify
* @info: Struct potential arg.
*  Return: 0
*/
int _mysetenv(info_t *info)
{
if (info->argc != 3)
return (_eputs("incorrect num of arg\n"), 1);

return (_setenv(info, info->argv[1], info->argv[2]) ? 0 : 1);
}



/**
* _myunsetenv - Remove environ variable
* @info: Structure containing arg.
*  Return: 0
*/
int _myunsetenv(info_t *info)
{
int i = 1;

if (info->argc == 1)
{
_eputs("less args.\n");
return (1);
}

while (i <= info->argc)
{
_unsetenv(info, info->argv[i]);
i++;
}

return (0);
}

/**
* populate_env_list - populates environment linked list
* @info: Structure containing args.
* Return:  0
*/

int populate_env_list(info_t *info)
{
list_t *node = NULL;
size_t i = 0;

while (environ[i])
{
add_node_end(&node, environ[i], 0);
i++;
}

info->env = node;
return (0);
}


