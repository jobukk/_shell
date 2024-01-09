#include "shell.h"

/**
* interactive - shell is interactive mode-true
* @info: struct address
*
* Return: 1 else 0
*/
int interactive(info_t *info)
{
return ((isatty(STDIN_FILENO) && info->readfd <= 2) ? 1 : 0);
}


/**
* is_delim - checks delimeter in char
* @c: char to check
* @delim: delimeter string
* Return: 1 else 0
*/
int is_delim(char c, char *delim)
{
for (; *delim; delim++)
if (*delim == c)
return (1);
return (0);
}


/**
*_isalpha - alphabetic char
*@c: char to input
*Return: 1 else 0
*/
int _isalpha(int c)
{
return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0);
}


/**
*_atoi - converts a str to  interger
*@s: str to convert
*Return: 0 on success
*/
int _atoi(char *s)
{
int i = 0, sign = 1, flag = 0, output = 0;

while (s[i] != '\0' && flag != 2)
{
sign = (s[i] == '-') ? -1 : sign;

if (s[i] >= '0' && s[i] <= '9')
{
flag = 1;
output = output * 10 + (s[i] - '0');
}
else if (flag == 1)
flag = 2;

i++;
}

return (sign *output);
}
