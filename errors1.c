
#include "shell.h"


/**
 * _erratoi - converts a str to an integer
 * @s: string
 * Return: 0 no numbers in string else 1
 */

int _erratoi(char *s)
{
int i = 0;
unsigned long int result = 0;

if (*s == '+')
s++;  /* TODO: why does this make main return 255? */

while (s[i] != '\0')
{
if (!(s[i] >= '0' && s[i] <= '9'))
{
return (-1);
}

result *= 10;
result += (s[i] - '0');
if (result > INT_MAX)
return (-1);

i++;
}

return (result);
}

/**
 * print_error - error message
 * @info: param & return info struct
 * @estr: str containing specified error type
 * Return:0 else 1
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
 * print_d - func prints decimal
 * @input: input
 * @fd: filedescriptor to write to
 *
 * Return: numb of char printed
 */

int print_d(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int count = 0;
unsigned int _abs_, current;
int i;

if (fd == STDERR_FILENO)
__putchar = _eputchar;

_abs_ = (input < 0) ? -input : input;
count += (input < 0) ? (__putchar('-'), 1) : 0;

current = _abs_;

for (i = 1000000000; i > 1; i /= 10)
{
count += (_abs_ / i) ? (__putchar('0' + current / i), 1) : 0;
current %= i;
}

__putchar('0' + current);
count++;

return (count);
}

/**
* convert_number - it converts num, a clone of itoa
* @num: num
* @base: base
* @flags: argument
*
* Return: strings
*/

char *convert_number(long int num, int base, int flags)
{
static char buffer[50];
char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" :
"0123456789ABCDEF";
char *ptr = &buffer[49];
*ptr = '\0';

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
*--ptr = '-';
num = -num;
}

while (num != 0)
{
*--ptr = array[num % base];
num /= base;
}

return (ptr);
}


/**
 * remove_comments - func instance of '#' with '\0'
 * @buf:  the string to modify
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
