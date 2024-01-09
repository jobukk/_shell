#include "shell.h"

/**
* is_chain - test if char is chain delimiter
* @info: parameter struct
* @buf: char buffer
* @p: address of current position in buf
*
* Return: 1 on success
*/
int is_chain(info_t *info, char *buf, size_t *p)
{
size_t j = *p;
char c = buf[j];

if ((c == '|' || c == '&') && buf[j + 1] == c)
{
buf[j] = 0;
*p = ++j;
info->cmd_buf_type = (c == '|') ? CMD_OR : CMD_AND;
}
else if (c == ';')
{
buf[j] = 0;
*p = j;
info->cmd_buf_type = CMD_CHAIN;
}
else
{
return (0);
}

return (1);
}

/**
* check_chain - continue chaining based on status
* @info: parameter struct
* @buf: char buffer
* @p: address of current in buf
* @i: starting pos in buf
* @len: len of buf
*
* Return: Void
*/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;

if ((info->cmd_buf_type == CMD_AND && info->status) ||
(info->cmd_buf_type == CMD_OR && !info->status))
{
buf[i] = 0;
j = len;
}

*p = j;
}

/**
* replace_alias - replace aliases in tokenized str
* @info: parameter struct
*
* Return: 1 on success
*/
int replace_alias(info_t *info)
{
int i = 0;
list_t *node;
char *p;
char *tempStr;

while (i < 10 && (node = node_starts_with(info->alias, info->argv[0], '=')))
{
free(info->argv[0]);
p = _strchr(node->str, '=');
tempStr = _strdup(p + 1);

if (!p || !tempStr)
{
free(tempStr);
return (0);
}

info->argv[0] = tempStr;
i++;
}

return (i == 10);
}

/**
* replace_vars - replace vars in tokenize str
* @info: parameter struct
*
* Return: 1 on success
*/
int replace_vars(info_t *info)
{
int i = 0;
char *convertedNumber;
list_t *node;
node = node_starts_with(info->env, &info->argv[i][1], '=');

while (info->argv[i])
{
if (info->argv[i][0] == '$' && info->argv[i][1])
{
if (!_strcmp(info->argv[i], "$?"))
{
convertedNumber = convert_number(info->status, 10, 0);
replace_string(&(info->argv[i]), _strdup(convertedNumber));
}
else if (!_strcmp(info->argv[i], "$$"))
{
replace_string(&(info->argv[i]),
_strdup(convert_number(getpid(), 10, 0)));
}
else if (node)
{
replace_string(&(info->argv[i]),
_strdup(_strchr(node->str, '=') + 1));

}
else
{
replace_string(&(info->argv[i]), _strdup(""));
}
}

i++;
}

return (0);
}

/**
* replace_string - replace str
* @old: address of old str
* @new: new str
*
* Return: 1 on success
*/
int replace_string(char **old, char *new)
{
free(*old);
return ((*old = new) != NULL);
}
