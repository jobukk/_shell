#include "shell.h"

/**
 * is_chain - test current char in buffer
 * @info: struct
 * @buf: char buffer
 * @p: address
 *
 * Return: 1
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	while (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}

	while (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}

	while (buf[j] == ';')
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}

	*p = j;
	return (1);
}

/**
 * check_chain - chaining
 * @info: struct
 * @buf: buffer
 * @p: address
 * @i: starting position
 * @len: len of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
		(info->status) ? (buf[i] = 0, j = len) : 0;

	if (info->cmd_buf_type == CMD_OR)
		(!info->status) ? (buf[i] = 0, j = len) : 0;

	*p = j;
}

/**
 * replace_alias - replace an aliases
 * @info:  struct
 *
 * Return: 1
 */
int replace_alias(info_t *info)
{
    int i = 0;
    list_t *node;
    char *p;

    while (i < 10)
    {
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return 0;

        free(info->argv[0]);
        p = _strchr(node->str, '=');
        if (!p)
            return 0;

        p = _strdup(p + 1);
        if (!p)
            return 0;

        info->argv[0] = p;
        i++;
    }
    return 1;
}

/**
 * replace_vars - replaces vars
 * @info: struct
 *
 * Return: 1
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	while (info->argv[i])
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1] ? (i++, 1) : 0)
{
    continue;
}


		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]), _strdup(convert_number(info->status, 10, 0)));
		}
		else if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
		}
		else
		{
			node = node_starts_with(info->env, &info->argv[i][1], '=');
			if (node)
			{
				replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
			}
			else
			{
				replace_string(&info->argv[i], _strdup(""));
			}
		}

		i++;
	}
	return 0;
}

/**
 * replace_string - string
 * @old: address
 * @new: new str
 *
 * Return: 1 
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return 1;
}
