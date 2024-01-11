#include "shell.h"

/**
 * interactive - true in interactive mode
 * @info: structure address
 *
 * Return: 1 else 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks delimiter in char
 * @c: char
 * @delim: delimiter str
 * Return: 1 else 0
 */
int is_delim(char c, char *delim)
{
	for (; *delim; delim++)
		(*delim == c) ? (c = 1) : 0;
	return (c);
}

/**
 * _isalpha - alphabetic character
 * @c: char to input
 * Return: 1 else 0
 */
int _isalpha(int c)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0);
}

/**
 * _atoi - string to integer
 * @s: string
 * Return: 0 if no number is converted
 */
int _atoi(char *s)
{
	int i;
	int sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		sign = (s[i] == '-') ? -1 : sign;
		result = (s[i] >= '0' && s[i] <= '9') ? result * 10 + (s[i] - '0') : result;
		flag = (flag == 1) ? 2 : (s[i] >= '0' && s[i] <= '9') ? 1 : flag;
	}

	output = (sign == -1) ? -result : result;

	return (output);
}
