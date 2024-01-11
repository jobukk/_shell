#include "shell.h"

#include <stdlib.h>

void free_string_array(char **array)
{
	int i;
    if (array == NULL) {
        return;
    }

    for (i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }

    free(array);
}

/**
 * get_environ - string array
 * @info: Structure
 * Return:  0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		free_string_array(info->environ);
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}


/**
 * _unsetenv - Remove an env var
 * @info: Structure
 * @var: string env
 * Return: 1 on delete else 0
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t j = 0;
	char *p;

	if (!node || !var)
		return (0);

	for (; node; node = node->next, j++)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			node = info->env;
		}
	}

	return (info->env_changed);
}

/**
 * _setenv - Initialize env
 * @info: Structure
 * @var: string env var property
 * @value: string env var value
 * Return: 0
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
			free(buf);
			return (0);
		}
	}

	add_node_end(&(info->env), buf);
	info->env_changed = 1;

	return (0);
}
