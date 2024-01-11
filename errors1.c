#include "shell.h"

/**
 * _erratoi -string to an integer
 * @s: the string
 * Return: 0 no number
 */
int _erratoi(char *s)
{
int a = 0;
unsigned long int result = 0;

if (*s == '+')
s++;


while (s[a] != '\0')
{
if (s[a] >= '0' && s[a] <= '9')
{
result *= 10;
result += (s[a] - '0');
if (result > INT_MAX)
return (-1);
}
else
{
return (-1);
}
a++;
}

return (result);
}

/**
 * print_error - error message
 * @info: parameter
 * @estr: string
 * Return: 0 no number
 */
void print_error(info_t *info, char *estr)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

/**
 * print_d -  decimal
 * @input: input
 * @fd: filedescriptor to write to
 *
 * Return: number of char
 */
int print_d(int input, int fd)
{
int (*__putchar)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
int count = 0;
unsigned int _abs_ = (input < 0) ? -input : input;
unsigned int current = _abs_;

if (input < 0)
{
__putchar('-');
count++;
}

while (current > 1)
{
if (_abs_ / 1000000000)
{
__putchar('0' + current / 1000000000);
count++;
}
current %= 1000000000;
}

__putchar('0' + current);
count++;

return (count);
}

/**
 * convert_number -itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */

char *convert_number(long int num, int base, int flags)
{
unsigned long n = (flags & CONVERT_UNSIGNED) ? num : -num;
char sign = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? '-' : '\0';
static char buffer[50];
char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
char *ptr = &buffer[50 - 1];
*ptr = '\0';

do {
*--ptr = array[n % base];
} while ((n /= base) != 0);

if (sign)
*--ptr = sign;

return (ptr);
}

/**
 * remove_comments - replaces first instance with '\0'
 * @buf: address
 *
 * Return: 0;
 */
void remove_comments(char *buf)
{
int i = 0;
while (buf[i] != '\0')
{
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
i++;
}
}
