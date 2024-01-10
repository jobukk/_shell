#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimiter
 * @c: the char to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	for (; *delim; delim++)
		(*delim == c) ? (c = 1) : 0;
	return (c);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0;
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *s)
{
	int i ;
	int sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i= 0;  s[i] != '\0' && flag != 2; i++)
	{
		sign = (s[i] == '-') ? -1 : sign;
		result = (s[i] >= '0' && s[i] <= '9') ? result * 10 + (s[i] - '0') : result;
		flag = (flag == 1) ? 2 : (s[i] >= '0' && s[i] <= '9') ? 1 : flag;
	}

	output = (sign == -1) ? -result : result;

	return (output);
}
